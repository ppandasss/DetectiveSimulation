
#pragma once

#include "Scene.h"
#include "../Renderer/Renderer.h"
#include "../GameObjects/Player.h"
#include "../UI/UIManager.h"


class Journal : public Scene
{
public:

	Journal()
	{
		
		//Player* Joph = new Player("Bus", "Assets/Images/spritesheet_test2.png", 4.0f, 4.0f);
	
		
		//camera.Reset();
		//camera.ZoomIn(4.0f);

		/*---------JOURNAL SPRITES NON - UI------------------*/
		GameObject* journalCover = new RenderGameObject("Cover", "Assets/Images/journalcover.png");
		journalCover->SetScale(glm::vec3(6.0f, 6.0f, 1.0f));
		journalCover->SetPosition(glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f));
		
		m_gameObjects.push_back(journalCover);

		GameObject* journalPage = new RenderGameObject("Cover", "Assets/Images/journalblankpages.png");
		journalPage->SetScale(glm::vec3(5.6f, 5.6f, 1.0f));
		journalPage->SetPosition(glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f));
		m_gameObjects.push_back(journalPage);

		/*-----------------JOURNAL UI-----------------------*/

		//UIManager* uiManager = new UIManager();
		

		UIElement* journalButton = new UIButton("Button 1", "Assets/Images/journalticket.png", glm::vec2(0.0f, 0.0f), glm::vec2(16.0f, 16.0f), UIElement::IN_GAME);
		journalButton->SetPosition(glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f));
		m_gameObjects.push_back(journalButton);
		journalButton->SetClickable(true);





	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); // Call the base class update

		if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_2))
		{
			Application::Get().SetScene("Hallway");
			// << "clicked" << std::endl;
			// Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Boss", "Assets/Images/awesomeface.png", m_position));
			 //

		}

		//std::cout << "cam pos journal " << camera.GetPosX() << " , " << camera.GetPosY() << std::endl;

	}

	Camera& camera = Application::GetCamera();
	Input& input = Application::GetInput();
};



//NOTE : UIs not follow camera
// ButtonUI cant scale 