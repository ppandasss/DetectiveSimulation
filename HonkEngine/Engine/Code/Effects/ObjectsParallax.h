#pragma once
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "../GameObjects/GameObject.h"
#include "../Application.h"

class ObjectsParallax {
public:
    ObjectsParallax() : enabled(false) {}

    void AddObjectToLayer(GameObject* object, float layerMultiplier) {
        if (object) {
            layerObjects[layerMultiplier].push_back(object);
        }
    }

    void UpdateLayers() {
        if (enabled) {
            UpdateLayeredObjects();
        }
    }

    void EnableParallaxEffect() {
        enabled = true;
    }

    void DisableParallaxEffect() {
        enabled = false;
    }

private:
    std::unordered_map<float, std::vector<GameObject*>> layerObjects;
    bool enabled;

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
                pos += glm::vec3(-mouseOffset.x * multiplier, mouseOffset.y * multiplier, 0.0f);
                object->SetPosition(pos);
            }
        }
    }
};
