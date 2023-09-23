#pragma once
#pragma once

#include "AnimateGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"Scene.h"
#include "Input.h"
#include <iostream>
#include"GameObject.h"


class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		:AnimateGameObject(name, texturePath,4.0f,4.0f)
	{
		m_scale = glm::vec3(0.5f, 0.5f, 0.0f);
	}
	
	 void Update(float dt,long frame) override
	{

		//std::cout << "frame" << frame << std::endl;
	
		AnimateGameObject::Update(dt, frame);
       
        if (Input::Get().GetKey(GLFW_KEY_A))
        {
            m_position.x -= 1.0f * dt;
			animY = 3.0f;
			if (frame % 20 == 0)
			{
				animX += 1.0f;
				if (animX > 4.0f)
				{
					animX = 0.0f;
				}
			}
           
        }
         if (Input::Get().GetKey(GLFW_KEY_D))
        {
            m_position.x += 1.0f * dt;
			animY = 2.0f;
			if (frame % 20 == 0)
			{
				animX += 1.0f;
				if (animX > 4.0f)
				{
					animX = 0.0f;
				}
			}
           
        }
		if (Input::Get().GetKey(GLFW_MOUSE_BUTTON_1))
		{
			mousePos = Application::Get().CursorPos();
			Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Konrai", "Assets/Images/konrai.jpg"));



			std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
		}
		if (Application::Get().IsMouseClick(GLFW_MOUSE_BUTTON_2))
		{
			Application::Get().SetScene("room1");
		}

		
	}



private:
    int frameCounter = 0;
    static const int framesPerCycle = 30;
	glm::vec2 mousePos;
};