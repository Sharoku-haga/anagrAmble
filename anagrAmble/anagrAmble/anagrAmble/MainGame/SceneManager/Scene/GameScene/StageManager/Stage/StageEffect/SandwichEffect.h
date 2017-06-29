//==================================================================================================================================//
//!< @file		SandwichEffect.h
//!< @brief		SandwichEffectクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SANDWICH_EFFECT_H
#define AR_SANDWICH_EFFECT_H

#include "StageEffect.h"

namespace ar
{

//======================================================================//
//!< ゲーム中の挟んでいる効果のクラス
//======================================================================//
class SandwichEffect : public StageEffect
{

public:
	/** 
	* Constructor
	* @param[in] rOwnerPos		オーナーの位置座標
	* @param[in] rRectSize		矩形サイズ
	* @param[in] rOwnwerID		オーナーの描画ID群	
	* @param[in] stageChipSize	ステージチップサイズ
	*/
	SandwichEffect(const sl::SLVECTOR2& rOwnerPos, const sl::fRect rRectSize 
					, const  sl::DrawingID& rOwnerID,  float stageChipSize);

	/** Destructor */
	virtual ~SandwichEffect(void);

	/** 
	* 挟む効果を開始する前の処理関数
	* @param[in] rSandwichedSpaceCenterPos 挟まれた空間の中心座標
	*/
	void ProcessBeforeEffectStart(const sl::SLVECTOR2& rSandwichedSpaceCenterPos);

	/** 
	* UVを変更する関数
	* オーナーのオブジェクトでよぶ関数
	* オーナーのUV情報が変わった場合によぶ
	*/
	void ChangeUV(void);

	/**
	* 挟む効果が終わったかどうかのフラグを確認する関数
	* @return 結果 true→終了 false→継続 
	*/
	bool EndEffect(void) { return m_EndEffect; }

	/**
	* Getter.この効果を現在反映している挟まれた空間の中心座標を取得する関数
 	* オブジェクトの子クラスに挟む効果を反映させるため使用
	*/
	const sl::SLVECTOR2& GetSandwichedSpaceCenterPos(void) { return m_SandwichedSpaceCenterPos; }

	/**
	* Setter.オーナーの位置座標をセットする関数
 	* オブジェクトの子クラスに挟む効果を反映させるため使用
	*/
	void SetOwnerPos(const sl::SLVECTOR2& rOwnerPos) { m_OwnerPos = rOwnerPos; }

	/** 初期化関数 */
	virtual void Initialize(void)override;

	/** 
	* ステージの位置を変更する関数 
	* @param[in] rPos	変更したい位置座標
	*/
	virtual void ChangeStagePos(const sl::SLVECTOR2& rPos);

private:
	sl::SLVECTOR2		m_OwnerPos;							//!< この効果のオーナーの座標
	sl::SLVECTOR2		m_SandwichedSpaceCenterPos;			//!< 挟まれた空間の中心座標
	sl::fRect			m_BasicRectSize;					//!< 基本となる矩形サイズ
	sl::DrawingID		m_DrawingID;						//!< 描画ID群 
	sl::DrawingID		m_OwnerID;							//!< この効果のオーナーの描画ID
	float				m_StageChipSize;					//!< ステージのチップサイズ
	float				m_EffectSpeed;						//!< 挟む効果のスピード
	bool				m_EndEffect;						//!< 挟む効果が終了したかどうかのフラグ true→終了 false→継続					

	
	/** 
	* 処理実行関数.純粋仮想関数 
	* Control()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数. 
	* Draw()内で使用する
	*/
	virtual void Render(void)override;

};	// class SandwichEffect 

}	// namespace ar

#endif	// AR_SANDWICH_EFFECT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
