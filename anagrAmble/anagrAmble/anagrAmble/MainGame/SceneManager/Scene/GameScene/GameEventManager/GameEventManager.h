﻿//==================================================================================================================================//
//!< @file		GameEventManager.h
//!< @brief		ar::GameEventManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//


#ifndef AR_GAME_EVENT_MANAGER_H
#define AR_GAME_EVENT_MANAGER_H

#include <string>
#include <map>
#include <deque>
#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class EventLisner;

//======================================================================//
//!< ゲームシーンのイベントを管理するクラス
//!< @attention イベントは全て小文字のアルファベットで登録すること
//======================================================================//
class GameEventManager
{

public:
	
	/**
	* 実体取得関数
	* @return GameEventManagerのインスタンス
	*/
	static GameEventManager& Instance(void) 
	{
		static GameEventManager eventManager;
		return eventManager;
	}

	/** 
	* イベント初期化関数 
	* 登録しているイベント、及びそれに対応するLisnerを全て削除し、初期化する関数
	*/
	void InitEventType(void);

	/**
	* 更新関数
	* 毎フレームをよんで、イベントをチェック、処理する関数
	*/
	void Update(void);

	/*
	* イベントタイプとそれに対応するリスナーを登録する関数
	* なおイベントタイプが登録されていない場合は自動的に追加する
	* @param[in] eventType	登録したいイベントタイプ or Lisnerが登録したいイベントタイプ
	* @param[in] pLisner	上記のイベントタイプに登録したいEventLisnerクラスのインスタンスへのポインタ
	*/
	void RegisterEventType(std::string eventType, EventLisner* pLisner); 

	/*
	* 現在登録しているイベントタイプを削除する関数
	* @param[in] eventtype 削除したいイベントタイプ
	*/
	void DelEventType(std::string eventType);

	/**
	* 同期的なイベントをLisnerに発信する関数
	* @param[in] eventtype 発信したいイベントタイプ
	*/
	void TriggerSynEvent(std::string eventType);  

	/**
	* ゲーム中で発生したイベントを受け取る関数
	* @param[in] eventtype 発生したイベントタイプ
	*/
	void ReceiveEvent(std::string eventType);  
   
	/** Destructor */
	~GameEventManager(void);

private:
	std::map<std::string, std::vector<EventLisner*> >  m_EventType;			//!< 登録しているイベントタイプとそれに対応するリスナーのポインタ群
	std::deque<std::string>							   m_CuurentEvent;		//!< 現在ゲーム中で発生したイベントを格納しておくdeque
	
	/** Constructor */
	GameEventManager(void) =default;

	/** コピー禁止 */	
	SL_DISALLOW_COPY_AND_ASSIGN(GameEventManager);


};	// class GameEventManager

}	// namespace ar

#endif	//AR_GAME_EVENT_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
