//==================================================================================================================================//
//!< @file		EventListener.h
//!< @brief		ar::EventListenerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_EVENT_LISTENER_H
#define AR_EVENT_LISTENER_H

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
class EventListener
{

public:
	/** Constructor */
	EventListener(void);

	/** Destructor */
	~EventListener(void);

	/**
	* 同期イベントの処理を登録する関数
	* @param[in] rEventType					同期イベントのタイプ
	* @param[in] rCallBackFunc				同期イベントの際によびだすコールバック関数
	*/
	void RegisterSynEventFunc(const std::string& rEventType, const std::function<void(void)>& rCallBackFunc);

	/** 
	* イベントマネージャーからイベントを受け取る関数
	* @param[in] rEventType		イベントマネージャーから受け取ったイベントのタイプ
	*/
	void ReceiveEvent(const std::string& rEventType); 

	/** 受けとっていたイベントを全て削除する関数 */
	void DelEvent(void); 
	
	/** 
	* 同期イベントの処理を行う関数
	* @param[in] rEventType		処理を行うイベントのタイプ
	*/
	void HandleSynEvent(const std::string& rEventType);  

	/**
	* イベントが現在空なのか、もしくはあるのか確認する関数
	* @return 結果 true→空である false→空でない
	*/
	inline bool EmptyCurrentEvent(void) { return m_CuurentEvent.empty(); }

	/**
	* Getter
	* 現在受け取っているイベントを取得する関数
	*/
	const std::deque<std::string>& GetEvent(void) { return m_CuurentEvent; };

private:
	std::deque<std::string>									m_CuurentEvent;					//!< 現在ゲーム中で発生したイベントを格納しておくdeque
	std::map<std::string, std::function<void(void)>>		m_SynEventFunc;					//!< 同期イベント処理を格納しておくmap

};	// class EventListener

}	// namespace ar

#endif	// AR_EVENT_LISTENER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
