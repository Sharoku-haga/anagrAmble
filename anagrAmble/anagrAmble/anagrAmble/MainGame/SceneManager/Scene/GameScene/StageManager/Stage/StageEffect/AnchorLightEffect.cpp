//==================================================================================================================================//
//!< @file		AnchorLightEffect.cpp
//!< @brief		ar::AnchorLightEffectクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "AnchorLightEffect.h"
#include "../ObjBase/Player/Anchor.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float  EffectWidth			= 24.f;					//!< エフェクトの横の大きさ
const float  HeightCorrectionVal	= 288.f;				//!< 縦の大きさの補正値
const float	 MoveSpeed				= 4.8f;					//!< 動くスピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

AnchorLightEffect::AnchorLightEffect(Anchor* pOwner, Anchor* pOwnerPairAnchor, float stageHeight, int texID)
	: m_TexID(texID)
	, m_StageHeight(stageHeight)
	, m_pOwnerAnchor(pOwner)
	, m_pOwnerPairAnchor(pOwnerPairAnchor)
	, m_CurrentState(PLACED_PLAYER_FRONT)
	, m_MovingLightPos({0.0f, 0.0f})
	, m_MovingRenge(0.0f)
	, m_CurrentMoveSpeed(0.0f)
{}

AnchorLightEffect::~AnchorLightEffect(void)
{
	m_pLibrary->ReleaseVertex2D(m_VtxID[MOVING_LIGHT]);
	m_pLibrary->ReleaseVertex2D(m_VtxID[NORMAL_LIGHT]);
}

void AnchorLightEffect::Initialize(void)
{
	m_Pos = m_MovingLightPos = m_pOwnerAnchor->GetPos();

	m_RectSize.m_Left		= -(EffectWidth / 2);
	m_RectSize.m_Top		= -(m_StageHeight + HeightCorrectionVal);
	m_RectSize.m_Right		= (EffectWidth / 2);;
	m_RectSize.m_Bottom		= m_StageHeight;

	m_VtxID.resize(TYPE_ID_MAX);
	m_UVAnimeID.resize(TYPE_ID_MAX);

	// 通常状態のVeretx作成
	{
		sl::fRect		uv = { 0.916f, 0.0f, 0.933f, 1.0f };
		m_VtxID[NORMAL_LIGHT] = m_pLibrary->CreateVertex2D(m_RectSize, uv);

		// 透明度を下げておく
		m_pLibrary->SetVtxColor(m_VtxID[NORMAL_LIGHT], 1.0f, 1.0f, 1.0f, 0.5f);

		m_UVAnimeID[NORMAL_LIGHT] = m_pLibrary->RegisterUVAnimeID(m_VtxID[NORMAL_LIGHT], 5, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT], 5, 0, uv, 5);
	}

	// 動いている状態のVertx作成
	{
		sl::fRect		uv = { 0.916f, 0.0f, 0.933f, 1.0f };
		m_VtxID[MOVING_LIGHT] = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}
}

void AnchorLightEffect::ChangeStagePos(sl::SLVECTOR2 pos)
{
	m_Pos = m_MovingLightPos = pos;
	m_CurrentState = PLACED_PLAYER_FRONT;
	m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void AnchorLightEffect::RunPlacedPlayerFrontState(void)
{
	m_Pos = m_MovingLightPos = m_pOwnerAnchor->GetPos();

	if(m_pOwnerAnchor->GetHasPlacePosStage())
	{	// どちらのアンカーもおかれたらPLACED_STAGEに変更する
		m_CurrentState = PLACED_STAGE;
	}
}

void AnchorLightEffect::RunPlacedStageState(void)
{
	m_pLibrary->UpdateUVAnime(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);

	if(RESULT_FAILED(m_pOwnerAnchor->GetHasPlacePosStage()))
	{	// オーナーのアンカーがおかれていなかったら、PLACED_PLAYER_FRONTに変更する
		m_CurrentState = PLACED_PLAYER_FRONT;
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);
		return;
	}

	if(m_pOwnerAnchor->GetHasPlacePosStage()
		&& m_pOwnerPairAnchor->GetHasPlacePosStage())
	{	// どちらのアンカーもおかれたらSANDWICHED_SPACEに変更する
		m_CurrentState = SANDWICHED_SPACE;

		float ownerAnchorPosX = m_pOwnerAnchor->GetPos().x;
		float ownerPairAnchorPosX = m_pOwnerPairAnchor->GetPos().x;
		
		// 位置によって動く範囲を決める
		// 動く範囲は、アンカーの間の半分の距離
		if(ownerAnchorPosX > ownerPairAnchorPosX)
		{	// オーナーアンカーの方が座標が大きい場合は後ろに動く
			m_CurrentMoveSpeed = -MoveSpeed;
			m_MovingRenge = ((ownerPairAnchorPosX - ownerAnchorPosX) / 2.0f);
		}
		else
		{	// オーナーアンカーの方が座標が小さい場合は前に動く
			m_CurrentMoveSpeed = MoveSpeed;
			m_MovingRenge = ((ownerPairAnchorPosX - ownerAnchorPosX) / 2.0f);
		}
	}
}

void AnchorLightEffect::RunSandwichedSpaceState(void)
{
	m_pLibrary->UpdateUVAnime(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);

	if(RESULT_FAILED(m_pOwnerAnchor->GetHasPlacePosStage())
		|| RESULT_FAILED(m_pOwnerPairAnchor->GetHasPlacePosStage()))
	{	// どちらのアンカーのアンカーが取り除かれたらPLACED_PLAYER_FRONTに変更し、座標もアンカーに戻す
		m_CurrentState = PLACED_PLAYER_FRONT;
		m_Pos = m_MovingLightPos = m_pOwnerAnchor->GetPos();
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);
		return;
	}

	if(m_pOwnerAnchor->GetHasPlacePosStage()
		&& RESULT_FAILED(m_pOwnerPairAnchor->GetHasPlacePosStage()))
	{	// オーナーのペアであるアンカーが取り除かれたらPLACED_STAGEに変更し、座標もアンカーに戻す
		m_CurrentState = PLACED_STAGE;
		m_Pos = m_MovingLightPos = m_pOwnerAnchor->GetPos();
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[NORMAL_LIGHT], m_UVAnimeID[NORMAL_LIGHT]);
	}

	if(m_CurrentMoveSpeed > 0)
	{
		if(m_MovingLightPos.x  < (m_MovingRenge + m_Pos.x))
		{
			m_MovingLightPos.x += m_CurrentMoveSpeed;
		}
		else
		{
			m_MovingLightPos = m_Pos;
		}
	}
	else
	{
		if(m_MovingLightPos.x  > (m_MovingRenge + m_Pos.x))
		{
			m_MovingLightPos.x += m_CurrentMoveSpeed;
		}
		else
		{
			m_MovingLightPos = m_Pos;
		}
	}
}

void AnchorLightEffect::Run(void)
{
	switch(m_CurrentState)
	{
	case PLACED_PLAYER_FRONT:
		RunPlacedPlayerFrontState();
		break;

	case PLACED_STAGE:
		
		RunPlacedStageState();
		break;

	case SANDWICHED_SPACE:
		RunSandwichedSpaceState();
		break;

	default:
		// do nothing
		break;
	}
}

void AnchorLightEffect::Render(void)
{
	sl::DrawingID	drawingID;
	drawingID.m_TexID = m_TexID;

	switch(m_CurrentState)
	{
	case PLACED_PLAYER_FRONT:
		break;

	case PLACED_STAGE:
		break;

	case SANDWICHED_SPACE:
		drawingID.m_VtxID = m_VtxID[MOVING_LIGHT];
		m_pLibrary->Draw2D(drawingID, (m_MovingLightPos - m_BasePointPos));
		break;

	default:
		// do nothing
		break;
	}

	drawingID.m_TexID = m_TexID;
	drawingID.m_VtxID = m_VtxID[NORMAL_LIGHT];
	m_pLibrary->Draw2D(drawingID, (m_Pos - m_BasePointPos));
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
