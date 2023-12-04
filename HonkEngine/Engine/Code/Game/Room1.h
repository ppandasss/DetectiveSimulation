
#pragma once

#include "../Scene.h"
#include "../RenderGameObject.h"
#include "../Player.h"
#include "../UIManager.h"

class Room1 : public Scene
{
public:

	Room1()
	{
	
		//GameObject* bank = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
		//Player* Joph = new Player("Bus", "Assets/Images/spritesheet_test2.png", 4.0f, 4.0f);
		//m_gameObjects.push_back(Joph);

		//UIManager* uiManager = new UIManager();
		//m_gameObjects.push_back(uiManager);

		UIElement* journalButton = new UIButton("Button 1", "Assets/Images/journalticket.png", glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f), UIElement::IN_GAME);
		m_gameObjects.push_back(journalButton);


	}
};