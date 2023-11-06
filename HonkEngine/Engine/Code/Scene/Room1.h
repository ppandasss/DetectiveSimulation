
#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../GameObjects/Player.h"

class Room1 : public Scene
{
public:

	Room1()
	{
	
		//GameObject* bank = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
		Player* Joph = new Player("Bus", "Assets/Images/Matha1.png", 1.0f, 1.0f);

		
		//m_gameObjects.push_back(Joph);


	}
};