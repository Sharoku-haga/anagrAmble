//==================================================================================================================================//
//!< @file		LogoScene.h
//!< @brief		ar::LogoSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LOGO_SCENE_H
#define AR_LOGO_SCENE_H

#include "../Scene.h"

namespace ar
{

class LogoBackground;
class LogoText;

//======================================================================//
//!< anagrAmbleにおけるロゴシーンのクラス
//======================================================================//
class LogoScene : public Scene
{
public:
	/** Constructor */
	LogoScene(void);

	/** Destructor */
	virtual ~LogoScene(void);

private:
	LogoBackground*			m_pBackground;			//!< LogoBackgroundクラスのインスタンスへのポインタ
	LogoText*				m_pText;				//!< LogoTextクラスのインスタンスへのポインタ

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};	// class LogoScene 

}	// namespace ar

#endif	// AR_LOGO_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
