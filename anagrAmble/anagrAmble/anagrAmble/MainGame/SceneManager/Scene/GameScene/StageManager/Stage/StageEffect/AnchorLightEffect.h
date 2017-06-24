//==================================================================================================================================//
//!< @file		AnchorLightEffect.h
//!< @brief		ar::AnchorLightEffectクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ANCHOR_LIGHT_EFFECT_H
#define AR_ANCHOR_LIGHT_EFFECT_H

#include <vector>
#include "StageEffect.h"

namespace ar
{

class Anchor;

//======================================================================//
//!< アンカーに使用する光エフェクトのクラス
//======================================================================//
class AnchorLightEffect : public StageEffect
{

public:
	/** 
	* Constructor
	* @param[in] pOwner				オーナーとなるAnchorクラスのインスタンスへのポインタ
	* @param[in] pOwnerPairAnchor	オーナーとペアとなるnchorクラスのインスタンスへのポインタ
	* @param[in] stageHeight		ステージの高さ
	* @param[in] texID				テクスチャーID
	*/
	AnchorLightEffect(Anchor* pOwner, Anchor* pOwnerPairAnchor, float stageHeight, int texID);

	/** Destructor */
	virtual ~AnchorLightEffect(void);

	/**
	* 初期化関数. 
	* 座標などをここで設定する
	*/
	virtual void Initialize(void)override;

	/** 
	* ステージの位置を変更する関数. 
	* @param[in] pos	変更したい位置座標
	*/
	virtual void ChangeStagePos(sl::SLVECTOR2 pos)override;

private:
	/** 状態の種類 */
	enum STATE
	{
		PLACED_PLAYER_FRONT,			//!< プレイヤーの前に置かれている状態
		PLACED_STAGE,					//!< ステージに置かれている状態
		SANDWICHED_SPACE,				//!< 空間を挟んでいる状態
		ID_MAX,
	};

	/** 光の種類 */
	enum TYPE_ID
	{
		NORMAL_LIGHT,			//!< 通常の光エフェクト
		MOVING_LIGHT,			//!< 動いている光のエフェクト
		TYPE_ID_MAX,
	};

	int					m_TexID;					//!< テクスチャーID
	std::vector<int>	m_VtxID;					//!< バーテックスID
	std::vector<int>	m_UVAnimeID;				//!< UVアニメーションID
	float				m_StageHeight;				//!< ステージの高さ
	Anchor*				m_pOwnerAnchor;				//!< オーナーとなるAnchorクラスのインスタンスへのポインタ
	Anchor*				m_pOwnerPairAnchor;			//!< オーナーAnchorのペアとなるAnchorクラスのインスタンスへのポインタ
	STATE				m_CurrentState;				//!< 現在のアンカーの状態

	sl::SLVECTOR2		m_MovingLightPos;			//!< 動くライトの座標
	float				m_MovingRenge;				//!< 動く範囲
	float				m_CurrentMoveSpeed;			//!< 現在の動くスピード

	/**
	* STATEはPLACED_PLAYER_FRONTのときの処理を行う関数
	*/
	void RunPlacedPlayerFrontState(void);

	/**
	* STATEはPLACED_STAGEのときの処理を行う関数
	*/
	void RunPlacedStageState(void);

	/**
	* STATEはSANDWICHED_SPACEのときの処理を行う関数
	*/
	void RunSandwichedSpaceState(void);

	/** 
	* 処理実行関数.
	* Control()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数.
	* Draw()内で使用する
	*/
	virtual void Render(void)override;

};	// class AnchorLightEffect

}	// namespace ar

#endif	// AR_ANCHOR_LIGHT_EFFECT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
