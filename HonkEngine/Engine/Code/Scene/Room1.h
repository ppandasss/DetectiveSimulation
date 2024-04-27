#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ObjectsParallax.h"
#include "../Effects/BackgroundParallax.h"
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
    Text* instructionText;

public:
    Room1() :audioManager(AudioManager::GetInstance()) {

        timer = &Timer::GetInstance();

        audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3", 4.0f);
        

        GameObject* background1a = new RenderGameObject("BG1", "Assets/Images/BG/Cabin_Background_01.png");
        GameObject* background2a = new RenderGameObject("BG2", "Assets/Images/BG/Cabin_Background_02.png");
        GameObject* background3a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_03.png");
        GameObject* background4a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_04.png");
        GameObject* background5a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_05.png");
        GameObject* background6a = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_06.png");

        GameObject* background1b = new RenderGameObject("BG1", "Assets/Images/BG/Cabin_Background_01.png");
        GameObject* background2b = new RenderGameObject("BG2", "Assets/Images/BG/Cabin_Background_02.png");
        GameObject* background3b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_03.png");
        GameObject* background4b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_04.png");
        GameObject* background5b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_05.png");
        GameObject* background6b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_06.png");

        background1a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background2a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background3a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background3a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background4a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background5a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
        background6a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

        background1b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background2b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background3b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background3b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background4b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background5b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background6b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));


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

        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(6.00f, -4.3f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

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
        m_gameObjects.push_back(background1a);
        m_gameObjects.push_back(background1b);
        m_gameObjects.push_back(background2a);
        m_gameObjects.push_back(background2b);
        m_gameObjects.push_back(background3a);
        m_gameObjects.push_back(background3b);
        m_gameObjects.push_back(background4a);
        m_gameObjects.push_back(background4b);
        m_gameObjects.push_back(background5a);
        m_gameObjects.push_back(background5b);
        m_gameObjects.push_back(background6a);
        m_gameObjects.push_back(background6b);
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
        m_gameObjects.push_back(instructionText);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(lamp, defaultLayer);   // Layer 1.5
        ObjectsparallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(cane, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(letter, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaSad, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaShy, objectLayerOne); // Layer 2

        //Scrolling effect for Background
        backgroundParallaxManager->AddBackgroundPair(0, background1a, background1b, 0.5f); // Layer 0, slower
        backgroundParallaxManager->AddBackgroundPair(1, background2a, background2b, 1.0f); // Layer 1, normal
        backgroundParallaxManager->AddBackgroundPair(2, background3a, background3b, 1.5f); // Layer 2, faster
        backgroundParallaxManager->AddBackgroundPair(3, background4a, background4b, 2.0f); // Layer 3, fastest
        backgroundParallaxManager->AddBackgroundPair(4, background5a, background5b, 2.5f); // Layer 4, fastest
        backgroundParallaxManager->AddBackgroundPair(5, background6a, background6b, 3.0f); // Layer 5, fastest

    
    }

    void OnEnter() override {
        //Scene::OnEnter();  // Call base class if there's relevant logic  
        audioManager.PlaySound("cabinMusic", true);
        audioManager.StopSound("Player_footstep");
    }

    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        backgroundParallaxManager->Update(dt);
        switch (currentPhase) {
        case RoomPhase::TakeOrderPhase:
            // Handle TakeOrderPhase logic
            dialogueManager->Update(dt, frame);
            if (dialogueManager->IsDialogueFinished()) {
                instructionText->SetContent("Press [E] to leave");
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

        // Allow leaving the room only in phases other than TakeOrderPhase
        if (currentPhase != RoomPhase::TakeOrderPhase && input.Get().GetKeyDown(GLFW_KEY_E)) {

            Application::Get().SetScene("Hallway");

            //Start timer
            timer->start(300);
            
        }

        // Handle dialogue progression
        if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {
            dialogueManager->PlayNextDialogue();
        }

    }

    void Render() override {
        Scene::Render(); // Renders GameObjects

        // Manually call DialogueManager's render function
        dialogueManager->Render();
    }

    void OnExit() override {
       // Scene::OnExit();  // Call base class if there's relevant logic
        audioManager.PlaySound("closeDoor",false);
        audioManager.PauseSound("cabinMusic");
    }

private:
    Input& input = Application::GetInput(); 
    Camera& camera = Application::GetCamera();
    unique_ptr<DialogueManager> dialogueManager;
    unique_ptr<ObjectsParallax> ObjectsparallaxManager;
    unique_ptr<BackgroundParallax> backgroundParallaxManager;


};