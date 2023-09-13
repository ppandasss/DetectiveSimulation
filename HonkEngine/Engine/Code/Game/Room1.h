
#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"
#include "../Player.h"

class Room1 : public Scene
{
public:

	Room1()
	{
	
		GameObject* bank = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");


		
		m_gameObjects.push_back(bank);


	}
};