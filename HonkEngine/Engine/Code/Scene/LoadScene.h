#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../GameObjects/AnimateGameObject.h"

class LoadScene : public Scene
{
private:
    float fadeInDuration = 3.0f;  // Duration for fade-in effect in seconds
    float fadeOutDuration = 2.0f; // Duration for fade-out effect in seconds
    float holdDuration = 2.0f;    // Duration to hold the logo before fading out
    float currentTime = 0.0f;     // Current time elapsed
    enum FadeState { FadingIn, Holding, FadingOut, FullyTransparent } fadeState = FadingIn;

public:
    LoadScene()
    {
        GameObject* engineLogo = new RenderGameObject("EngineLogo", "Assets/Images/ILogo.png");
        engineLogo->SetScale(glm::vec3(4.0f, 3.0f, 0.0f)); // Initial scale set to 4.0f by 3.0f
        std::cout << "Engine logo size: " << engineLogo->GetScale().x << " " << engineLogo->GetScale().y << std::endl;
        m_gameObjects.push_back(engineLogo);
    }

    void Update(float dt, long frame)
    {
        currentTime += dt;
        RenderGameObject* engineLogo = dynamic_cast<RenderGameObject*>(GetGameObjectByName("EngineLogo"));
        if (engineLogo)
        {
            switch (fadeState)
            {
            case FadingIn:
            {
                // Scope for FadingIn variables
                float alphaIn = currentTime / fadeInDuration;
                engineLogo->SetAlpha(alphaIn);
                float scaleIn = 1.0f + 0.2f * alphaIn; // Expands from 100% to 120%
                engineLogo->SetScale(glm::vec3(4.0f * scaleIn, 3.0f * scaleIn, 1.0f)); // Adjust based on original size
                if (currentTime >= fadeInDuration)
                {
                    fadeState = Holding;
                    currentTime = 0.0f;
                }
                break;
            }

            case Holding:
            {
                // Holding phase does not require scoped variables
                engineLogo->SetAlpha(1.0f);
                engineLogo->SetScale(glm::vec3(4.8f, 3.6f, 1.0f)); // Maintained at 120%
                if (currentTime >= holdDuration)
                {
                    fadeState = FadingOut;
                    currentTime = 0.0f;
                }
                break;
            }

            case FadingOut:
            {
                // Scope for FadingOut variables
                float alphaOut = 1.0f - (currentTime / fadeOutDuration);
                engineLogo->SetAlpha(alphaOut);
                float scaleOut = 1.2f - 0.2f * (currentTime / fadeOutDuration); // Gradually return to 100%
               // engineLogo->SetScale(glm::vec3(4.0f * scaleOut, 3.0f * scaleOut, 1.0f));
                if (currentTime >= fadeOutDuration)
                {
                    fadeState = FullyTransparent;
                    currentTime = 0.0f;
                    engineLogo->SetAlpha(0.0f); // Ensure it's fully transparent

                    Application::Get().SetScene("MainMenu");
                    //Application::Get().SetScene("Hallway"); // Change scene when fully faded out
                }
                break;
            }

            case FullyTransparent:
            {
                // Fully Transparent phase does not require scoped variables
                break; // Nothing else to do once fully transparent
            }
            }
        }

        // Handle instant scene switch on key press (debug or skip functionality)
        Input& input = Application::GetInput();
        if (input.Get().GetKey(GLFW_KEY_SPACE))
        {
            Application::Get().SetScene("MainMenu");
            //Application::Get().SetScene("Hallway");
        }
    }



};
