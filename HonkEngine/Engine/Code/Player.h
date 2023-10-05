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
#include "Animator.h" 


class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		:AnimateGameObject(name, texturePath,4.0f,4.0f)
	{
		m_scale = glm::vec3(1.0f, 1.0f, 0.0f);
		m_animator.AddAnimation("walk_left", 3, 4, 6.0f, Animator::LoopType::Loop, []() { /* On Complete */ });
		m_animator.AddAnimation("walk_right", 2, 4, 6.0f, Animator::LoopType::Loop, []() { /* On Complete */ });
	}
	
void Update(float dt, long frame) override
    {
        Input& input = Application::GetInput();
        AnimateGameObject::Update(dt, frame);



		if (input.Get().GetKey(GLFW_KEY_A))
		{
			m_position.x -= speed * dt;
			m_animator.SetAnimation("walk_left");

		}
		if (input.Get().GetKey(GLFW_KEY_D))
		{
			m_position.x += speed * dt;
			m_animator.SetAnimation("walk_right");

		}
		 if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		 {
			 mousePos = Application::Get().CursorPos();
			 Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Konrai", "Assets/Images/konrai.jpg"));
			 std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
		 }
		if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_2))
		{
			Application::Get().SetScene("room1");
		}
	
		// Then update the animator
		m_animator.Update(dt);

		// Now get the current frame and row
		int currentFrame = m_animator.GetCurrentFrame();
		std::cout << "Current Frame: " << currentFrame << std::endl;
		int currentRow = m_animator.GetCurrentRow();

		// Use the current frame and row for your sprite sheet
		animY = static_cast<float>(currentRow);
		animX = static_cast<float>(currentFrame);
		
	}



private:
	float speed = 5.0f;

	glm::vec2 mousePos;
	Animator m_animator;
};