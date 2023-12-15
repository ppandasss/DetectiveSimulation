#pragma once
#pragma once

#include "AnimateGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include <iostream>
#include"GameObject.h"
#include "../Animation/Animator.h" 



class Player : public AnimateGameObject
{
public:
	Player(const std::string& name, const std::string& texturePath,int p_row,int p_col)
		:AnimateGameObject(name, texturePath, p_row, p_col),audioManager(AudioManager::GetInstance())
	{
		m_scale = glm::vec3(6.5f, 6.125f, 0.0f);
        m_position = glm::vec3(0.0f, -1.0f, 0.0f);
	    m_animator.AddAnimation("walk_left", 1, 8, 7.5f, Animator::LoopType::Loop, []() {});
        m_animator.AddAnimation("walk_right", 2, 8, 7.5f, Animator::LoopType::Loop, []() {});
        audioManager.LoadSound("Player_footsteps","Assets/Sounds/footstep.mp3",3.0f);
	}
	
void Update(float dt, long frame) override
{
    Input& input = Application::GetInput();
    AnimateGameObject::Update(dt, frame);

    // Initialize to a default or idle animation
    std::string currentAnimation = "idle"; 
    bool isWalking = false;

    const float leftBound = -20.52f;
    const float rightBound = 21.0f;
    
    if (input.Get().GetKey(GLFW_KEY_A))
    {
        isWalking = true;
        float newPos = m_position.x - speed * dt;
        m_position.x = std::max(newPos, leftBound); // Ensure player doesn't move past left bound
        currentAnimation = "walk_left";
    }
    if (input.Get().GetKey(GLFW_KEY_D))
    {
        isWalking = true;
        float newPos = m_position.x + speed * dt;
        m_position.x = std::min(newPos, rightBound); // Ensure player doesn't move past right bound
        currentAnimation = "walk_right";
    }
    if (input.Get().GetKeyDown(GLFW_KEY_E))
    {
        Application::Get().SetScene("Room1");
    }
    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
    {

        Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Boss", "Assets/Images/awesomeface.png",m_position));

    }
    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_2))
    {
        Application::Get().SetScene("Journal");
       // Application::Get().GetCurrentScene()->AddGameObject(new RenderGameObject("Boss", "Assets/Images/awesomeface.png", m_position));
        //

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

    if (isWalking && !audioManager.IsSoundPlaying("Player_footsteps")) {
        audioManager.PlaySound("Player_footsteps", true);
    }
    else if (!isWalking && audioManager.IsSoundPlaying("Player_footsteps")) {
        audioManager.StopSound("Player_footsteps");
    }
}



private:
	float speed = 5.0f;
	glm::vec2 mousePos;
	Animator m_animator;
    AudioManager& audioManager;
};