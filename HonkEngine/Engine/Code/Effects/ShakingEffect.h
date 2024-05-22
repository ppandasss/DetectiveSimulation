#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <random>
#include "../UI/UIElement.h"

class ShakingEffect {
public:
    ShakingEffect(float amplitude, int shakeInterval, int shakeDuration, int pauseDuration)
        : amplitude(amplitude), shakeInterval(shakeInterval), shakeDuration(shakeDuration), pauseDuration(pauseDuration),
        isShaking(false), shakeDirection(1), shakeCount(0), elapsedTime(0.0f), shakeTime(0.0f) {}

    ~ShakingEffect() = default;

    void AddObject(UIElement* object) {
        objects.push_back({ object, object->GetPosition() });
    }

    void StartShaking() {
        isShaking = true;
        shakeCount = 0;
        shakeDirection = 1;
        elapsedTime = 0.0f;
        shakeTime = 0.0f;
    }

    void StopShaking() {
        isShaking = false;
        for (auto& shakingObject : objects) {
            shakingObject.object->SetPosition(shakingObject.initialPosition);
        }
    }

    void Update(float deltaTime) {
        if (!isShaking) return;

        elapsedTime += deltaTime;
        shakeTime += deltaTime;

        if (shakeTime < shakeDuration / 1000.0f) { // Shake for shakeDuration seconds
            if (elapsedTime >= shakeInterval / 1000.0f) { // Convert ms to seconds
                for (auto& shakingObject : objects) {
                    ApplyShake(shakingObject);
                }
                shakeDirection = -shakeDirection; // Reverse direction for the next shake
                shakeCount++;
                elapsedTime = 0.0f;
            }
        }
        else {
            if (shakeTime >= (shakeDuration + pauseDuration) / 1000.0f) { // Total duration of shake + pause
                shakeTime = 0.0f;
                shakeCount = 0;
            }
        }
    }

private:
    struct ShakingObject {
        UIElement* object;
        glm::vec3 initialPosition;
    };
    std::vector<ShakingObject> objects;
    float amplitude;
    int shakeInterval; // Time in ms for each shake
    int shakeDuration; // Time in ms for the duration of shaking
    int pauseDuration; // Time in ms for pauses
    bool isShaking;
    int shakeDirection;
    int shakeCount;
    float elapsedTime;
    float shakeTime;

    void ApplyShake(ShakingObject& shakingObject) {
        float offset = ((rand() % 2001 - 1000) / 1000.0f) * amplitude; // Random number between -1 and 1
        glm::vec3 newPosition = shakingObject.object->GetPosition() + glm::vec3(offset, 0.0f, 0.0f);
        shakingObject.object->SetPosition(newPosition);
    }
};
