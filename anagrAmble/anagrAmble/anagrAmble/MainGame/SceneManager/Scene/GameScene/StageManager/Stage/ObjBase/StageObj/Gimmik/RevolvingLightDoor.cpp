//==================================================================================================================================//
//!< @file		RevolvingLightDoor.cpp
//!< @brief		ar::RevolvingLightDoorクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "RevolvingLightDoor.h"
#include "../Block/LightBlock.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int LightBlockCount	= 4;			//!< 光ブロックの数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

RevolvingLightDoor::RevolvingLightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_OriginalTypeID(typeID)
{
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;
}

RevolvingLightDoor::~RevolvingLightDoor(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		sl::DeleteSafely(&pblock);
	}
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void RevolvingLightDoor::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left = -(m_StageChipSize / 2);
	m_RectSize.m_Top = -(m_StageChipSize / 2);
	m_RectSize.m_Right = (m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.5f, 0.0f, 0.55f, 0.088f };

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// 光ブロックを生成する
	for(int count = 0; count < LightBlockCount; ++count)
	{
		m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
												, m_StageIndexData, m_DrawingID.m_TexID));
	}

	// 光ブロックを初期化する
	for(auto& pLightBlock : m_pLightBlocks)
	{
		pLightBlock->Initialize();
	}

	Revolve();

	// 空間入れ替え処理終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::RevolvingLightDoor::Revolve, this));

	// 時戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_return_end", std::bind(&ar::RevolvingLightDoor::Revolve, this));

	// ステージに位置を固定する
	//m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);
}

void RevolvingLightDoor::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_TypeID = m_OriginalTypeID;

	// 光ブロックを自分の位置にもどしてから再度展開
	for(auto& pLightBlock : m_pLightBlocks)
	{
		pLightBlock->ChangeStagePos(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);;
	}

	Revolve();
}

void RevolvingLightDoor::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// スイッチONOFFで交互に切り替える
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		if(m_OriginalTypeID == REVOLVING_LIGHT_DOOR_HORIZONTAL)
		{
			m_TypeID = REVOLVING_LIGHT_DOOR_VERTICAL;
		}
		else
		{
			m_TypeID = REVOLVING_LIGHT_DOOR_HORIZONTAL;
		}

		Revolve();
		break;

	case SWITCH_OPERATING_AREA_OFF:
		m_TypeID = m_OriginalTypeID;
		Revolve();
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void RevolvingLightDoor::Run(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Control();
	}
}

void RevolvingLightDoor::Render(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Draw();
	}
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void RevolvingLightDoor::HandleEvent(void)
{}

void RevolvingLightDoor::Revolve(void)
{
	// 一旦光ブロックを元位置に戻す
	for(auto& pLightBlock : m_pLightBlocks)
	{
		pLightBlock->ChangeStagePos(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);
	}

	Stage::INDEX_DATA checkIndexData;

	switch(m_TypeID)
	{
	case REVOLVING_LIGHT_DOOR_HORIZONTAL:

		// 右方向へまず光ブロックの半分を展開
		for(int count = 1; count <= (LightBlockCount / 2); ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum + count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを展開する
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら展開をやめる
				break;;
			}
		}

		// 左方向へ残り半分の光ブロックを展開
		for(int count = 1; count <= (LightBlockCount / 2); ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum - count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを展開する
				m_pLightBlocks[(count - 1 + (LightBlockCount / 2))]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら展開をやめる
				return;
			}
		}
		break;

	case REVOLVING_LIGHT_DOOR_VERTICAL:

		// 上方向へまず光ブロックの半分を展開
		for(int count = 1; count <= (LightBlockCount / 2); ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum - count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 何もないならそのスペースに光ブロックを展開する
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら展開をやめる
				break;;
			}
		}

		// 下方向へ光ブロック展開
		for(int count = 1; count <= (LightBlockCount / 2); ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum + count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを展開する
				m_pLightBlocks[(count - 1 + (LightBlockCount / 2))]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら展開をやめる
				return;
			}
		}
		break;

	default:
		// do nothing
		break;
	}
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
