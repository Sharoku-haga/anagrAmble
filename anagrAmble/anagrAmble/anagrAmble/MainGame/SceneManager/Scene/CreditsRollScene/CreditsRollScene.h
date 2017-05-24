//==================================================================================================================================//
//!< @file		CreditsRollScene.h
//!< @brief		ar::CreditsRollSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_CREDIT_ROLL_SCENE_H
#define AR_CREDIT_ROLL_SCENE_H

#include "../Scene.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるエンドロールシーンのクラス
//======================================================================//
class CreditsRollScene : public Scene
{

public:
	/** Constructor */
	CreditsRollScene(void);

	/** Destructor */
	~CreditsRollScene(void);

private:
	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};	// class CreditsRollScene

}	// namespace ar 

#endif	// AR_CREDIT_ROLL_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
