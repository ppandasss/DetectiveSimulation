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


class Room2 : public Scene {

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
    Room2() :audioManager(AudioManager::GetInstance()) {

        timer = &Timer::GetInstance();

        audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3", 4.0f);
        audioManager.LoadSound("knockDoor", "Assets/Sounds/SFX_KnockDoor.mp3", 2.0f);
        audioManager.LoadSound("slideDoor", "Assets/Sounds/SFX_SlideDoor.mp3", 2.5f);

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
        background4a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4a->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
        background5a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5a->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
        background6a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6a->SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));

        background1b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background2b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background3b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background3b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
        background4b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background4b->SetPosition(glm::vec3(76.6f, 2.0f, 0.0f));
        background5b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background5b->SetPosition(glm::vec3(76.6f, 2.0f, 0.0f));
        background6b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));  background6b->SetPosition(glm::vec3(76.6f, 1.0f, 0.0f));


        // Scale Multiplier to fit asset scale with screensize
        float sm = 1.23f;

        //Objects     
        UIElement* room = new UINormal("cabin1", "Assets/Images/Archibald/Archibald_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.0f * sm, 10.55f * sm, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Archibald/Archibald_Lamp.png", glm::vec3(1.3f, -0.5f, 0.0f), glm::vec3(0.84f * sm, 1.94f * sm, 0.0f), true);
        UIElement* luggage = new UINormal("Luggage", "Assets/Images/Archibald/Item_Archibald_Luggage.png", glm::vec3(6.2f, -1.9f, 0.0f), glm::vec3(1.59f * sm * 1.2f, 2.32f * sm * 1.2f, 0.0f), true);
        
        //Inspection Items
        UIElement* movingLuggage = new UINormal("MovingLuggage", "Assets/Images/Archibald/Inspection_Archibald_MovingLuggage.png", glm::vec3(1.7f, -4.6f, 0.0f), glm::vec3(3.78f * sm * 1.2f, 2.38f * sm * 1.2f, 0.0f), true);
        //UIElement* archibaldInspect = new UINormal("ArchibaldInspect", "Assets/Images/Martha/Inspection_Cane.png", glm::vec3(-4.0f, -3.72f, 0.0f), glm::vec3(1.07f * sm * 1.2f, 3.7f * sm * 1.2f, 0.0f), true);
        //UIElement* newspaper = new UINormal("Newspaper", "Assets/Images/Martha/Inspection_Letter.png", glm::vec3(-2.15f, -5.9f, 0.0f), glm::vec3(1.13f * sm * 1.2f, 0.73f * sm * 1.2f, 0.0f), true);

        //UIs
        //Speaker Sprite emotion
        UIElement* archibaldNormal = new UINormal("Archibald_Normal", "Assets/Images/Archibald/Archibald_Normal.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);
        UIElement* archibaldHappy = new UINormal("Archibald_Happy", "Assets/Images/Archibald/Archibald_Happy.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);
        UIElement* archibaldDisappoint = new UINormal("Archibald_Disappoint", "Assets/Images/Archibald/Archibald_Disappoint.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);
        UIElement* archibaldUpset = new UINormal("Archibald_Upset", "Assets/Images/Archibald/Archibald_Upset.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);
        UIElement* archibaldSad = new UINormal("Archibald_Sad", "Assets/Images/Archibald/Archibald_Sad.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);
        UIElement* archibaldShy = new UINormal("Archibald_Shy", "Assets/Images/Archibald/Archibald_Shy.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.46f * sm, 7.32f * sm, 0.0f), true);

        //Dialogue Box
        UIButton* dialogueBox = new UIButton("DialogueBox", "Assets/Images/UI/DialogueBox.png",
            glm::vec3(0.0f, 3.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono.ttf");
        //Choices
        UIButton* dialogueChoice1 = new UIButton("DialogueChoiceBox1", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -2.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice2 = new UIButton("DialogueChoiceBox2", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -3.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice3 = new UIButton("DialogueChoiceBox3", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -1.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        //Speak Icons
        UIElement* archibaldIcon = new UINormal("ArchibaldIcon", "Assets/Images/UI/Speaker_icon_Archibald.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(1.4f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("ArchibaldDialogue", dialogueBox,
            "Assets/Dialogue/Archibald/Archibald_Order.xml", "Archibald_Normal");

        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(5.9f, -4.8f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        //Add SpeakSprite
        dialogueManager->AddSpeakerSprite("Archibald_Normal", archibaldNormal);
        dialogueManager->AddSpeakerSprite("Archibald_Happy", archibaldHappy);
        dialogueManager->AddSpeakerSprite("Archibald_Disappoint", archibaldDisappoint);
        dialogueManager->AddSpeakerSprite("Archibald_Upset", archibaldUpset);
        dialogueManager->AddSpeakerSprite("Archibald_Sad", archibaldSad);
        dialogueManager->AddSpeakerSprite("Archibald_Shy", archibaldShy);
        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("A", archibaldIcon);
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
        //m_gameObjects.push_back(archibaldInspect);
        m_gameObjects.push_back(movingLuggage);
        //m_gameObjects.push_back(newspaper);
        m_gameObjects.push_back(archibaldNormal);
        m_gameObjects.push_back(archibaldHappy);
        m_gameObjects.push_back(archibaldDisappoint);
        m_gameObjects.push_back(archibaldUpset);
        m_gameObjects.push_back(archibaldSad);
        m_gameObjects.push_back(archibaldShy);
        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(luggage);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(archibaldIcon);
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
        //ObjectsparallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        //ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        //ObjectsparallaxManager->AddObjectToLayer(cane, objectLayerOne);   // Layer 2
        //ObjectsparallaxManager->AddObjectToLayer(letter, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldSad, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(archibaldShy, objectLayerOne); // Layer 2

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
        audioManager.PlaySound("knockDoor");
        audioManager.StopSound("Player_footsteps");
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
        audioManager.PlaySound("slideDoor");
        audioManager.PauseSound("cabinMusic");
    }

private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    unique_ptr<DialogueManager> dialogueManager;
    unique_ptr<ObjectsParallax> ObjectsparallaxManager;
    unique_ptr<BackgroundParallax> backgroundParallaxManager;


};