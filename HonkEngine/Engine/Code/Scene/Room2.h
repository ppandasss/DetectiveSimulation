#pragma once

#include "Scene.h"
#include "../UI/UINormal.h"  
#include "../UI/UIButton.h" 
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
        UIElement* room = new UINormal("cabin2", "Assets/Images/Twins/Twin_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.0f * sm, 10.55f * sm, 0.0f), true);
        UIElement* medicineBack = new UINormal("MedicineBack", "Assets/Images/Twins/Twin_Inspection_MedicineBack.png", glm::vec3(-6.7f, -2.6f, 0.0f), glm::vec3(3.44f / 4 * sm, 3.96f / 4 * sm, 0.0f), true);


        //Inspection Items
        UIElement* medicineFront = new UINormal("MedicineFront", "Assets/Images/Twins/Twin_Inspection_MedicineFront.png", glm::vec3(1.7f, -4.6f, 0.0f), glm::vec3(4.56f / 3 * sm, 1.76f / 3 * sm, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Twins/Twin_Inspection_Hat.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(4.89f / 4 * sm, 4.05f / 4 * sm, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Twins/Twin_Inspection_Bag.png", glm::vec3(-3.139f, 0.224f, 0.0f), glm::vec3(5.58f / 3 * sm, 4.92f / 3 * sm, 0.0f), true);


        //Inspection Item Buttons
        UIButton* medicineFrontInspect = new UIButton("MedicineFront", "Assets/Images/Twins/Twin_Inspection_MedicineFront.png", glm::vec3(1.7f, -4.6f, 0.0f), glm::vec3(4.56f / 3 * sm, 1.76f / 3 * sm, 0.0f), true, false, "");
        medicineFrontInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_MedicineFront_Highlight.png");

        UIButton* hatInspect = new UIButton("HatInspect", "Assets/Images/Twins/Twin_Inspection_Hat.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(4.89f / 4 * sm, 4.05f / 4 * sm, 0.0f), true, false, "");
        hatInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_Hat_Highlight.png");

        UIButton* bagInspect = new UIButton("BagInspect", "Assets/Images/Twins/Twin_Inspection_Bag.png", glm::vec3(-3.139f, 0.224f, 0.0f), glm::vec3(5.58f / 3 * sm, 4.92f / 3 * sm, 0.0f), true, false, "");
        bagInspect->SetHoverTexture("Assets/Images/Twins/Twin_Inspection_Bag_Highlight.png");

        //UIs
        //Speaker Sprite emotion
        UIElement* nathanielNormal = new UINormal("Nathaniel_Normal", "Assets/Images/Twins/Nathaniel_Normal.png", glm::vec3(-5.0f, -1.5f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielHappy = new UINormal("Nathaniel_Happy", "Assets/Images/Twins/Nathaniel_Happy.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielDisappoint = new UINormal("Nathaniel_Disappoint", "Assets/Images/Twins/Nathaniel_Disappoint.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielUpset = new UINormal("Nathaniel_Upset", "Assets/Images/Twins/Nathaniel_Upset.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielSad = new UINormal("Nathaniel_Sad", "Assets/Images/Twins/Nathaniel_Sad.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);
        UIElement* nathanielShy = new UINormal("Nathaniel_Shy", "Assets/Images/Twins/Nathaniel_Shy.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(4.72f * sm, 6.19f * sm, 0.0f), true);

        UIElement* evelynNormal = new UINormal("Evelyn_Normal", "Assets/Images/Twins/Evelyn_Normal.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynHappy = new UINormal("Evelyn_Happy", "Assets/Images/Twins/Evelyn_Happy.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynDisappoint = new UINormal("Evelyn_Disappoint", "Assets/Images/Twins/Evelyn_Disappoint.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynUpset = new UINormal("Evelyn_Upset", "Assets/Images/Twins/Evelyn_Upset.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynSad = new UINormal("Evelyn_Sad", "Assets/Images/Twins/Evelyn_Sad.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);
        UIElement* evelynShy = new UINormal("Evelyn_Shy", "Assets/Images/Twins/Evelyn_Shy.png", glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(3.06f * sm, 5.87f * sm, 0.0f), true);

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
        UIElement* nathanielIcon = new UINormal("NathanielIcon", "Assets/Images/UI/Speaker_icon_Nathaniel.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(1.45f, 1.51f, 0.0f), true);
        UIElement* eyelynIcon = new UINormal("EvelynIcon", "Assets/Images/UI/Speaker_icon_Evelyn.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(1.57f, 1.5f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("TwinDialogue", dialogueBox, "Nathaniel_Normal");
        dialogueManager->LoadDialogues("Order", "Assets/Dialogue/Twin/Twin_Order.xml");
        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(5.9f, -4.8f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        //Add SpeakSprite
        dialogueManager->AddSpeakerSprite("Nathaniel_Normal", nathanielNormal);
        dialogueManager->AddSpeakerSprite("Nathaniel_Happy", nathanielHappy);
        dialogueManager->AddSpeakerSprite("Nathaniel_Disappoint", nathanielDisappoint);
        dialogueManager->AddSpeakerSprite("Nathaniel_Upset", nathanielUpset);
        dialogueManager->AddSpeakerSprite("Nathaniel_Sad", nathanielSad);
        dialogueManager->AddSpeakerSprite("Nathaniel_Shy", nathanielShy);

        dialogueManager->AddSpeakerSprite("Evelyn_Normal", evelynNormal);
        dialogueManager->AddSpeakerSprite("Evelyn_Happy", evelynHappy);
        dialogueManager->AddSpeakerSprite("Evelyn_Disappoint", evelynDisappoint);
        dialogueManager->AddSpeakerSprite("Evelyn_Upset", evelynUpset);
        dialogueManager->AddSpeakerSprite("Evelyn_Sad", evelynSad);
        dialogueManager->AddSpeakerSprite("Evelyn_Shy", evelynShy);

        //Add SpeakerIcon
        dialogueManager->AddSpeakerIcon("N", nathanielIcon);
        dialogueManager->AddSpeakerIcon("E", eyelynIcon);
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
        m_gameObjects.push_back(medicineBack);

        m_gameObjects.push_back(hat);
        m_gameObjects.push_back(hatInspect);

        m_gameObjects.push_back(bag);
        m_gameObjects.push_back(bagInspect);

        m_gameObjects.push_back(nathanielNormal);
        m_gameObjects.push_back(nathanielHappy);
        m_gameObjects.push_back(nathanielDisappoint);
        m_gameObjects.push_back(nathanielUpset);
        m_gameObjects.push_back(nathanielSad);
        m_gameObjects.push_back(nathanielShy);

        m_gameObjects.push_back(medicineFront);
        m_gameObjects.push_back(medicineFrontInspect);

        m_gameObjects.push_back(evelynNormal);
        m_gameObjects.push_back(evelynHappy);
        m_gameObjects.push_back(evelynDisappoint);
        m_gameObjects.push_back(evelynUpset);
        m_gameObjects.push_back(evelynSad);
        m_gameObjects.push_back(evelynShy);


        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(nathanielIcon);
        m_gameObjects.push_back(eyelynIcon);
        m_gameObjects.push_back(waiterIcon);
        m_gameObjects.push_back(instructionText);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.83f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(hat, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayerOne);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(medicineBack, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(medicineFront, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielSad, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(nathanielShy, objectLayerOne); // Layer 2

        ObjectsparallaxManager->AddObjectToLayer(evelynNormal, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynHappy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynDisappoint, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynUpset, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynShy, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(evelynShy, objectLayerOne); // Layer 2

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
            if (dialogueManager->IsDialogueFinished("Order")) {
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