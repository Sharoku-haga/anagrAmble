//==================================================================================================================================//
//!< @file		SandwichedStageSpace.h
//!< @brief		ar::SandwichedStageSpaceクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SANDWICHED_STAGE_SPACE_H
#define AR_SANDWICHED_STAGE_SPACE_H

#include <vector>
#include "../../../Stage.h"

namespace sl
{

class ISharokuLibrary;

}

namespace ar
{

class EventListener;
class StageDataManager;
class CollisionManager;
class Player;
class Anchor;
class SandwichedSpaceBackground;
class SandwichedStageSpaceObj;

//======================================================================//
//!< ゲームにおいてプレイヤーのアンカーで挟んだ空間を管理するクラス
//======================================================================//
class SandwichedStageSpace
{

public:
	/** 
	* Constructor 
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] pPlayer			オーナーとして登録するPlayerクラスのインスタンスへのポインタ
	*/
	SandwichedStageSpace(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
						, Player*	pPlayer);

	/** Destructor */
	~SandwichedStageSpace(void);

	/** 
	* アンカーで挟んだ空間内のデータを初期化する関数 
	* アンカーが2つ設置されたらよばれる関数
	* @param[in] pAnchorOne 空間を挟んだアンカーのその1
	* @param[in] pAnchorTwo 空間を挟んだアンカーのその2
	*/
	void InitializeData(Anchor* pAnchorOne, Anchor*	pAnchorTwo);

	/**
	* アンカーで挟んだ空間内のデータを破棄する関数
	* アンカーが回収されたら呼ばれる関数
	*/
	void DiscardData(void);

	/**
	* コントロール関数
	* イベント処理を行う
	*/
	void Control(void);

	/** 
	* 描画関数
	* 描画処理を行う
	*/
	void Draw(void);

private:
	sl::ISharokuLibrary*										m_pLibrary;					//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	EventListener*												m_pEventListener;				//!< EventListenerクラスのインスタンスへのポインタ
	StageDataManager*											m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*											m_pCollisionManager;		//!< CollisionManagerクラスのインスタンスへのポインタ
	Player*														m_pPlayer;					//!< Playerクラスのインスタンスへのポインタ
	SandwichedSpaceBackground*									m_pBackground;				//!< SandwichedSpaceBackgroundクラスのインスタンスへのポインタ
	std::vector<SandwichedStageSpaceObj*>						m_pObjs;					//!< SandwichedStageSpaceObjクラスのインスタンスへのポインタのvector
	Stage::INDEX_DATA											m_StartIndex;				//!< 挟んだ空間の開始インデックスデータ
	Stage::INDEX_DATA											m_EndIndex;					//!< 挟んだ空間の終了インデックスデータ
	float														m_StageChipSize;			//!< ステージチップのサイズ

	/** 
	* イベント処理関数.
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	void HandleEvent(void);

	/** 挟んだ空間内のオブジェクトを生成する関数 */
	void CreateSandwichedObj(void);

	/**
	* 空間全体を動かす関数.コールバック関数
	* "player_move"のイベントがおこった際に呼ばれる
	*/
	void Move(void);

	/**
	* 空間入れ替えの為の準備を行う関数.コールバック関数
	* "space_change_start"のイベントがおこった際によばれる
	*/
	void PrepareSpaceChange(void);

	/** 挟んだ空間に挟む効果を適用する関数 */
	void ApplySandwichEffect(void);

	/** 挟んだ空間の挟む効果をきる関数 */
	void DetachSandwichEffect(void);

};	// class SandwichedStageSpace

}	// namespace ar

#endif	// AR_SANDWICHED_STAGE_SPACE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
