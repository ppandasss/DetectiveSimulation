#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../UI/UIElement.h"
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"

class JournalRoom : public Scene
{
public:

	JournalRoom()
	{

		//RenderGameObject* room = new RenderGameObject("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f));
		//room->SetScale(glm::vec3(20.0f, 12.0f, 0.0f));

		UIElement* JournalButtonTest = new UIButton("JournalButtonTest", "Assets/Images/JournalButton.png", glm::vec3(-6.5f, -3.5f, 0.0f), glm::vec3(2.5f, 2.5f, 0.0f));

		m_gameObjects.push_back(JournalButtonTest);


	}

	void Update(float dt, long frame) {

		Scene::Update(dt, frame); // Call the base class update


		if (input.Get().GetKeyDown(GLFW_KEY_J))
		{

			std::cout << "Journal Button Test Room" << std::endl;
			Application::Get().SetScene("Hallway");

		}
	}

	Input& input = Application::GetInput();
};