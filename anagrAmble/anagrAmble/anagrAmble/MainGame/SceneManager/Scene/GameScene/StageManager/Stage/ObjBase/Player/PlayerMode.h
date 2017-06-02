//==================================================================================================================================//
//!< @file		PlayerMode.h
//!< @brief		ar::PlayerModeクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_PLAYER_MODE_H
#define AR_PLAYER_MODE_H

#include <array>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class StageDataManager;
class CollisionManager;
class Player;
class Anchor;

//======================================================================//
//!< プレイヤーのモードクラス
//!< プレイヤーの3つの形態の操作、また遷移を管理する
//======================================================================//
class PlayerMode
{

public:
	/** 
	* Constructor 
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] pPlayer			オーナーとして登録するPlayerクラスのインスタンスへのポインタ
	* @param[in] texID				テクスチャーID(アンカーのテクスチャー)
	*/
	PlayerMode(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, 
				Player*	pPlayer, int texID);

	/** Destructor */
	~PlayerMode(void);

	/** 
	* コントロール関数
	* アンカーの制御やエリア入れ替えの制御などを行う
	*/
	void Control(void);

	/** 
	* 描画関数
	* アンカーの描画や入れ替えるエリアの描画を行う
	*/
	void Draw(void);

private:
	/** モードの種類ID */
	enum MODE_TYPE
	{
		NORMAL,			//!< 通常モード
		ANCHOR_SET,		//!< アンカーセットを行うモード
		AREA_CHENGE,	//!< エリアの入れ替えを行うモード
	};

	static const int						m_AnchorCount = 2;		//!< アンカーの数

	sl::ISharokuLibrary*					m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	StageDataManager*						m_pStageDataManager;	//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*						m_pCollisionManager;	//!< CollisionManagerクラスのインスタンスへのポインタ
	Player*									m_pPlayer;				//!< このクラスのオーナーであるPlayerクラスのインスタンスへのポインタ
	std::array<Anchor*, m_AnchorCount>		m_pAnchors;				//!< Anchorクラスのインスタンスへのポインタの固定長配列。数がかわることがないので、固定長配列でいく
	MODE_TYPE								m_CurrentModeType;		//!< 現在のモードタイプ

};	// class PlayerMode	

}	// namespace ar

#endif	// AR_PLAYER_MODE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
