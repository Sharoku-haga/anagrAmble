//==================================================================================================================================//
//!< @file		slUVAnimation.h
//!< @brief		sl::UVAnimationクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_UV_ANIMATION_H
#define SL_UV_ANIMATION_H

#include <vector>
#include "../../Common/slStruct.h"

namespace sl
{

//======================================================================//
//!< UVアニメーションを管理するクラス
//======================================================================//
class UVAnimation
{

public:
	/** 
	* Constructor
	* この中でアニメーション順番も先頭から順に値をいれている
	* @param[in] patternCount		アニメーションのパターン数
	* @param[in] repeat				アニメーションを繰り返すかどうかのフラグ true→繰り返す false→繰り返さない デフォルトはfalse
	*/
	UVAnimation(int patternCount, bool repeat = false);

	/** Destructor */
	~UVAnimation(void);

	/**
	* UVアニメーションのデータを作成する関数 
	* 引数で渡されたUV間隔をもとにアニメーションを作成していく関数
	* @param[in] tuCount			tu方向のカウント数
	* @param[in] tvCount			tv方向のカウント数
	* @param[in] rBasicUV			基本となるUV値. この値を基本として増やして行く
	* @param[in] dispFlameCount		アニメーションの表示フレーム数
	*/
	void CreateAnimeData(int tuCount, int tvCount, const sl::fRect& rStartUVVal, int dispFlameCount);

	/**
	* アニメーション更新関数
	* UVアニメーションを更新する関数.
	* @return アニメーションが更新したかどうか true→更新した false→更新していない.
	*/
	bool Upadate(void);

	/**
	* アニメーションを初期状態に戻す関数
	*/
	void ReturnInitialState(void);

	/**
	* 現在のアニメーションが最後の番号かどうか確認する関数
	* @return アニメーションが最後の番号かどうか true→最後の番号である false →最後の番号でない 
	*/
	bool CheckLastNumCurrnttAnime(void);

	/**
	* Getter 現在のアニメのUV値を取得する関数
	* @return 現在のアニメーションのUV値
	*/
	const sl::fRect& GetCurrentAnimeUV(void)const { return m_CurrentAnimeData.m_UV; }

	/**
	* Setter UVアニメーションデータを設定する関数
	* @param[in] index				設定したいm_AnimeDataのインデックス
	* @param[in] rUV				設定したいUV値
	* @param[in] dispFlameCount		設定したいアニメーションを表示するフレーム数
	*/
	void SetAnimeData(int index,  const sl::fRect& rUV, int dispFlameCount);

	/**
	* Setter UVアニメーションの順番を設定する関数
	* @param[in] rAnimeOrder	アニメーションの順番を格納している配列
	*/
	void SetAnimeOrder(const std::vector<int>& rAnimeOrder);

private:
	/** アニメデータの構造体 */
	struct AnimeData
	{
		sl::fRect	m_UV;					//!< UV値
		int			m_DispFlameCount;		//!< アニメーションを表示するフレーム
		AnimeData(const sl::fRect& rUV, int dispFlameCount)
			: m_UV(rUV)
			, m_DispFlameCount(dispFlameCount)
		{}
	};

	std::vector<AnimeData>		m_AnimeData;				//!< アニメデータを格納している配列(vector)
	std::vector<int>			m_AnimeOrder;				//!< アニメーションの順番を格納している配列(vector)
	int							m_AnimePatternCount;		//!< アニメーションのパターン数
	int							m_CurrentAnimeOrderNum;		//!< 現在のアニメーションの順番の番号
	int							m_CurentDispFlameCount;		//!< 現在のアニメーションを表示しているフレームカウント数
	AnimeData					m_CurrentAnimeData;			//!< 現在のアニメデータ
	bool						m_Repeat;					//!< アニメーションを繰り返すかどうかのフラグ true→繰り返す false→繰り返さない 

};	// class UVAnimation

}	// namespace sl

#endif // SL_UV_ANIMATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
