//==================================================================================================================================//
//!< @file		StageEffect.h
//!< @brief		ar::StageEffectクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_EFFECT_H
#define AR_STAGE_EFFECT_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< ステージに存在するオブジェクトの基底クラス
//======================================================================//
class StageEffect
{

public:
	/** Constructor */
	StageEffect(void);

	/** Destructor */
	~StageEffect(void) = default;

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/**
	* 初期化関数. 純粋仮想関数
	* 座標などをここで設定する
	*/
	virtual void Initialize(void) = 0;

	/** 
	* Setter ベースポイントの位置座標をセットする関数.static
	* @param[in]  basePoitPos ベースポイントの位置座標
	*/
	static void SetBasePointPos(const sl::SLVECTOR2 basePointPos) { m_BasePointPos = basePointPos; }

	/** 
	* Setter 表示している画面範囲をセットする関数.static
	* @param[in] displayWidth	画面の横サイズ
	* @param[in] displayHeight	画面の縦サイズ
	*/
	static void SetDisplayArea(float displayWidth, float displayHeight)
	{
		m_DisplayArea.m_Right = displayWidth;
		m_DisplayArea.m_Bottom = displayHeight;
	}

private:
	static	sl::SLVECTOR2	m_BasePointPos;					//!< ベースポイントの位置座標.static
	static  sl::fRect		m_DisplayArea;					//!< 画面範囲.static

	sl::ISharokuLibrary*	m_pLibrary;						//!< sl::ISharokuLibrary*クラスのインスタンスへのポインタ
	sl::SLVECTOR2			m_Pos;							//!< 位置座標
	sl::fRect				m_RectSize;						//!< 基本矩形サイズ

	/** 
	* 処理実行関数.純粋仮想関数 
	* Control()内で使用
	*/
	virtual void Run(void) = 0;

	/** 
	* 描画関数.純粋仮想関数 
	* Draw()内で使用する
	*/
	virtual void Render(void) = 0;
};

}	// namespace ar

#endif	// AR_STAGE_EFFECT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
