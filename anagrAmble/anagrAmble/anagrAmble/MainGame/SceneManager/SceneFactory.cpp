//==================================================================================================================================//
//!< @file		SceneFactory.cpp
//!< @brief		ar::SceneFactoryクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SceneFactory.h"
#include "GameDataManager/GameDataManager.h"
#include "Scene/LogoScene/LogoScene.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/GameScene/GameScene.h"
#include "Scene/GameClearScene/GameClearScene.h"
#include "Scene/GameOverScene/GameOverScene.h"
#include "Scene/CreditsRollScene/CreditsRollScene.h"

namespace ar
{

/* Static Variable -------------------------------------------------------------------------------------------- */

GameDataManager*		SceneFactory::m_pGameDataManager = nullptr;

/* Public Functions ------------------------------------------------------------------------------------------- */

void SceneFactory::Initialize(GameDataManager*	pGameDataManager)
{
	m_pGameDataManager = pGameDataManager;
}

Scene* SceneFactory::CreateScene(Scene::ID id)
{
	Scene* pScene = nullptr;

	switch(id)
	{

	case Scene::LOGO:
		pScene = new LogoScene();
		break;

	case Scene::TITLE:
		pScene = new TitleScene();
		break;

	case Scene::GAME:
		pScene = new GameScene(m_pGameDataManager);
		break;

	case Scene::GAME_CLEAR:
		pScene = new GameClearScene(m_pGameDataManager);
		break;

	case Scene::GAME_OVER:
		pScene = new GameOverScene();
		break;

	case Scene::CREDITS_ROLL:
		pScene = new CreditsRollScene();
		break;

	case Scene::END:
		// do nothing
		break;

	default:
		// do nothing
		break;
	}
	return pScene;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
