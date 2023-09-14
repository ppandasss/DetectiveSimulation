#pragma once
#pragma once

#include "AnimGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"Scene.h"
#include "Input.h"

class Player : public AnimGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath)
		: AnimGameObject(name, texturePath,4,4)
	{}
	
	virtual void Update(float dt)
	{
		if (Input::Get().GetKey(GLFW_KEY_A))
		{
			m_position.x -= 5.0f * dt;

		}
		if (Input::Get().GetKey(GLFW_KEY_D))
		{
			m_position.x += 5.0f * dt;

		}
		if (Input::Get().GetKey(GLFW_MOUSE_BUTTON_1))
		{
			mousePos = Application::Get().CursorPos();

			Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Konrai", "Assets/Images/konrai.jpg"));
			//GameObjects numbers will print out for debuging .It should be only 3 when click


			std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
		}
		if (Application::Get().IsMouseClick(GLFW_MOUSE_BUTTON_2))
		{
			Application::Get().SetScene("room1");
		}
		
	}



private:

	glm::vec2 mousePos;
};