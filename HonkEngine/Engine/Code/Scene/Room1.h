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

        GameObject* background = new RenderGameObject("BG", "Assets/Images/Cabin_Background.png");
        background->SetScale(glm::vec3(76.60f, 10.8f, 0.0f));
        background->SetPosition(glm::vec3(-3.2f, 3.0f, 0.0f));

        UIElement* room = new UINormal("cabin1", "Assets/Images/Martharoom.png", glm::vec3(0.0f, -0.15f, 0.0f), glm::vec3(14.30f * 1.345f, 10.55f * 1.345f, 0.0f), true);
        UIElement* martha = new UINormal("Martha", "Assets/Images/Martha.png", glm::vec3(5.4f, -2.85f, 0.0f), glm::vec3(3.81f * 1.345f, 6.53f * 1.345f, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martharoom_Lamp.png", glm::vec3(-1.45f, -0.45f, 0.0f), glm::vec3(1.62f * 1.345f, 2.25f * 1.345f, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Martharoom_hat.png", glm::vec3(-1.2f, -1.5f, 0.0f), glm::vec3(3.12f * 1.345f, 0.92f * 1.345f, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Martharoom_bag.png", glm::vec3(-0.6f, -5.6f, 0.0f), glm::vec3(2.59f * 1.345f, 1.64f * 1.345f, 0.0f), true);
        UIElement* cane = new UINormal("Cane", "Assets/Images/Martharoom_cane.png", glm::vec3(-4.55f, -3.73f, 0.0f), glm::vec3(1.07f * 1.345f, 3.7f * 1.345f, 0.0f), true);
        UIElement* letter = new UINormal("Letter", "Assets/Images/Martharoom_letter.png", glm::vec3(-2.35f, -7.5, 0.0f), glm::vec3(1.13f * 1.345f, 0.73f * 1.345f, 0.0f), true);

        dialogueManager = std::make_unique<DialogueManager>("DialogueManagerName", "Assets/Fonts/OverpassMono.ttf", "Assets/Dialogue/Dialogue_Martha_OrderPhase.xml");
        UIElement* dialogueBox = new UINormal("DialogueBox", "Assets/Images/UI/DialogueBox.png", glm::vec3(0.0f, 3.6f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f), true);
        UIElement* marthaIcon = new UINormal("MarthaIcon", "Assets/Images/UI/Speaker_icon_Martha.png", glm::vec3(4.18f, 3.6f, 0.0f), glm::vec3(2.19f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.53f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);


        dialogueManager->SetDialoguePosition(6.8f, 3.85f);
        dialogueManager->SetDialogueScale(0.55f);
        m_gameObjects.push_back(background);
        m_gameObjects.push_back(room);
        m_gameObjects.push_back(martha);
        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(bag);
        m_gameObjects.push_back(cane);
        m_gameObjects.push_back(letter);
        m_gameObjects.push_back(dialogueBox);
        //m_gameObjects.push_back(marthaIcon);
        m_gameObjects.push_back(waiterIcon);

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