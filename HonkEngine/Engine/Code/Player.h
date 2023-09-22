#pragma once
#pragma once

#include "AnimateGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"Scene.h"
#include "Input.h"

class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		: AnimateGameObject(name, texturePath,p_row,p_col)
	{
		
	}
	
	virtual void Update(float dt,long frame)
	{
       
        if (Input::Get().GetKey(GLFW_KEY_A))
        {
            m_position.x -= 5.0f * dt;
			animY = 2.0f / 4.0f;
			if (frame % 10)
			{
				animX += 1.0f / 4.0f;
				if(animX > 3.0f/4.0f)
				{
					animX = 0.0f;
				}
			}
           
        }
        else if (Input::Get().GetKey(GLFW_KEY_D))
        {
            m_position.x += 5.0f * dt;
			animY = 3.0f / 4.0f;
			if (frame % 10)
			{
				animX += 1.0f / 4.0f;
				if (animX > 3.0f / 4.0f)
				{
					animX = 0.0f;
				}
			}
           
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
    int frameCounter = 0;
    static const int framesPerCycle = 30;
	glm::vec2 mousePos;
};