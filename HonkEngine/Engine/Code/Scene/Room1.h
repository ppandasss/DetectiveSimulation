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
#include "../GameStateManager.h"
#include <memory>
#include "../GameObjects/CharacterData.h"
#include "../Effects/TransitionEffects.h"

using namespace std;


class Room1 : public Scene {

private:
    CharacterData* characterData = CharacterData::GetInstance();
    AudioManager& audioManager;
    Timer* timer;
    Text* instructionText;
    GameStateManager& gameStateManager = GameStateManager::GetInstance();
    Door* door = DoorManager::GetInstance().GetDoorByName("Room1Door");
    Door* kichenDoor = DoorManager::GetInstance().GetDoorByName("KitchenDoor");
   
    UIElement* transitionObject;
    std::unique_ptr<TransitionEffects> transitionEffects;

    //Inspect beject with highlight and no
    UIElement* cane;
    UIButton* caneInspect;
    UIElement* letter;
    UIButton* letterInspect;

public:
    Room1() :audioManager(AudioManager::GetInstance()) {

        timer = &Timer::GetInstance();

        audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3",Music,5.0f);
        audioManager.LoadSound("knockDoor", "Assets/Sounds/SFX_KnockDoor.mp3",SFX, 2.0f);
        audioManager.LoadSound("slideDoor", "Assets/Sounds/SFX_SlideDoor.mp3",SFX, 2.5f);
      


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


        transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
        transitionEffects = std::make_unique<TransitionEffects>(transitionObject);

        // Scale Multiplier to fit asset scale with screensize
        float sm = 1.23f;

        //Objects     
        UIElement* room = new UINormal("cabin1", "Assets/Images/Martha/Martha_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.60f * sm, 10.55f * sm, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Martha/Lamp.png", glm::vec3(-1.3f, -0.3f, 0.0f), glm::vec3(1.62f * sm, 2.25f * sm, 0.0f), true);
        UIElement* hat = new UINormal("Hat", "Assets/Images/Martha/Hat.png", glm::vec3(-1.1f, -1.22f, 0.0f), glm::vec3(3.12f * sm, 0.92f * sm, 0.0f), true);
        UIElement* bag = new UINormal("Bag", "Assets/Images/Martha/Bag.png", glm::vec3(-0.25f, -5.25f, 0.0f), glm::vec3(2.59f * sm * 1.2f, 1.64f * sm * 1.2f, 0.0f), true);

        //Inspection Items
        cane = new UINormal("Cane", "Assets/Images/Martha/Martha_Inspection_Cane.png", glm::vec3(-4.0f, -3.72f, 0.0f), glm::vec3(1.07f * sm * 1.2f, 3.7f * sm * 1.2f, 0.0f), true);
        letter = new UINormal("Letter", "Assets/Images/Martha/Martha_Inspection_Letter.png", glm::vec3(-2.15f, -5.9f, 0.0f), glm::vec3(1.13f * sm * 1.2f, 0.73f * sm * 1.2f, 0.0f), true);

        //Inspection Item Buttons
        caneInspect = new UIButton("Cane", "Assets/Images/Martha/Martha_Inspection_Cane.png", glm::vec3(-4.0f, -3.72f, 0.0f), glm::vec3(1.07f * sm * 1.2f, 3.7f * sm * 1.2f, 0.0f), true, false, "");
        caneInspect->SetHoverTexture("Assets/Images/Martha/Martha_Inspection_Cane_Highlight.png");
        caneInspect->SetOnClickAction([this]() {
            std::cout << "Cane button clicked." << std::endl;
            inspectingObject = "Cane";
            });


        letterInspect = new UIButton("Letter", "Assets/Images/Martha/Martha_Inspection_Letter.png", glm::vec3(-2.15f, -5.9f, 0.0f), glm::vec3(1.13f * sm * 1.2f, 0.73f * sm * 1.2f, 0.0f), true, false, "");
        letterInspect->SetHoverTexture("Assets/Images/Martha/Martha_Inspection_Letter_Highlight.png");
        letterInspect->SetOnClickAction([this]() {
            std::cout << "Letter button clicked." << std::endl;
            inspectingObject = "Letter";
            });
        caneInspect->setActiveStatus(false);
        letterInspect->setActiveStatus(false);


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
            glm::vec3(0.0f, -2.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice2 = new UIButton("DialogueChoiceBox2", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -3.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        UIButton* dialogueChoice3 = new UIButton("DialogueChoiceBox3", "Assets/Images/UI/DialogueChoiceBox.png",
            glm::vec3(0.0f, -1.8f, 0.0f), glm::vec3(7.47f * 0.9f, 1.07f * 0.9f, 0.0f),
            true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");

        dialogueChoice1->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice2->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice3->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");

        //Speak Icons
        UIElement* marthaIcon = new UINormal("MarthaIcon", "Assets/Images/UI/Speaker_icon_Martha.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(2.19f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("MarthaDialogue", dialogueBox, "Martha_Normal");
        dialogueManager->LoadDialogues("Order", "Assets/Dialogue/Martha/Martha_Order.xml");
        dialogueManager->LoadDialogues("Serve_OnTime", "Assets/Dialogue/Martha/Martha_Serve_OnTime.xml");
        dialogueManager->LoadDialogues("Serve_Late", "Assets/Dialogue/Martha/Martha_Serve_Late.xml");



        //Text
        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue dialogue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.6f);
        instructionText->SetPosition(glm::vec3(5.9f, -4.8f, 0.0f));
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

        m_gameObjects.push_back(caneInspect);
        m_gameObjects.push_back(letterInspect);

        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(marthaIcon);
        m_gameObjects.push_back(waiterIcon);
        m_gameObjects.push_back(instructionText);
        m_gameObjects.push_back(transitionObject);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayer = 0.85f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(lamp, objectLayer);   // Layer 1.5
        ObjectsparallaxManager->AddObjectToLayer(hat, objectLayer);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(bag, objectLayer);    // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(caneInspect, objectLayer);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(letterInspect, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(cane, objectLayer);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(letter, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaNormal, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaHappy, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaDisappoint, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaUpset, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaSad, objectLayer); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(marthaShy, objectLayer); // Layer 2

        //Scrolling effect for Background
        backgroundParallaxManager->AddBackgroundPair(0, background1a, background1b, 0.5f); // Layer 0, slower
        backgroundParallaxManager->AddBackgroundPair(1, background2a, background2b, 1.0f); // Layer 1, normal
        backgroundParallaxManager->AddBackgroundPair(2, background3a, background3b, 1.5f); // Layer 2, faster
        backgroundParallaxManager->AddBackgroundPair(3, background4a, background4b, 2.0f); // Layer 3, fastest
        backgroundParallaxManager->AddBackgroundPair(4, background5a, background5b, 2.5f); // Layer 4, fastest
        backgroundParallaxManager->AddBackgroundPair(5, background6a, background6b, 3.0f); // Layer 5, fastest


    }

    void OnEnter() override {

        transitionEffects->FadeIn(1.0f, [this]() {});

        audioManager.PlaySound("cabinMusic", true);
        if (gameStateManager.getRoomState() == RoomState::Prepare && KitchenData::GetInstance()->checkCompletePlate())
        {
            GameStateManager::GetInstance().SetRoomState(RoomState::Serve);
        }
        SetSequencesDialogue();
    }

    void SetSequencesDialogue()
    {
        switch (gameStateManager.getRoomState()) {
        case RoomState::Order:
            dialogueManager->SetDialogueSet("Order");
            orderDialogueKey = "Order";
            break;
        case RoomState::Serve:

            if (characterData->getServeTimeLevel(Cabin::CABIN1) == ONTIME) {
                serveDialogueKey = "Serve_OnTime";
            }
            else {
                serveDialogueKey = "Serve_Late";
            }
            dialogueManager->SetDialogueSet(serveDialogueKey);
            std::cout << "Setting serve dialogue: " << serveDialogueKey << std::endl;

            // Reset flags
            teaDialogueSet = false;
            sandwichDialogueSet = false;
            dessertDialogueSet = false;
            SetMealReactionDialogue();
            SetScoredDialogue();
            SetInteractDialogue();

            break;
        }
    }

    void SetMealReactionDialogue() {

        // Get instance of KitchenData to access the player's choices
        KitchenData* kitchen = KitchenData::GetInstance();

        // Determine the dialogue key based on the tea choice as an example
        switch (kitchen->getTea()) {

        case EARLGREYTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_EarlGrey", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Assam_EarlGrey.xml");
            teaDialogueKey = "MealReact_Tea_EarlGrey";
            break;
        case ASSAMTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_Assam", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Assam_EarlGrey.xml");
            teaDialogueKey = "MealReact_Tea_Assam";
            break;
        case CHAMOMILETEA:
            dialogueManager->LoadDialogues("MealReact_Tea_Charmomile", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_Chamomile.xml");
            teaDialogueKey = "MealReact_Tea_Charmomile";
            break;
        case GREENTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_GreenTea", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Tea_GreenTea.xml");
            teaDialogueKey = "MealReact_Tea_GreenTea";
            break;
        }

        switch (kitchen->getSandwich()) {
        case SALMON:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Salmon", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Salmon_Beef.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Salmon";
            break;
        case BEEF:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Beef", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Salmon_Beef.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Beef";
            break;
        case EGG:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Egg", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Egg.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Egg";
            break;
        case CUCUMBER:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Cucumber", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Sandwich_Cucumber.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Cucumber";
            break;
        }

        switch (kitchen->getDessert()) {
        case ECLAIR:
            dialogueManager->LoadDialogues("MealReact_Dessert_Eclair", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Eclair";
            break;
        case MACARON:
            dialogueManager->LoadDialogues("MealReact_Dessert_Macaron", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Macaron";
            break;
        case TART:
            dialogueManager->LoadDialogues("MealReact_Dessert_Tart", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Eclair_Macaron_Tart.xml");
            dessertDialogueKey = "MealReact_Dessert_Tart";
            break;
        case SCONE:
            dialogueManager->LoadDialogues("MealReact_Dessert_Scone", "Assets/Dialogue/Martha/MealReact/Martha_MealReact_Pastry_Scone.xml");
            dessertDialogueKey = "MealReact_Dessert_Scone";
            break;
        }

        std::cout << "Tea Dialogue Key set to: " << teaDialogueKey << std::endl;
        std::cout << "Sandwich Dialogue Key set to: " << sandwichDialogueKey << std::endl;
        std::cout << "Dessert Dialogue Key set to: " << dessertDialogueKey << std::endl;
    }

    void SetScoredDialogue() {
        InteractionLevel level = characterData->getServeScoreLevel(Cabin::CABIN1);

        switch (level)
        {
        case LOW:
            dialogueManager->LoadDialogues("Score_Low", "Assets/Dialogue/Martha/MealResult/Martha_MealResult_Low.xml");
            scoreDialogueKey = "Score_Low";
            cout << "Score Low" << endl;
            break;
        case AVERAGE:
            dialogueManager->LoadDialogues("Score_Average", "Assets/Dialogue/Martha/MealResult/Martha_MealResult_Average.xml");
            scoreDialogueKey = "Score_Average";
            cout << "Score Average" << endl;    
            break;
        case INFORMATIVE:
            dialogueManager->LoadDialogues("Score_Informative", "Assets/Dialogue/Martha/MealResult/Martha_MealResult_Informative.xml");
            scoreDialogueKey = "Score_Informative";
            cout << "Score Informative" << endl;
            break;
        default:
            break;
        }
    }
    void SetInteractDialogue() {


        InteractionLevel level = characterData->getInteractionLevel(Cabin::CABIN1);
        std::cout << "Retrieved interaction level: " << static_cast<int>(level) << std::endl;

        switch (level) {
        case InteractionLevel::LOW:
            std::cout << "Interaction level is LOW." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Low_Start", "Assets/Dialogue/Martha/Average/Martha_Average_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Low_Letter", "Assets/Dialogue/Martha/Average/Martha_Average_Letter.xml");
            dialogueManager->LoadDialogues("Inspect_Low_Cane", "Assets/Dialogue/Martha/Average/Martha_Average_Cane.xml");
            dialogueManager->LoadDialogues("Inspect_Low_End", "Assets/Dialogue/Martha/Average/Martha_Average_End.xml");
            inspectStartDialogueKey = "Inspect_Low_Start";
            inspectLetterDialogueKey = "Inspect_Low_Letter";
            inspectCaneDialogueKey = "Inspect_Low_Cane";
            inspectEndDialogueKey = "Inspect_Low_End";

            cout << "Interaction Low" << endl;
            break;
        case InteractionLevel::AVERAGE:
            std::cout << "Interaction level is AVERAGE." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Average_Start", "Assets/Dialogue/Martha/Average/Martha_Average_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Average_Letter", "Assets/Dialogue/Martha/Average/Martha_Average_Letter.xml");
            dialogueManager->LoadDialogues("Inspect_Average_Cane", "Assets/Dialogue/Martha/Average/Martha_Average_Cane.xml");
            dialogueManager->LoadDialogues("Inspect_Average_End", "Assets/Dialogue/Martha/Average/Martha_Average_End.xml");
            inspectStartDialogueKey = "Inspect_Average_Start";
            inspectLetterDialogueKey = "Inspect_Average_Letter";
            inspectCaneDialogueKey = "Inspect_Average_Cane";
            inspectEndDialogueKey = "Inspect_Average_End";

            cout << "Interaction Average" << endl;
            break;
        case InteractionLevel::INFORMATIVE:
            std::cout << "Interaction level is INFORMATIVE." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Informative_Start", "Assets/Dialogue/Martha/Informative/Martha_Informative_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_Letter", "Assets/Dialogue/Martha/Informative/Martha_Informative_Letter.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_Cane", "Assets/Dialogue/Martha/Informative/Martha_Informative_Cane.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_End", "Assets/Dialogue/Martha/Informative/Martha_Informative_End.xml");
            inspectStartDialogueKey = "Inspect_Informative_Start";
            inspectLetterDialogueKey = "Inspect_Informative_Letter";
            inspectCaneDialogueKey = "Inspect_Informative_Cane";
            inspectEndDialogueKey = "Inspect_Informative_End";

            cout << "Interaction Informative" << endl;
            break;
        }

    }



    void Update(float dt, long frame) {
        Scene::Update(dt, frame);
        backgroundParallaxManager->Update(dt);
        ObjectsparallaxManager->UpdateLayers();
        dialogueManager->Update(dt, frame);
        transitionEffects->Update(dt);

        UpdateDialogueProgress();
        HandleKeyInputs();
    }

    bool IsChoiceDialogue() {
        if (dialogueManager->IsCurrentDialogueQuestion()) {
            return true;
        }
        return false;
    }


    void UpdateDialogueProgress() {
        // Manage different room states
        if (gameStateManager.getGameState() != GameState::ROOM1_STATE) return;

        if (IsChoiceDialogue()) {
            SetInstruction("Select a choice to continue");
        }
        else {
            SetInstruction("Press [Space] or [Mouse] to continue");
        }

        switch (gameStateManager.getRoomState()) {
        case RoomState::Order:
            ManageOrderState();
            break;
        case RoomState::Serve:
            ManageServeState();
            break;
        case RoomState::Score:
            ManageScoreState();
            break;
        case RoomState::MealReact:
            ManageMealReactions();
            break;
        case RoomState::InspectionStart:
            ManageInspectionStartState();
            break;
        case RoomState::Inspection:
            ManageInspectionState();
            break;
        case RoomState::InspectionEnd:
		    ManageInspectionEndState();
			
			break;
        }
    }

    void ManageOrderState() {
        if (dialogueManager->IsDialogueFinished("Order")) {
            SetInstruction("Press [E] to leave");
            if (input.Get().GetKeyDown(GLFW_KEY_E)) {
                transitionEffects->FadeOut(1.0f, [this]() { gameStateManager.SetRoomState(Prepare); });
                
            }
        }
    }

    void ManageServeState() {
        //Set Serve Dialogue
        if (!serveDialogueSet) {
            PromptForNextDialogue(serveDialogueKey, serveDialogueSet);
        }
        else if (serveDialogueSet && dialogueManager->IsDialogueFinished(serveDialogueKey)) {
            //If serve end dialogue is finished, set the room state to MealReact
            gameStateManager.SetRoomState(RoomState::MealReact);
        }
    }

    void ManageMealReactions() {

        if (!teaDialogueSet && dialogueManager->IsDialogueFinished(serveDialogueKey) && !dessertDialogueSet) {
            PromptForNextDialogue(teaDialogueKey, teaDialogueSet);
        }
        else if (teaDialogueSet && !sandwichDialogueSet && dialogueManager->IsDialogueFinished(teaDialogueKey) && !dessertDialogueSet) {
            PromptForNextDialogue(sandwichDialogueKey, sandwichDialogueSet);
        }
        else if (sandwichDialogueSet && !dessertDialogueSet && dialogueManager->IsDialogueFinished(sandwichDialogueKey)) {
            PromptForNextDialogue(dessertDialogueKey, dessertDialogueSet);
        }


        if (teaDialogueSet && sandwichDialogueSet && dessertDialogueSet && dialogueManager->IsDialogueFinished(dessertDialogueKey)) {

            gameStateManager.SetRoomState(RoomState::Score);
        }
    }


    void ManageScoreState() {
        // Begin scoring dialogue
        if (!scoreDialogueSet) {
            PromptForNextDialogue(scoreDialogueKey, scoreDialogueSet);
        }
        else if (scoreDialogueSet && dialogueManager->IsDialogueFinished(scoreDialogueKey)) {
            gameStateManager.SetRoomState(RoomState::InspectionStart); // Transition to Inspection state
        }
    }


    void ManageInspectionStartState() {
        //Play InspectStartDialogue
        if (!inspectStartDialogueSet) {
            PromptForNextDialogue(inspectStartDialogueKey, inspectStartDialogueSet);
        }
        else if (inspectStartDialogueSet && dialogueManager->IsDialogueFinished(inspectStartDialogueKey)) {
           gameStateManager.SetRoomState(RoomState::Inspection);
        }

      
    }

    void ManageInspectionState()
    {
        // Check if both objects have been inspected
        if (!isCaneInspected || !isLetterInspected) {
            
            InspectCaneDialogue();
            InspectLetterDialogue();
            NormalObjectToggle();
            SetInspectionObject();
        }
       
    }


    void NormalObjectToggle() {
        cane->setActiveStatus(!caneInspect->getActiveStatus());
        letter->setActiveStatus(!letterInspect->getActiveStatus());
    }

    void SetInspectionObject() {

        if (inspectingObject != "")
        {
            SetInstruction("Press [Space] or [Mouse] to continue");
            caneInspect->setActiveStatus(false);
            letterInspect->setActiveStatus(false);  
            ObjectsparallaxManager->DisableParallaxEffect();
        }
        else
        {
            SetInstruction("Select an object to inspect");
            caneInspect->setActiveStatus(!isCaneInspected);
			letterInspect->setActiveStatus(!isLetterInspected);
			ObjectsparallaxManager->EnableParallaxEffect();
        }
     
    }

    void InspectCaneDialogue() {
        if (!inspectCaneDialogueSet && inspectingObject == "Cane") {
          dialogueManager->SetDialogueSet(inspectCaneDialogueKey);
          inspectCaneDialogueSet = true;
        }
        if (inspectCaneDialogueSet && dialogueManager->IsDialogueFinished(inspectCaneDialogueKey)) {
            std::cout << "Cane Inspection Completed" << std::endl;
            inspectCaneDialogueSet = false; // Reset the flag
            inspectingObject = ""; // Correct the assignment
            isCaneInspected = true; // Mark the cane as inspected
            CheckForEndDialogue();
        }

    }

    void InspectLetterDialogue() {
        if(!inspectLetterDialogueSet && inspectingObject == "Letter") {
			dialogueManager->SetDialogueSet(inspectLetterDialogueKey);
			inspectLetterDialogueSet = true;
		}
        if(inspectLetterDialogueSet && dialogueManager->IsDialogueFinished(inspectLetterDialogueKey)) {
            std::cout << "Letter Inspection Completed" << std::endl;
			inspectLetterDialogueSet = false; // Reset the flag
			inspectingObject = ""; // Correct the assignment
			isLetterInspected = true; // Mark the letter as inspected
			CheckForEndDialogue();
		}
  
    }

    void CheckForEndDialogue() {
        if (isCaneInspected && isLetterInspected && !inspectEndDialogueSet) {
            std::cout << "Both items inspected, moving to final dialogue." << std::endl;
            gameStateManager.SetRoomState(RoomState::InspectionEnd);
            
            
        }
    }

    void ManageInspectionEndState() {
		if (!inspectEndDialogueSet) {
            ObjectsparallaxManager->DisableParallaxEffect();
			PromptForNextDialogue(inspectEndDialogueKey, inspectEndDialogueSet);
		}
		else if (inspectEndDialogueSet && dialogueManager->IsDialogueFinished(inspectEndDialogueKey)) {
			gameStateManager.SetRoomState(RoomState::End);
            Application::Get().SetTimer(2000, [this]() { transitionEffects->FadeOut(1.0f, [this]() {}); }, false);
		}
	}
  
    void PromptForNextDialogue(const string& nextKey, bool& flag) {
        SetInstruction("Press [Space] or [Mouse] to continue");
        if (!flag && (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0))) {
            dialogueManager->SetDialogueSet(nextKey);
            flag = true;
        }
    }


    void SetInstruction(const string& message) {
        instructionText->SetContent(message);
    }

    void HandleKeyInputs() {
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
        BellManager::GetInstance().StopAllRinging();
    }



private:
    Input& input = Application::GetInput();
    Camera& camera = Application::GetCamera();
    unique_ptr<DialogueManager> dialogueManager;
    unique_ptr<ObjectsParallax> ObjectsparallaxManager;
    unique_ptr<BackgroundParallax> backgroundParallaxManager;
    string orderDialogueKey;
    string currentDialogueKey;
    string serveDialogueKey;
    string teaDialogueKey;
    string sandwichDialogueKey;
    string dessertDialogueKey;
    string scoreDialogueKey;
    string inspectStartDialogueKey;
    string inspectLetterDialogueKey;
    string inspectCaneDialogueKey;
    string inspectEndDialogueKey;

    bool orderDialogueSet = false;
    bool serveDialogueSet = false;
    bool teaDialogueSet = false;
    bool sandwichDialogueSet = false;
    bool dessertDialogueSet = false;
    bool scoreDialogueSet = false;
    bool inspectStartDialogueSet = false;
    bool inspectEndDialogueSet = false;
    bool inspectLetterDialogueSet = false;
    bool inspectCaneDialogueSet = false;

    bool isCaneInspected = false;
    bool isLetterInspected = false;



    string inspectingObject;

};
