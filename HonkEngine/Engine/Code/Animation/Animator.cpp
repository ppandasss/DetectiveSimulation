#include "Animator.h"
#include <iostream>

void Animator::AddAnimation(const std::string& name,  int row, int maxFrames, float speed, LoopType loopType, std::function<void()> onComplete) {
    m_animations[name] = { speed, maxFrames,row, loopType, onComplete };
}

void Animator::SetAnimation(const std::string& name) {
    if (m_animations.find(name) != m_animations.end() ) {

       // std::cout << "Setting animation: " << name << std::endl;
        m_currentAnimation = name;
        if (m_currentAnimation != name)
        {
            m_currentFrame = 0;
        }
        
    }
    else {
       // std::cout << "Animation not found: " << name << std::endl;
        m_currentFrame = 0;
    }
}

void Animator::Update(float dt) {

    
   
 
    if (m_currentAnimation.empty()) return;

    Animation& anim = m_animations[m_currentAnimation];
    float frameIncrement = anim.speed * dt;

    if (anim.loopType == LoopType::PingPong) {
        if (m_pingPongForward) {
            m_currentFrame += frameIncrement;
        }
        else {
            m_currentFrame -= frameIncrement;
        }

        if (m_currentFrame >= anim.maxFrames || m_currentFrame <= 0) {
            m_pingPongForward = !m_pingPongForward;
            if (anim.onComplete) {
                anim.onComplete();
            }
        }
    }
    else {
        m_currentFrame += frameIncrement;
        if (m_currentFrame >= anim.maxFrames) {
            //std::cout << "Updating Animator. Current Frame: " << m_currentFrame << std::endl;
            if (anim.loopType == LoopType::Loop) {
                m_currentFrame = 0;
            }
            else {
                m_currentFrame = static_cast<float>(anim.maxFrames - 1);
            }

            if (anim.onComplete) {
                anim.onComplete();
            }
        }
    }
}

int Animator::GetCurrentFrame() const {
    return static_cast<int>(m_currentFrame);
}

int Animator::GetCurrentRow() const {
    if (m_currentAnimation.empty()) return 0;
    return m_animations.at(m_currentAnimation).row;
}
