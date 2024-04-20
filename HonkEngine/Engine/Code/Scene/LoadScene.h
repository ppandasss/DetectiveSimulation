#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../GameObjects/AnimateGameObject.h"

class LoadScene : public Scene
{
private:
    float fadeInDuration = 3.0f; // Duration for fade-in effect in seconds
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
        // Update the current time
        currentTime += dt;

        // Get the engineLogo object
        RenderGameObject* engineLogo = dynamic_cast<RenderGameObject*>(GetGameObjectByName("EngineLogo"));
        if (engineLogo)
        {
            switch (fadeState)
            {
            case FadingIn:
            {
                // Calculate the new alpha value for fade-in effect
                float alphaIn = currentTime / fadeInDuration;
                engineLogo->SetAlpha(alphaIn);

                // Calculate the scale for the fade-in effect from initial scale to 120%
                float scale = 1.0f + 0.2f * alphaIn; // Expands from 100% to 120%
                engineLogo->SetScale(glm::vec3(4.0f * scale, 3.0f * scale, 1.0f));

                // Check if the fade-in duration is complete
                if (currentTime >= fadeInDuration)
                {
                    fadeState = Holding;
                    currentTime = 0.0f; // Reset the current time for holding
                }
                break;
            }

            case Holding:
                // Hold the logo at 120% opacity and scale
                engineLogo->SetAlpha(1.0f);
                engineLogo->SetScale(glm::vec3(4.8f, 3.6f, 1.0f)); // 120% of initial size

                // Check if the hold duration is complete
                if (currentTime >= holdDuration)
                {
                    fadeState = FadingOut;
                    currentTime = 0.0f; // Reset the current time for fade-out
                }
                break;

            case FadingOut:
            {
                float alphaOut = 1.0f - (currentTime / fadeOutDuration);
                engineLogo->SetAlpha(alphaOut);

                // Check if the fade-out duration is complete
                if (currentTime >= fadeOutDuration)
                {
                    fadeState = FullyTransparent;
                    currentTime = 0.0f; // Reset the current time for the fully transparent state
                }
                break;
            }
            case FullyTransparent:
                // Keep the logo fully transparent
                engineLogo->SetAlpha(0.0f);

                // Check if the logo has been fully transparent for 1 second
                if (currentTime >= 1.0f)
                {
                    // Switch to the "Hallway" scene
                    Application::Get().SetScene("Hallway");
                }
                break;
            }
        }

        // Check for any key press to switch scenes
        Input& input = Application::GetInput();
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
        {
            if (input.Get().GetKey(key))
            {
                Application::Get().SetScene("Hallway");
                break; // Exit the loop once a key is detected
            }
        }
    }

};
