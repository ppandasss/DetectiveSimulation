#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"
#include "../AnimGameObject.h"
#include "../Player.h"

class LevelScene : public Scene
{
public:
	LevelScene()
	{
		Player* boss = new Player("Boss", "Assets/Images/spritesheet_test.png");
		GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");

		
		cabin->SetScale({ 2,2,0 });
		boss->SetPosition({ 0, -0.8, 0 });
		boss->SetScale({ 0.5, 0.5, 0 });
		//boss->SetOrientation(1.7);
		m_gameObjects.push_back(cabin);
		m_gameObjects.push_back(boss);

		
	
		
	}
};