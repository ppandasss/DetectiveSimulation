#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ParallaxManager.h"
#include "../GameObjects/Timer.h"
#include <memory>

using namespace std;


class Room1 : public Scene {

private:
    AudioManager& audioManager;

    enum class RoomPhase {
        TakeOrderPhase,
        ServePhase,
        InspectionPhase
    };

    RoomPhase currentPhase = RoomPhase::TakeOrderPhase;

    Timer* timer;

public:
    Room1() :audioManager(AudioManager::GetInstance()) {

        timer = &Timer::GetInstance();

        //audioManager.StopSound("HallwayMusic");
        audioManager.LoadSound("cabinMusic", "Assets/Sounds/BGmusic_Cabin.mp3", 0.2f);
        audioManager.SetSoundVolume("cabinMusic", 4.0f);

        GameObject* background1 = new RenderGameObject("BG1", "Assets/Images/Cabin_Background.png");
        GameObject* background2 = new RenderGameObject("BG2", "Assets/Images/Cabin_Background.png");
        background1->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background2->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));
        background1->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background2->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));

        // Scale Multiplier to fit asset scale with screensize
        float sm = 1.23f;

        //Objects     
        UIElement* room = new UINormal("cabin1", "Assets/Images/Martha_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.60f * sm, 10.55f * sm, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martha/Lamp.png", glm::vec3(-1.3f, -0.3f, 0.0f), glm::vec3(1.62f * sm, 2.25f * sm, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Martha/Hat.png", glm::vec3(-1.1f, -1.22f, 0.0f), glm::vec3(3.12f * sm, 0.92f * sm, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Martha/Bag.png", glm::vec3(-0.25f, -5.25f, 0.0f), glm::vec3(2.59f * sm * 1.2f, 1.64f * sm * 1.2f, 0.0f), true);
        UIElement* cane = new UINormal("Cane", "Assets/Images/Martha/Inspection_Cane.png", glm::vec3(-4.0f, -3.72f, 0.0f), glm::vec3(1.07f * sm * 1.2f, 3.7f * sm * 1.2f, 0.0f), true);
        UIElement* letter = new UINormal("Letter", "Assets/Images/Martha/Inspection_Letter.png", glm::vec3(-2.15f, -5.9f, 0.0f), glm::vec3(1.13f * sm * 1.2f, 0.73f * sm * 1.2f, 0.0f), true);

        //UIs
        //Speaker Sprite emotion
        UIElement* marthaNormal = new UINormal("Martha_Normal", "Assets/Images/Martha/Martha_Normal.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* marthaHappy = new UINormal("Martha_Happy", "Assets/Images/Martha/Martha_Happy.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* marthaDisappoint = new UINormal("Martha_Disappoint", "Assets/Images/Martha/Martha_Disappoint.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* marthaUpset = new UINormal("Martha_Upset", "Assets/Images/Martha/Martha_Upset.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* marthaSad = new UINormal("Martha_Sad", "Assets/Images/Martha/Martha_Sad.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);
        UIElement* marthaShy = new UINormal("Martha_Shy", "Assets/Images/Martha/Martha_Shy.png", glm::vec3(4.95f, -2.45f, 0.0f), glm::vec3(3.81f * sm, 6.53f * sm, 0.0f), true);

        //dialogue Box
        UIButton* dialogueBox = new UIButton("DialogueBox", "Assets/Images/UI/DialogueBox.png",
            glm::vec3(0.0f, 3.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");
        //Choices
        UIButton* dialogueChoice1 = new UIButton("DialogueChoiceBox1", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -2.5f, 0.0f), glm::vec3(7.47f, 1.07f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice2 = new UIButton("DialogueChoiceBox2", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -3.65f, 0.0f), glm::vec3(7.47f, 1.07f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice3 = new UIButton("DialogueChoiceBox3", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -1.35f, 0.0f), glm::vec3(7.47f, 1.07f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        //Speak Icons
        UIElement* marthaIcon = new UINormal("MarthaIcon", "Assets/Images/UI/Speaker_icon_Martha.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(2.19f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("MarthaDialogue", dialogueBox,
            "Assets/Dialogue/Martha/Martha_Order.xml", "Martha_Normal");


        //Add SpeakSprite
        dialogueManager->AddSpeakerSprite("Martha_Normal", marthaNormal);
        dialogueManager->AddSpeakerSprite("Martha_Happy", marthaHappy);
        dialogueManager->AddSpeakerSprite("Martha_Disappoint", marthaDisappoint);
        dialogueManager->AddSpeakerSprite("Martha_Upset", marthaUpset);
        dialogueManager->AddSpeakerSprite("Martha_Sad", marthaSad);
        dialogueManager->AddSpeakerSprite("Martha_Shy", marthaShy);
        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("M", marthaIcon);
        dialogueManager->AddSpeakerIcon("W", waiterIcon);
        //Add ChoiceButton
        dialogueManager->AddChoiceButton(dialogueChoice1);
        dialogueManager->AddChoiceButton(dialogueChoice2);
        dialogueManager->AddChoiceButton(dialogueChoice3);


        //setDialogueUI
        dialogueManager->SetDialoguePosition(-0.5f, 3.6f);
        dialogueManager->SetDialogueScale(0.55f);
        dialogueManager->SetChoiceScale(0.56f);

        //Push GamePbjects
        m_gameObjects.push_back(background1);
        m_gameObjects.push_back(background2);
        m_gameObjects.push_back(room);
        m_gameObjects.push_back(marthaNormal);
        m_gameObjects.push_back(marthaHappy);
        m_gameObjects.push_back(marthaDisappoint);
        m_gameObjects.push_back(marthaUpset);
        m_gameObjects.push_back(marthaSad);
        m_gameObjects.push_back(marthaShy);
        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(bag);
        m_gameObjects.push_back(cane);
        m_gameObjects.push_back(letter);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(marthaIcon);
        m_gameObjects.push_back(waiterIcon);

        //add Parallax Effects
        parallaxManager = make_unique<ParallaxManager>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        parallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        parallaxManager->AddObjectToLayer(lamp, defaultLayer);   // Layer 1.5
        parallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        parallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        parallaxManager->AddObjectToLayer(cane, objectLayerOne);   // Layer 2
        parallaxManager->AddObjectToLayer(letter, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaNormal, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaHappy, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaDisappoint, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaUpset, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaSad, objectLayerOne); // Layer 2
        parallaxManager->AddObjectToLayer(marthaShy, objectLayerOne); // Layer 2

        //Scrolling effect for Background
        parallaxManager->SetBackgroundSpeed(2.0f);
        parallaxManager->AddBackgroundObject(background1);
        parallaxManager->AddBackgroundObject(background2);


    }

    void OnEnter() override {
        Scene::OnEnter();  // Call base class if there's relevant logic
        audioManager.PlaySound("cabinMusic", true);
    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        switch (currentPhase) {
        case RoomPhase::TakeOrderPhase:
            // Handle TakeOrderPhase logic
            dialogueManager->Update(dt, frame);
            if (dialogueManager->IsDialogueFinished()) {
                currentPhase = RoomPhase::ServePhase;
            }
            break;

        case RoomPhase::ServePhase:
            // Handle ServePhase logic
            // For now, leave blank as per the instructions
            break;

        case RoomPhase::InspectionPhase:
            // Handle InspectionPhase logic
            // For now, leave blank as per the instructions
            break;
        }

        // Update ParallaxManager for background only
        parallaxManager->UpdateBackground(dt);

        // Allow leaving the room only in phases other than TakeOrderPhase
        if (currentPhase != RoomPhase::TakeOrderPhase && input.Get().GetKeyDown(GLFW_KEY_E)) {

            Application::Get().SetScene("Hallway");

            //Start timer
            timer->start(300);
        }

        // Handle dialogue progression
        if (input.Get().GetKeyDown(GLFW_KEY_SPACE)) {
            dialogueManager->PlayNextDialogue();
        }


    }

    void Render() override {
        Scene::Render(); // Renders GameObjects

        // Manually call DialogueManager's render function
        dialogueManager->Render();
    }

    void OnExit() override {
        Scene::OnExit();  // Call base class if there's relevant logic
        audioManager.StopSound("cabinMusic");
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    unique_ptr<DialogueManager> dialogueManager;
    unique_ptr<ParallaxManager> parallaxManager;

};