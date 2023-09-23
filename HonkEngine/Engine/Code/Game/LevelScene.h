#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"

#include "../Player.h"

class LevelScene : public Scene
{
public:
	LevelScene()
	{ 
		//RenderGameObject* boss = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
		//GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");
		Player* Bus = new Player("Bus", "Assets/Images/spritesheet_test.png",4.0f,4.0f);
		
		
		Bus->SetScale({ 0.2, 0.2, 0 });
		//boss->SetOrientation(1.7);
		//m_gameObjects.push_back(cabin);
		//m_gameObjects.push_back(boss);
		AddGameObject(Bus);
	}
};