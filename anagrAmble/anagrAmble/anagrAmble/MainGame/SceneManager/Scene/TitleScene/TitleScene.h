//==================================================================================================================================//
//!< @file		TitleScene.h
//!< @brief		TitleSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_TITLE_SCENE_H
#define AR_TITLE_SCENE_H

#include "../Scene.h"

namespace ar
{

class TitleBackground;
class TitleText;
class TitleMenu;

//======================================================================//
//!< anagrAmbleにおけるタイトルシーンのクラス
//======================================================================//
class TitleScene : public Scene
{

public:
	/** Constructor */
	TitleScene(void);

	/** Destructor */
	virtual ~TitleScene(void);

private:
	TitleBackground*		m_pBackground;			//!< TitleBackgroundクラスのインスタンスへのポインタ
	TitleText*				m_pText;				//!< TitleTextクラスのインスタンスへのポインタ
	TitleMenu*				m_pMenu;				//!< TitleMenuクラスのインスタンスへのポインタ 

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};

}	// namespace ar

#endif	// AR_TITLE_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
