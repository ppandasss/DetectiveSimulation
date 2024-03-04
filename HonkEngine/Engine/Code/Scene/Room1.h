#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>e
#include <iostream>
#include "../Dialogue/DialogueBox.h"
#include "../Dialogue/Dialoguemanager.h"
#include <memory>

class Room1 : public Scene {
public:

    Room1() {

       UIElement* room = new UINormal("cabin1", "Assets/Images/Martharoom.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 12.0f, 0.0f), true);
       UIElement* martha = new UINormal("Martha", "Assets/Images/Martha.png", glm::vec3(5.7f, -2.3f, 0.0f), glm::vec3(5.3f, 6.5f, 0.0f), true);
       UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martharoom_Lamp.png", glm::vec3(-0.9f, -0.2f, 0.0f), glm::vec3(1.8f, 2.0f, 0.0f), true);
       UIElement* hat = new UINormal("Hat", "Assets/Images/Martharoom_hat.png", glm::vec3(-0.9f, -1.0f, 0.0f), glm::vec3(3.3f, 1.0f, 0.0f), true);

       dialogueManager = std::make_unique<DialogueManager>("DialogueManagerName", "Assets/Fonts/EI.ttf", "Assets/Dialogue/Dialogue_Martha_OrderPhase.xml");
       UIElement* dialogueBox = new UINormal("DialogueBox", "Assets/Images/DialogueBox.png", glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(7.0f, 1.0f, 0.0f), true);

        dialogueManager->SetDialoguePosition(0.0f,-2.0f);
        dialogueManager->SetDialogueScale(0.6f);
        m_gameObjects.push_back(room);
        m_gameObjects.push_back(martha);
        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(dialogueBox);

    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame); // Call the base class update

        dialogueManager->Update(dt, frame);

        GameObject* dialogueText = GetGameObjectByName("Dialogue1");
        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetKeyDown(GLFW_KEY_T)) {
            dialogueManager->PlayNextDialogue();
           //alogueText
        }


        // Use the UIElement for cabin interaction
        
        
    }
    void Render() override {
        Scene::Render(); // Renders GameObjects

        // Manually call DialogueManager's render function
        dialogueManager->Render();
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    std::unique_ptr<DialogueManager> dialogueManager;

};
