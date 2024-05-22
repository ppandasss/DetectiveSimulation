#pragma once
#include "../UI/UIElement.h"
#include "../Application.h"
#include <functional>

class TransitionEffects {
public:
    TransitionEffects(UIElement* uiElement)
        : uiElement(uiElement), isActive(false) {
        if (uiElement) {
            uiElement->setActiveStatus(false);
            uiElement->SetAlpha(0.0f);  // Ensure it's initially transparent
        }
    }

    void FadeIn(float duration, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        uiElement->setActiveStatus(true);
        isActive = true;

        // Initialize alpha to transparent
        float initialAlpha = 0.0f;
        float targetAlpha = 1.0f;
        float elapsedTime = 0.0f;

        Application::Get().SetTimer(static_cast<int>(duration * 1000), [this, initialAlpha, targetAlpha, duration, &elapsedTime, onComplete]() mutable {
            double deltaTime = Application::Get().GetDeltaTime();
            elapsedTime += deltaTime;
            float alpha = initialAlpha + (targetAlpha - initialAlpha) * (elapsedTime / duration);
            uiElement->SetAlpha(alpha);

            if (elapsedTime >= duration) {
                uiElement->SetAlpha(targetAlpha);
                uiElement->setActiveStatus(false);
                isActive = false;
                if (onComplete) onComplete();
            }
            }, true);
    }

    void FadeOut(float duration, const std::string& nextScene, std::function<void()> onComplete = nullptr) {
        if (!uiElement) return;

        uiElement->setActiveStatus(true);
        isActive = true;

        // Initialize alpha to opaque
        float initialAlpha = 1.0f;
        float targetAlpha = 0.0f;
        float elapsedTime = 0.0f;

        Application::Get().SetTimer(static_cast<int>(duration * 1000), [this, initialAlpha, targetAlpha, duration, &elapsedTime, nextScene, onComplete]() mutable {
            double deltaTime = Application::Get().GetDeltaTime();
            elapsedTime += deltaTime;
            float alpha = initialAlpha + (targetAlpha - initialAlpha) * (elapsedTime / duration);
            uiElement->SetAlpha(alpha);

            if (elapsedTime >= duration) {
                uiElement->SetAlpha(targetAlpha);
                uiElement->setActiveStatus(false);
                isActive = false;
                Application::Get().SetScene(nextScene);
                if (onComplete) onComplete();
            }
            }, true);
    }

private:
    UIElement* uiElement;
    bool isActive;
};
