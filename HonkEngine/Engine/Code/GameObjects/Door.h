#pragma once

#include "GameObject.h"
#include <string>
#include <glm/glm.hpp>

class Door : public GameObject {
public:
    Door(const std::string& name, const glm::vec3& position, const glm::vec3& scale, const std::string& sceneName)
        : GameObject(name), m_sceneName(sceneName) {
        SetPosition(position);
        SetScale(scale);
    }

    bool CheckCollision(const glm::vec3& playerPosition, const glm::vec3& playerScale) {
     
        glm::vec3 doorMin = m_position - m_scale * 0.5f;
        glm::vec3 doorMax = m_position + m_scale * 0.5f;
        glm::vec3 playerMin = playerPosition - playerScale * 0.5f;
        glm::vec3 playerMax = playerPosition + playerScale * 0.5f;

        return (doorMin.x <= playerMax.x && doorMax.x >= playerMin.x) &&
            (doorMin.y <= playerMax.y && doorMax.y >= playerMin.y) &&
            (doorMin.z <= playerMax.z && doorMax.z >= playerMin.z);
    }

    const std::string& GetSceneName() const {
        return m_sceneName;
    }

private:
    std::string m_sceneName;
};
