
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
		
		
		RenderGameObject* room = new RenderGameObject("cabin1", "Assets/Images/passenger_room1.png",glm::vec3(0.0f, 0.0f, 0.0f));
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

		GameObject* cabinObject = GetGameObjectByName("cabin1");
		if (cabinObject) {
			// Cast to Player* if necessary, or directly use if GetPosition is part of GameObject
			RenderGameObject* cabin = dynamic_cast<RenderGameObject*>(cabinObject);
			if (cabin) {

				// Get the player's position
				glm::vec3 camPos = glm::vec3(camera.GetPosX(),camera.GetPosY(),0.0f);

				cabin->SetPosition(camPos);

			}
		}
	}

	Input& input = Application::GetInput();
	Camera& camera = Application::GetCamera();
};