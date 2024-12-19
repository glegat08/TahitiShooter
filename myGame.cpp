#include "myGame.h"

myGame::myGame(SceneManager& scene)
	: m_sceneManager(&scene)
{
}

void myGame::exec()
{
	m_sceneManager->exec();
}