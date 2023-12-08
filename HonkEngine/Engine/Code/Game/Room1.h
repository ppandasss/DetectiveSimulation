
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
	
		//Player* Joph = new Player("Bus", "Assets/Images/spritesheet_test2.png", 4.0f, 4.0f);
	

		/*---------JOURNAL SPRITES NON - UI------------------*/
		GameObject* journalCover = new RenderGameObject("Cover", "Assets/Images/journalcover.png");
		journalCover->SetScale(glm::vec3(1.5f, 1.5f, 1.0f));
		m_gameObjects.push_back(journalCover);

		GameObject* journalPage = new RenderGameObject("Cover", "Assets/Images/journalblankpages.png");
		journalPage->SetScale(glm::vec3(1.4f, 1.4f, 1.0f));
		m_gameObjects.push_back(journalPage);

		/*-----------------JOURNAL UI-----------------------*/

		//UIManager* uiManager = new UIManager();
		

		UIElement* journalButton = new UIButton("Button 1", "Assets/Images/journalticket.png", glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f), UIElement::IN_GAME);
		m_gameObjects.push_back(journalButton);
		journalButton->SetClickable(true);


	}
};