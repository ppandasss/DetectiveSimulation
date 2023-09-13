#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"
#include "../Player.h"

class LevelScene : public Scene
{
public:
	LevelScene()
	{
		Player* boss = new Player("Boss", "Assets/Images/waiter_test.png");
		GameObject* bank = new RenderGameObject("Boss", "Assets/Images/thomas.jpg");

		
		boss->SetPosition({ 0, -0.5, 0 });
		boss->SetScale({ 0.5, 0.5, 0 });
		//boss->SetOrientation(1.7);
		m_gameObjects.push_back(bank);
		m_gameObjects.push_back(boss);

		
	
		
	}
};