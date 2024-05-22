#pragma once

#include "GameObject.h"
#include <string>
#include <glm/glm.hpp>

class Door : public GameObject {
public:
    Door(const std::string& name, GameObject* highlighted, const glm::vec3& position, const glm::vec3& scale, const std::string& sceneName)
        : GameObject(name), highlightState(highlighted), m_sceneName(sceneName), isOpen(false) {
        SetPosition(position);
        SetScale(scale);
        highlightState->setActiveStatus(false);
    }

    bool CheckCollision(const glm::vec3& playerPosition, const glm::vec3& playerScale) {
        glm::vec3 doorMin = m_position - m_scale * 0.5f;
        glm::vec3 doorMax = m_position + m_scale * 0.5f;

        // Apply the collision scale factor
        glm::vec3 reducedPlayerScale = playerScale * collisionScaleFactor;
        glm::vec3 playerMin = playerPosition - reducedPlayerScale * 0.5f;
        glm::vec3 playerMax = playerPosition + reducedPlayerScale * 0.5f;

        return (doorMin.x <= playerMax.x && doorMax.x >= playerMin.x) &&
            (doorMin.y <= playerMax.y && doorMax.y >= playerMin.y) &&
            (doorMin.z <= playerMax.z && doorMax.z >= playerMin.z);
    }

    void Highlight(bool active) {
        highlightState->SetPosition(m_position);
        highlightState->SetScale(m_scale);
        highlightState->setActiveStatus(active);  
    }

    const std::string& GetSceneName() const {
        return m_sceneName;
    }

    void setPermission(bool open) {
        isOpen = open;
    }

    bool getPermission() const {
        return isOpen;
    }

private:
    bool isOpen;
    const float collisionScaleFactor = 0.3f;
    GameObject* highlightState;
    std::string m_sceneName;
};