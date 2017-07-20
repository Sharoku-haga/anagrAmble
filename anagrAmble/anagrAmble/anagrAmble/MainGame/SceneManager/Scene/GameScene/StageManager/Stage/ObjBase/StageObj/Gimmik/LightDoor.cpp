//==================================================================================================================================//
//!< @file		LightDoor.cpp
//!< @brief		ar::LightDoorクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightDoor.h"
#include "../Block/LightBlock.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../StageEffect/SandwichEffect.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int LightBlockCount = 3;			//!< 光ブロックの数(ドアの長さ分)

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LightDoor::LightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
	, const Stage::INDEX_DATA& rStageIndexData, int texID, ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasOpened(false)
{
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;
}

LightDoor::~LightDoor(void)
{
	for(auto& pblock : m_pLightBlocks)
	{
		sl::DeleteSafely(&pblock);
	}
	sl::DeleteSafely(&m_pSandwichEffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightDoor::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.55f, 0.0f, 0.6f, 0.088f };

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();

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

	// 扉を閉じる
	Close();

	// 空間入れ替え処理終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::LightDoor::Close, this));

	// 時戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_return_end", std::bind(&ar::LightDoor::Close, this));

	// プレイヤーリスポーン終了イベント
	GameEventManager::Instance().RegisterEventType("player_respawn_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_respawn_end", std::bind(&ar::LightDoor::Close, this));
}

void  LightDoor::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSandwichEffect->ChangeStagePos(m_Pos);

	// 光ブロックを1回自分位置に収納してから再度展開する
	Open();
	Close();
}

void LightDoor::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// スイッチONなら扉を開け、OFFなら閉める
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		Open();
		break;

	case SWITCH_OPERATING_AREA_OFF:
		Close();
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightDoor::Run(void)
{
	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();

	}

	for(auto& pblock : m_pLightBlocks)
	{
		pblock->Control();
	}
}

void LightDoor::Render(void)
{
	// 開いているなら光ブロックの処理を飛ばす
	if(RESULT_FAILED(m_HasOpened))
	{
		for(auto& pblock : m_pLightBlocks)
		{
			pblock->Draw();
		}
	}

	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}
}

void LightDoor::HandleEvent(void)
{}

void LightDoor::Open(void)
{
	m_HasOpened = true;
	for(auto& pblock : m_pLightBlocks)
	{
		pblock->ChangeStagePos(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);
	}
}

void LightDoor::Close(void)
{
	m_HasOpened = false;
	Stage::INDEX_DATA checkIndexData;

	// 扉の種類にあわせて光ブロックを展開していく
	switch(m_TypeID)
	{
	case LIGHT_DOOR_UP:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YIndexNum = m_StageIndexData.m_YIndexNum - count;
			checkIndexData.m_XIndexNum = m_StageIndexData.m_XIndexNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_DOWN:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YIndexNum = m_StageIndexData.m_YIndexNum + count;
			checkIndexData.m_XIndexNum = m_StageIndexData.m_XIndexNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_RIGHT:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YIndexNum = m_StageIndexData.m_YIndexNum;
			checkIndexData.m_XIndexNum = m_StageIndexData.m_XIndexNum + count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_LEFT:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YIndexNum = m_StageIndexData.m_YIndexNum;
			checkIndexData.m_XIndexNum = m_StageIndexData.m_XIndexNum - count;
			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YIndexNum, checkIndexData.m_XIndexNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
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
