#pragma once

#include "SceneManager.h"

class myGame
{
public:
	myGame(SceneManager& scene);

	void exec();

private:
	SceneManager* m_sceneManager;
};