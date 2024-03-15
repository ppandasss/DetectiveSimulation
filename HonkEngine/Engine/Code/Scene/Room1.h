#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/DialogueBox.h"
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ParallaxManager.h"
#include <memory>

class Room1 : public Scene {
public:

    Room1() {

        GameObject* background1 = new RenderGameObject("BG1", "Assets/Images/Cabin_Background.png");
        GameObject* background2 = new RenderGameObject("BG2", "Assets/Images/Cabin_Background.png");
        background1->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background2->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background1->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background2->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));

        //Objects
        UIElement* room = new UINormal("cabin1", "Assets/Images/Martharoom.png", glm::vec3(0.0f, -0.15f, 0.0f), glm::vec3(14.30f * 1.345f, 10.55f * 1.345f, 0.0f), true);
        UIElement* martha = new UINormal("Martha", "Assets/Images/Martha.png", glm::vec3(5.4f, -2.85f, 0.0f), glm::vec3(3.81f * 1.345f, 6.53f * 1.345f, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martharoom_Lamp.png", glm::vec3(-1.45f, -0.45f, 0.0f), glm::vec3(1.62f * 1.345f, 2.25f * 1.345f, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Martharoom_hat.png", glm::vec3(-1.2f, -1.5f, 0.0f), glm::vec3(3.12f * 1.345f, 0.92f * 1.345f, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Martharoom_bag.png", glm::vec3(-0.6f, -5.6f, 0.0f), glm::vec3(2.59f * 1.345f, 1.64f * 1.345f, 0.0f), true);
        UIElement* cane = new UINormal("Cane", "Assets/Images/Martharoom_cane.png", glm::vec3(-4.55f, -3.73f, 0.0f), glm::vec3(1.07f * 1.345f, 3.7f * 1.345f, 0.0f), true);
        UIElement* letter = new UINormal("Letter", "Assets/Images/Martharoom_letter.png", glm::vec3(-2.35f, -7.5, 0.0f), glm::vec3(1.13f * 1.345f, 0.73f * 1.345f, 0.0f), true);

        //UIs
        dialogueManager = std::make_unique<DialogueManager>("DialogueManagerName", "Assets/Fonts/OverpassMono.ttf", "Assets/Dialogue/Dialogue_Martha_OrderPhase.xml");
        UIElement* dialogueBox = new UINormal("DialogueBox", "Assets/Images/UI/DialogueBox.png", glm::vec3(0.0f, 3.6f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f), true);
        UIElement* marthaIcon = new UINormal("MarthaIcon", "Assets/Images/UI/Speaker_icon_Martha.png", glm::vec3(4.18f, 3.6f, 0.0f), glm::vec3(2.19f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.53f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        //setDialogueUI
        dialogueManager->SetDialoguePosition(-0.5f, 3.70f);
        dialogueManager->SetDialogueScale(0.55f);


        //Push GamePbjects
        m_gameObjects.push_back(background1);
        m_gameObjects.push_back(background2);
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

        //add Parallax Effects
        parallaxManager = std::make_unique<ParallaxManager>();
        // Add objects to different layers
        parallaxManager->AddObjectToLayer(room, 0.1f);   // Layer 1
        parallaxManager->AddObjectToLayer(lamp, 0.15f);   // Layer 1.5
        parallaxManager->AddObjectToLayer(hat, 0.2f);    // Layer 2
        parallaxManager->AddObjectToLayer(bag, 0.2f);    // Layer 2
        parallaxManager->AddObjectToLayer(cane, 0.2f);   // Layer 2
        parallaxManager->AddObjectToLayer(letter, 0.2f); // Layer 2
        parallaxManager->AddObjectToLayer(martha, 0.15f); // Layer 2

        //Scrolling effect for Background
        parallaxManager->SetBackgroundSpeed(0.05f);
        parallaxManager->AddBackgroundObject(background1);
        parallaxManager->AddBackgroundObject(background2);


    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        dialogueManager->Update(dt, frame);
        parallaxManager->Update();

        if (input.Get().GetKeyDown(GLFW_KEY_E)) {
            Application::Get().SetScene("Hallway");
        }

        if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
            dialogueManager->PlayNextDialogue();
        }

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
    std::unique_ptr<ParallaxManager> parallaxManager;

};