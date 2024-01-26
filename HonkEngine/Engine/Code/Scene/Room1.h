
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
		RenderGameObject* room = new RenderGameObject("cabin1", "Assets/Images/passenger_room1.png",glm::vec3(0.0f,0.0f,0.0f));
		room->SetScale(glm::vec3(20.0f, 12.0f, 0.0f));

		


		m_gameObjects.push_back(room);


	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); // Call the base class update

		if (input.Get().GetKeyDown(GLFW_KEY_E))
		{

			std::cout << "Button pressed" << std::endl;
			Application::Get().SetScene("Hallway");
		}

		
	}

	Input& input = Application::GetInput();
};