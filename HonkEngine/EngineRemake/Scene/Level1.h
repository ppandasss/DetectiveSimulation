#pragma once

#include "../Code/Scene.h"
#include "../Code/RenderGameObject.h"



class LevelScene : public Scene
{
public:
	LevelScene()
	{
		RenderGameObject* boss = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
		
		m_gameObjects.push_back(boss);
	}
};