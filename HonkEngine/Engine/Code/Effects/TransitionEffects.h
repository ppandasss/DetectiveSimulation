#pragma once
#include "../UI/UIElement.h"
#include "../Application.h"
#include <functional>

class TransitionEffects {
public:
    TransitionEffects(UIElement* uiElement)
        : uiElement(uiElement), isActive(false), elapsedTime(0.0f), duration(0.0f), initialAlpha(0.0f), targetAlpha(0.0f), onComplete(nullptr) {
        if (uiElement) {
            uiElement->setActiveStatus(true);
            uiElement->SetAlpha(1.0f);  // Ensure it's initially transparent
        }
    }

    void FadeIn(float duration, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        uiElement->setActiveStatus(true);
        isActive = true;

        // Initialize alpha to fully opaque
        this->duration = duration;
        this->initialAlpha = 1.0f;
        this->targetAlpha = 0.0f;
        this->elapsedTime = 0.0f;
        this->onComplete = onComplete;
    }

    void FadeOut(float duration, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        uiElement->setActiveStatus(true);
        isActive = true;

        // Initialize alpha to fully transparent
        this->duration = duration;
        this->initialAlpha = 0.0f;
        this->targetAlpha = 1.0f;
        this->elapsedTime = 0.0f;
        this->onComplete = onComplete;
    }

    void Update(float dt) {
        if (!isActive || !uiElement) return;

        elapsedTime += dt;
        float alpha = initialAlpha + (targetAlpha - initialAlpha) * (elapsedTime / duration);
        uiElement->SetAlpha(alpha);

        if (elapsedTime >= duration) {
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
    std::function<void()> onComplete;
};
