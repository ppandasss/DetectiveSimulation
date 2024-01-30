#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>

class Room1 : public Scene {
public:

    Room1() {

        // Create a UIElement instead of RenderGameObject for the cabin
        UINormal* room = new UINormal("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f),true);
        m_gameObjects.push_back(room);

    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame); // Call the base class update

        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            std::cout << "Button pressed" << std::endl;
            Application::Get().SetScene("Hallway");
        }

        // Use the UIElement for cabin interaction
        GameObject* cabinObject = GetGameObjectByName("cabin1");
        if (cabinObject) {
            UIElement* cabin = dynamic_cast<UIElement*>(cabinObject);
            if (cabin) {
                // Get the player's position
                glm::vec3 camPos = glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f);
                cabin->SetPosition(camPos);
            }
        }
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
};
