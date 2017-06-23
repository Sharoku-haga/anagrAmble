//==================================================================================================================================//
//!< @file		slUVAnimationManager.h	
//!< @brief		sl::UVAnimationManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_UV_ANIMATION_MANAGER_H
#define SL_UV_ANIMATION_MANAGER_H

#include <map>
#include <vector>
#include "../../Common/slStruct.h"

namespace sl
{

class UVAnimation;

//======================================================================//
//!< UVAnimationクラスを管理するクラス
//======================================================================//
class UVAnimationManager
{
public:
	/** Constructor */
	UVAnimationManager(void);

	/** Destructor */
	~UVAnimationManager(void);

	/** 
	* アニメーションを登録する関数
	* @param[in] vtxID			アニメーションと紐づけしたいバーテックスのID
	* @param[in] patternCount	アニメーションのパターン数
	* @param[in] repeat			アニメーションを繰り返すかどうかのフラグ true→繰り返す false→繰り返さない デフォルトはfalse
	* @return 登録したのアニメーションID
	*/
	int RegisterAnimationID(int vtxID, int patternCount, bool repeat = false);

	/** 
	* UVアニメーションを生成する関数
	* @param[in] vtxID				バーテックスのID
	* @param[in] animeID			アニメーションのID
	* @param[in] tuCount			tu方向のカウント数
	* @param[in] tvCount			tv方向のカウント数
	* @param[in] rBasicUV			基本となるUV値. この値を基本として増やして行く
	* @param[in] dispFlameCount		アニメーションの表示フレーム数
	*/
	void CreateUVAnimationData(int vtxID, int animeID, int tuCount, int tvCount
							, const sl::fRect& rStartUVVal, int dispFlameCount);

	/**
	* アニメーション更新関数
	* UVアニメーションを更新する関数.
	* @param[in] vtxID		アニメーションを更新したいバーテックスのID
	* @param[in] animeID	更新したいアニメーションのID
	* @return アニメーションが更新したかどうか true→更新した false→更新していない.
	*/
	bool UpdateUVAnimation(int vtxID, int animeID);

	/**
	* アニメーションを初期状態に戻す関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	*/
	void ReturnUVAnimeInitialState(int vtxID, int animeID);

	/**
	* 現在のアニメーションが最後の番号かどうか確認する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @return アニメーションが最後の番号かどうか true→最後の番号である false →最後の番号でない 
	*/
	bool CheckLastNumCurrnttAnime(int vtxID, int animeID);

	/**
	* Getter 現在のアニメのUV値を取得する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @return 現在のアニメーションのUV値
	*/
	const sl::fRect& GetCurrentAnimeUV(int vtxID, int animeID);

	/**
	* Setter UVアニメーションデータを設定する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @param[in] index				設定したいm_AnimeDataのインデックス
	* @param[in] rUV				設定したいUV値
	* @param[in] dispFlameCount		設定したいアニメーションを表示するフレーム数
	*/
	void SetAnimeData(int vtxID, int animeID, int index,  const sl::fRect& rUV, int dispFlameCount);

	/**
	* Setter UVアニメーションの順番を設定する関数
	* @param[in] vtxID			バーテックスのID
	* @param[in] animeID		アニメーションのID
	* @param[in] rAnimeOrder	アニメーションの順番を格納している配列
	*/
	void SetAnimeOrder(int vtxID, int animeID, const std::vector<int>& rAnimeOrder);

private:
	std::map<int, std::vector<UVAnimation*>>		m_pUVAnimations;			//!< VertexIDをキーとしたUVAnimationクラスのインスタンスへのポインタの配列(vector)を格納したmap

};

}	// namespace sl

#endif	// SL_UV_ANIMATION_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
