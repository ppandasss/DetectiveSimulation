#pragma once

#include "AnimateGameObject.h"
#include "../Animation/Animator.h"
#include <iostream>
#include <glm/glm.hpp>
#include "../Application.h"
#include "../Scene/Scene.h"

class Bell : public AnimateGameObject {
public:
    Bell(const std::string& name, const std::string& texturePath, float row, float col)
        : AnimateGameObject(name, texturePath, row, col), animating(false), isRinging(false),m_name(name)
    {
        m_animator.AddAnimation("bell_ring", 1, 3, 5.0f, Animator::LoopType::Once, std::bind(&Bell::onRingComplete, this));
    }

    virtual void Update(float dt, long frame) override {
        AnimateGameObject::Update(dt, frame);
        if (animating) {
            m_animator.Update(dt);
            m_animator.SetAnimation(currentAnimation);
            // Now get the current frame and row
            int currentFrame = m_animator.GetCurrentFrame();
            int currentRow = m_animator.GetCurrentRow();

            // Use the current frame and row for your sprite sheet
            animY = static_cast<float>(currentRow);
            animX = static_cast<float>(currentFrame);
        }
    }

    void startRinging() {
        if (!animating) {
            animating = true;
            //std::cout << "Starting to ring." << std::endl;
            currentAnimation = "bell_ring";
            AudioManager::GetInstance().PlaySound("bellRing", false);
            isRinging = true;
        }

    }

    void stopRinging() {
        currentAnimation = "idle";
        animating = false;
        isRinging = false;
        AudioManager::GetInstance().StopSound("bellRing");  // Ensure this method stops the sound immediately.
        m_animator.SetAnimation(currentAnimation);
    }

    bool isBellRinging() const {
        return isRinging;
    }

    std::string getName()
    {
		return m_name;
	} 


private:
    void onRingComplete() {

        //std::cout << "Ring complete. Will ring again in 2 seconds." << std::endl;
        if (animating) {
            currentAnimation = "idle";
            m_animator.SetAnimation(currentAnimation);  // Set idle animation immediately
            animating = false;  // Reset animating state
            Application::Get().SetTimer(2000, [this]() { this->startRinging(); }, false);  // Set timer to restart ringing
        }
    }

    std::string m_name;
    Animator m_animator;
    bool animating;
    bool isRinging;
    std::string currentAnimation;
};
