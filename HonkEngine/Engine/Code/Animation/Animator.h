#pragma once

#include <unordered_map>
#include <functional>
#include <string>

class Animator {
public:
    enum class LoopType {
        Once,
        Loop,
        PingPong,
    };

    struct Animation {
        float speed;
        int maxFrames;
        int row;
        LoopType loopType;
        std::function<void()> onComplete;
    };

    Animator() : m_currentFrame(0), m_currentAnimation("") {}

    void AddAnimation(const std::string& name, int row, int maxFrames, float speed, LoopType loopType, std::function<void()> onComplete);

    void SetAnimation(const std::string& name);

    void Update(float dt);

    int GetCurrentFrame() const;

    int GetCurrentRow() const;

    std::string GetCurrentAnimation() const { return m_currentAnimation; } 
private:
    float m_currentFrame;
    std::string m_currentAnimation;
    std::unordered_map<std::string, Animation> m_animations;
    bool m_pingPongForward = true;
};
