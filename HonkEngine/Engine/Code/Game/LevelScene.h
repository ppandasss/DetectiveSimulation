#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"
#include"../AnimateGameObject.h"	

#include "../Player.h"

class LevelScene : public Scene
{
public:
	LevelScene()
	{ 
		//RenderGameObject* boss = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
		//GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");
		Player* Bus = new Player("Bus", "Assets/Images/spritesheet_test.png",4.0f,4.0f);
		
		
		
		//boss->SetOrientation(1.7);
		//m_gameObjects.push_back(cabin);
		//m_gameObjects.push_back(boss);
		m_gameObjects.push_back(Bus);
	}
};