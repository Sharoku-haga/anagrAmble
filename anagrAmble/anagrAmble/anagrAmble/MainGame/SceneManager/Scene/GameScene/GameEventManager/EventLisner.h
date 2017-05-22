//==================================================================================================================================//
//!< @file		EventLisner.h
//!< @brief		ar::EventLisnerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_EVENT_LISNER_H
#define AR_EVENT_LISNER_H

#include <string>
#include <deque>
#include <map>
#include <functional>

namespace ar
{

//======================================================================//
//!< イベントマネージャーからイベントを受け取り、
//!< そのイベントを別クラスに通知するクラス
//!< また同期イベントが通知された際は
//!< 登録されたイベント関数で処理を行う
//======================================================================//
class EventLisner
{

public:
	/** Constructor */
	EventLisner(void);

	/** Destructor */
	~EventLisner(void);

	/**
	* 同期イベントの処理を登録する関数
	* @param[in] eventType					同期イベントのタイプ
	* @param[in] callBackFunc				同期イベントの際によびだすコールバック関数
	*/
	void RegisterSynEventFunc(std::string eventType, std::function<void(void)> callBackFunc);

	/** 
	* イベントマネージャーからイベントを受け取る関数
	* @param[in] eventType		イベントマネージャーから受け取ったイベントのタイプ
	*/
	void ReceiveEvent(std::string eventType); 

	/** 受けとっていたイベントを全て削除する関数 */
	void DelEvent(void); 
	
	/** 
	* 同期イベントの処理を行う関数
	* @param[in] eventType		処理を行うイベントのタイプ
	*/
	void HandleSynEvent(std::string eventType);  

	/**
	* Getter
	* 現在受け取っているイベントを取得する関数
	*/
	const std::deque<std::string>& GetEvent(void) { return m_CuurentEvent; };

private:
	std::deque<std::string>									m_CuurentEvent;					//!< 現在ゲーム中で発生したイベントを格納しておくdeque
	std::map<std::string, std::function<void(void)>>		m_SynEventFunc;					//!< 同期イベント処理を格納しておくmap

};	// class EventLisner

}	// namespace ar

#endif	// AR_EVENT_LISNER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
