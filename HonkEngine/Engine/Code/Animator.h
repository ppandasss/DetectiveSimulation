#pragma once
class Animator {
public:
    Animator(float animationSpeed, int maxFrames)
        : m_speed(animationSpeed), m_maxFrames(maxFrames), m_currentFrame(0) {}

    void Update(float dt) {
        m_currentFrame += m_speed * dt;
        if (m_currentFrame >= m_maxFrames) {
            m_currentFrame = 0;
        }
    }

    int GetCurrentFrame() const {
        return static_cast<int>(m_currentFrame);
    }

private:
    float m_speed;
    int m_maxFrames;
    float m_currentFrame;
};
