#pragma once
#include "../UI/UIElement.h"
#include "../Application.h"
#include <functional>

class TransitionEffects {
public:
    TransitionEffects(UIElement* uiElement)
        : uiElement(uiElement), isActive(false), elapsedTime(0.0f), duration(0.0f), initialAlpha(0.0f), targetAlpha(0.0f), currentAlpha(0.0f), onComplete(nullptr) {
        if (uiElement) {
            uiElement->setActiveStatus(true);
            uiElement->SetAlpha(currentAlpha);  // Ensure it's initially set to current alpha
        }
    }

    void FadeIn(float duration, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        isActive = true;

        // Initialize alpha based on current state
        this->duration = duration;
        this->initialAlpha = currentAlpha;
        this->targetAlpha = 0.0f;  // Fade to transparent
        this->elapsedTime = 0.0f;
        this->onComplete = onComplete;
    }

    void FadeOut(float duration, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        isActive = true;

        // Initialize alpha based on current state
        this->duration = duration;
        this->initialAlpha = currentAlpha;
        this->targetAlpha = 1.0f;  // Fade to opaque
        this->elapsedTime = 0.0f;
        this->onComplete = onComplete;
    }

    void Update(float dt) {
        if (!isActive || !uiElement) return;

        elapsedTime += dt;
        float progress = elapsedTime / duration;
        currentAlpha = initialAlpha + (targetAlpha - initialAlpha) * progress;
        uiElement->SetAlpha(currentAlpha);

        if (elapsedTime >= duration) {
            currentAlpha = targetAlpha;
            uiElement->SetAlpha(targetAlpha);
            isActive = false;
            if (onComplete) onComplete();
            // Deactivate UIElement after FadeIn is complete
            if (targetAlpha == 0.0f) {
                uiElement->setActiveStatus(false);
            }
        }
    }

private:
    UIElement* uiElement;
    bool isActive;
    float elapsedTime;
    float duration;
    float initialAlpha;
    float targetAlpha;
    float currentAlpha;  // Track current alpha state
    std::function<void()> onComplete;
};
