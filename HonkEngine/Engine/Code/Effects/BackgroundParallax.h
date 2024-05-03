#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../GameObjects/GameObject.h"

class BackgroundParallax {
public:
    BackgroundParallax() {}

    // Add a pair of background objects to a specific layer with a given speed
    void AddBackgroundPair(size_t layerIndex, GameObject* object1, GameObject* object2, float speed) {
        if (layers.size() <= layerIndex) {
            layers.resize(layerIndex + 1);
        }
        layers[layerIndex].push_back({ {object1, object2}, speed });
    }

    // Update all layers and pairs within those layers
    void Update(float dt) {
        for (auto& layer : layers) {
            for (auto& pair : layer) {
                UpdatePairPositions(pair.first, pair.second, dt);
            }
        }
    }

private:
    std::vector<std::vector<std::pair<std::vector<GameObject*>, float>>> layers;

    void UpdatePairPositions(std::vector<GameObject*>& objects, float speed, float dt) {
        float backgroundWidth = 76.6f;  // Assuming all backgrounds have the same width
        for (GameObject* background : objects) {
            glm::vec3 pos = background->GetPosition();
            pos.x -= speed * dt;
            if (pos.x <= -backgroundWidth) {
                pos.x += 2 * backgroundWidth;  // Loop the background around
            }
            background->SetPosition(pos);
        }
    }
};
