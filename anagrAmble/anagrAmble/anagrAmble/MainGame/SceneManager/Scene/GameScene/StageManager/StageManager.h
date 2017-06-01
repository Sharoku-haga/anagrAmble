//==================================================================================================================================//
//!< @file		StageManager.h
//!< @brief		ar::StageManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_MANAGER_H
#define AR_STAGE_MANAGER_H

namespace ar
{

class GameDataManager;
class StageDataManager;
class Stage;

//======================================================================//
//!< ステージ関連を管理するクラス
//======================================================================//
class StageManager
{

public:
	/** 
	* Constructor
	* @param[in] pGameDataManager GameDataManagerクラスのインスタンスへのポインタ 
	*/
	explicit StageManager(GameDataManager*	pGameDataManager);

	/** Destructor */
	~StageManager(void);

	/** コントロール関数 */
	void Contorl(void);

	/** 描画関数 */
	void Draw(void);

private:
	enum STATE
	{
		STAGE_INIT,		//!< ステージ初期化
		STAGE_RUN,		//!< ステージ処理実行
	};

	GameDataManager*	m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	StageDataManager*	m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	Stage*				m_pStage;					//!< Stageクラスのインスタンスへのポインタ
	STATE				m_CurrentState;				//!< 現在の状態

};	// class StageManager

} // namespace ar

#endif	// AR_STAGE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
