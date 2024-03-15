#pragma once
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "../GameObjects/GameObject.h"
#include "../Application.h"

class ParallaxManager {
public:
    ParallaxManager(float backgroundSpeed = 0.1f) : backgroundSpeed(backgroundSpeed) {}

    void AddObjectToLayer(GameObject* object, float layerMultiplier) {
        if (object) {
            layerObjects[layerMultiplier].push_back(object);
        }
    }

    void AddBackgroundObject(GameObject* object) {
        if (object) {
            backgroundObjects.push_back(object);
        }
    }

    void SetBackgroundSpeed(float newSpeed) {
        backgroundSpeed = newSpeed;
    }

    void Update() {
        UpdateBackgroundPositions();
        UpdateLayeredObjects();
    }

private:
    std::unordered_map<float, std::vector<GameObject*>> layerObjects;
    std::vector<GameObject*> backgroundObjects;
    float backgroundSpeed;

    void UpdateBackgroundPositions() {
        float backgroundWidth = 76.6f; // Adjust this to your background width
        for (GameObject* background : backgroundObjects) {
            glm::vec3 pos = background->GetPosition();
            pos.x -= backgroundSpeed;
            if (pos.x <= -backgroundWidth) {
                pos.x += 2 * backgroundWidth; // Adjust for the number of background objects
            }
            background->SetPosition(pos);
        }
    }

    void UpdateLayeredObjects() {
        static glm::vec2 previousMousePos = glm::vec2(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);
        glm::vec2 mousePos = Application::Get().CursorPos();
        glm::vec2 mouseDelta = mousePos - previousMousePos;
        previousMousePos = mousePos;
        glm::vec2 screenCenter = glm::vec2(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);
        glm::vec2 mouseOffset = mouseDelta / screenCenter;

        for (auto& layer : layerObjects) {
            float multiplier = layer.first;
            for (GameObject* object : layer.second) {
                glm::vec3 pos = object->GetPosition();
                pos += glm::vec3(-mouseOffset.x * multiplier, 0.0f, 0.0f);
                object->SetPosition(pos);
            }
        }
    }
};
