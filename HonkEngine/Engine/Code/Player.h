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
#include "Scene.h"


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

    // Initialize to a default or idle animation
    std::string currentAnimation = "idle"; // Assume "idle" is an animation you've added


    //std::cout << "Player Pos x :" << m_position.x << "Player Pos y :" << m_position.y << std::endl;
    if (input.Get().GetKey(GLFW_KEY_A))
    {
        m_position.x -= speed * dt;
        currentAnimation = "walk_left";
    }
    if (input.Get().GetKey(GLFW_KEY_D))
    {
        m_position.x += speed * dt;
        currentAnimation = "walk_right";
    }
    if (input.Get().GetMouseButton(GLFW_MOUSE_BUTTON_1))
    {
        std::cout << "clicked" << std::endl;
        Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Boss", "Assets/Images/awesomeface.png"));
     
    }
    // Set the animation
    m_animator.SetAnimation(currentAnimation);

    // Then update the animator
    m_animator.Update(dt);

    // Now get the current frame and row
    int currentFrame = m_animator.GetCurrentFrame();
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