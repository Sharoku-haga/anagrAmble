//==================================================================================================================================//
//!< @file		ElectricEffect.h
//!< @brief		ar::ElectricEffectヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ELECTRIC_EFFECT_H
#define AR_ELECTRIC_EFFECT_H

#include "StageEffect.h"

namespace ar
{

//======================================================================//
//!< 通電ブロックに使用するエフェクトのクラス
//======================================================================//
class ElectricEffect : public StageEffect
{

public:
	/** 
	* Constructor
	* @param[in] texID				テクスチャーID
	* @param[in] rRectSize			矩形サイズ
	*/
	ElectricEffect(int texID, const sl::fRect& rRectSize);

	/** Destructor */
	virtual ~ElectricEffect(void);

	/**
	* 初期化関数. 
	* 座標などをここで設定する
	*/
	virtual void Initialize(void)override;

	/** 
	* ステージの位置を変更する関数. 
	* @param[in] pos	変更したい位置座標
	*/
	virtual void ChangeStagePos(const sl::SLVECTOR2& rPos)override;

private:
	sl::DrawingID				m_DrawingID;		//!< 描画関連のID構造体
	int							m_UVAnimeID;		//!< UVアニメID

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

};	// class ElectricEffect

}	// namespace ar

#endif // AR_ELECTRIC_EFFECT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

