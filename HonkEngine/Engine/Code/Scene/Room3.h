#pragma once

#include "Scene.h"
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <cstdlib> 
#include <ctime> 
#include <functional>
#include "../Dialogue/Dialoguemanager.h"
#include "../Effects/ObjectsParallax.h"
#include "../Effects/BackgroundParallax.h"
#include "../GameObjects/Timer.h"
#include "../UI/UINormal.h"  
#include "../UI/UIButton.h" 
#include "../UI/UIElement.h"  
#include "../Input/Input.h"
#include "../Engine.h"
#include "../Effects/ShakingEffect.h"
#include "../Effects/TransitionEffects.h"

using namespace std;


class Room3 : public Scene {

    CharacterData* characterData = CharacterData::GetInstance();
    AudioManager& audioManager;

    Text* instructionText;
    GameStateManager& gameStateManager = GameStateManager::GetInstance();
    Door* door = DoorManager::GetInstance().GetDoorByName("Room3Door");
    Door* kichenDoor = DoorManager::GetInstance().GetDoorByName("KitchenDoor");

    UIElement* transitionObject;
    std::unique_ptr<TransitionEffects> transitionEffects;

    UIElement* movingLuggage;
    UIButton* movingLuggageInspect;
    UIElement* newspaper;
    UIButton* newspaperInspect;
    UIElement* messyClothes;
    UIButton* messyClothesInspect;

    unique_ptr<ShakingEffect> shakingEffect;

public:
    Room3() :audioManager(AudioManager::GetInstance()) {

        srand(time(NULL));


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
        UIElement* room = new UINormal("cabin1", "Assets/Images/Archibald/Archibald_Cabin.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.0f * sm, 10.55f * sm, 0.0f), true);
        UIElement* lamp = new UINormal("Lamp", "Assets/Images/Archibald/Archibald_Lamp.png", glm::vec3(1.3f, -0.5f, 0.0f), glm::vec3(0.84f * sm, 1.94f * sm, 0.0f), true);
        UIElement* luggage = new UINormal("Luggage", "Assets/Images/Archibald/Archibald_Bag.png", glm::vec3(6.2f, -1.9f, 0.0f), glm::vec3(1.59f * sm * 1.2f, 2.32f * sm * 1.2f, 0.0f), true);
        
        //Inspection Items
        movingLuggage = new UINormal("MovingLuggage", "Assets/Images/Archibald/Archibald_Inspection_MovingLuggage.png", glm::vec3(1.7f, -4.6f, 0.0f), glm::vec3(3.78f * sm * 1.2f, 2.38f * sm * 1.2f, 0.0f), true);
        newspaper = new UINormal("Newspaper", "Assets/Images/Archibald/Archibald_Inspection_Newspaper.png", glm::vec3(-3.139f, 0.224f, 0.0f), glm::vec3(1.09f * sm , 2.22f * sm, 0.0f), true);
       

        //Inspection Item Buttons
        movingLuggageInspect = new UIButton("MovingLuggageInspect", "Assets/Images/Archibald/Archibald_Inspection_MovingLuggage.png", glm::vec3(1.7f, -4.6f, 0.0f), glm::vec3(3.78f * sm * 1.2f, 2.38f * sm * 1.2f, 0.0f), true, false, "");
        movingLuggageInspect->SetHoverTexture("Assets/Images/Archibald/Archibald_Inspection_MovingLuggage_Highlight.png");
        movingLuggageInspect->SetOnClickAction([this]() {
            std::cout << "MovingLuggage button clicked." << std::endl;
            inspectingObject = "MovingLuggage";
            });

        newspaperInspect = new UIButton("NewspaperInspect", "Assets/Images/Archibald/Archibald_Inspection_Newspaper.png", glm::vec3(-3.139f, 0.224f, 0.0f), glm::vec3(1.09f * sm, 2.22f * sm, 0.0f), true, false, "");
        newspaperInspect->SetHoverTexture("Assets/Images/Archibald/Archibald_Inspection_Newspaper_Highlight.png");
        newspaperInspect->SetOnClickAction([this]() {
            std::cout << "Newspaper button clicked." << std::endl;
            inspectingObject = "Newspaper";
            });

        messyClothesInspect = new UIButton("MessyClothesInspect", "Assets/Images/Archibald/Archibald_Inspection_MessyClothes.png", glm::vec3(-3.58f, -1.99f, 0.0f), glm::vec3(6.6f * sm, 7.6f * sm, 0.0f), true, false, "");
        messyClothesInspect->SetHoverTexture("Assets/Images/Archibald/Archibald_Inspection_MessyClothes_Highlight.png");
        messyClothesInspect->SetOnClickAction([this]() {
            std::cout << "MessyClothes button clicked." << std::endl;
            inspectingObject = "MessyClothes";
            });

        movingLuggageInspect->setActiveStatus(false);
        newspaperInspect->setActiveStatus(false);
        messyClothesInspect->setActiveStatus(false);

         

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

        dialogueChoice1->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice2->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");
        dialogueChoice3->SetHoverTexture("Assets/Images/UI/DialogueChoiceBox_Hover.png");

        //Speak Icons
        UIElement* archibaldIcon = new UINormal("ArchibaldIcon", "Assets/Images/UI/Speaker_icon_Archibald.png", glm::vec3(4.18f, 3.5f, 0.0f), glm::vec3(1.4f, 1.57f, 0.0f), true);
        UIElement* waiterIcon = new UINormal("WaiterIcon", "Assets/Images/UI/Speaker_icon_Waiter.png", glm::vec3(4.18f, 3.43f, 0.0f), glm::vec3(1.23f, 1.4f, 0.0f), true);

        dialogueManager = make_unique<DialogueManager>("ArchibaldDialogue", dialogueBox, "Archibald_Normal");

       
        dialogueManager->LoadDialogues("Order","Assets/Dialogue/Archibald/Archibald_Order.xml");
        dialogueManager->LoadDialogues("Serve_OnTime", "Assets/Dialogue/Archibald/Archibald_Serve_OnTime.xml");
        dialogueManager->LoadDialogues("Serve_Late","Assets/Dialogue/Archibald/Archibald_Serve_Late.xml");

        

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

        m_gameObjects.push_back(movingLuggage);
        m_gameObjects.push_back(movingLuggageInspect);

        m_gameObjects.push_back(messyClothesInspect);
        m_gameObjects.push_back(archibaldNormal);
        m_gameObjects.push_back(archibaldHappy);
        m_gameObjects.push_back(archibaldDisappoint);
        m_gameObjects.push_back(archibaldUpset);
        m_gameObjects.push_back(archibaldSad);
        m_gameObjects.push_back(archibaldShy);

        m_gameObjects.push_back(newspaper);
        m_gameObjects.push_back(newspaperInspect);

        m_gameObjects.push_back(lamp);
        m_gameObjects.push_back(luggage);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(dialogueChoice1);
        m_gameObjects.push_back(dialogueChoice2);
        m_gameObjects.push_back(dialogueChoice3);
        m_gameObjects.push_back(archibaldIcon);
        m_gameObjects.push_back(waiterIcon);
        m_gameObjects.push_back(instructionText);
        m_gameObjects.push_back(transitionObject);

        //add Parallax Effects
        ObjectsparallaxManager = make_unique<ObjectsParallax>();
        backgroundParallaxManager = std::make_unique<BackgroundParallax>();

        float defaultLayer = 0.8f;
        float objectLayerOne = 0.85f;

        // Add objects to different layers
        ObjectsparallaxManager->AddObjectToLayer(room, defaultLayer);   // Layer 1
        ObjectsparallaxManager->AddObjectToLayer(lamp, objectLayerOne);   // Layer 1.5
        ObjectsparallaxManager->AddObjectToLayer(luggage, objectLayerOne);   // Layer 1.5
        ObjectsparallaxManager->AddObjectToLayer(movingLuggageInspect, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(newspaperInspect, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(movingLuggage, objectLayerOne);   // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(newspaper, objectLayerOne); // Layer 2
        ObjectsparallaxManager->AddObjectToLayer(messyClothesInspect, objectLayerOne); // Layer 2
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

        shakingEffect = std::make_unique<ShakingEffect>(0.05f, 100, 220, 6500);

        shakingEffect->AddObject(movingLuggage);
        shakingEffect->AddObject(movingLuggageInspect);
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

            if (characterData->getServeTimeLevel(Cabin::CABIN3) == ONTIME) {
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
            if (kitchen->getOptional() == MILK)
            {
                dialogueManager->LoadDialogues("MealReact_Tea_EarlGrey_WithMilk", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Assam_EarlGrey_WithMilk.xml");
                teaDialogueKey = "MealReact_Tea_EarlGrey_WithMilk";
            }			
            else
            {
                dialogueManager->LoadDialogues("MealReact_Tea_EarlGrey", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Assam_EarlGrey.xml");
                teaDialogueKey = "MealReact_Tea_EarlGrey";
            }
            break;
        case ASSAMTEA:
            if (kitchen->getOptional() == MILK)
            {
                dialogueManager->LoadDialogues("MealReact_Tea_Assam_WithMilk", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Assam_EarlGrey_WithMilk.xml");
                teaDialogueKey = "MealReact_Tea_Assam_WithMilk";
            }
            else
            {
                dialogueManager->LoadDialogues("MealReact_Tea_Assam", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Assam_EarlGrey.xml");
                teaDialogueKey = "MealReact_Tea_Assam";
            }
            break;
        case CHAMOMILETEA:
            dialogueManager->LoadDialogues("MealReact_Tea_Charmomile", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Other.xml");
            teaDialogueKey = "MealReact_Tea_Charmomile";
            break;
        case GREENTEA:
            dialogueManager->LoadDialogues("MealReact_Tea_GreenTea", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Tea_Other.xml");
            teaDialogueKey = "MealReact_Tea_GreenTea";
            break;
        }

        switch (kitchen->getSandwich()) {
        case SALMON:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Salmon", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Sandwich_Salmon.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Salmon";
            break;
        case BEEF:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Salmon", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Sandwich_Other.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Salmon";
            break;
        case EGG:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Egg", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Sandwich_Other.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Egg";
            break;
        case CUCUMBER:
            dialogueManager->LoadDialogues("MealReact_Sandwich_Cucumber", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Sandwich_Other.xml");
            sandwichDialogueKey = "MealReact_Sandwich_Cucumber";
            break;
        }

        switch (kitchen->getDessert()) {
        case ECLAIR:
            dialogueManager->LoadDialogues("MealReact_Dessert_Eclair", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Pastry_Other.xml");
            dessertDialogueKey = "MealReact_Dessert_Eclair";
            break;
        case MACARON:
            dialogueManager->LoadDialogues("MealReact_Dessert_Macaron", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Pastry_Other.xml");
            dessertDialogueKey = "MealReact_Dessert_Macaron";
            break;
        case TART:
            dialogueManager->LoadDialogues("MealReact_Dessert_Tart", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Pastry_LemonTart.xml");
            dessertDialogueKey = "MealReact_Dessert_Tart";
            break;
        case SCONE:
            dialogueManager->LoadDialogues("MealReact_Dessert_Scone", "Assets/Dialogue/Archibald/MealReact/Archibald_MealReact_Pastry_Other.xml");
            dessertDialogueKey = "MealReact_Dessert_Scone";
            break;
        }

        std::cout << "Tea Dialogue Key set to: " << teaDialogueKey << std::endl;
        std::cout << "Sandwich Dialogue Key set to: " << sandwichDialogueKey << std::endl;
        std::cout << "Dessert Dialogue Key set to: " << dessertDialogueKey << std::endl;
    }

    void SetScoredDialogue() {
        InteractionLevel level = characterData->getServeScoreLevel(Cabin::CABIN3);

        switch (level)
        {
        case LOW:
            dialogueManager->LoadDialogues("Score_Low_Start", "Assets/Dialogue/Archibald/MealResult/Archibald_MealResult_Low.xml");
            scoreDialogueKey = "Score_Low_Start";
            cout << "Score Low" << endl;
            break;
        case AVERAGE:
            dialogueManager->LoadDialogues("Score_Average_Start", "Assets/Dialogue/Archibald/MealResult/Archibald_MealResult_Average.xml");
            scoreDialogueKey = "Score_Average_Start";
            cout << "Score Average" << endl;
            break;
        case INFORMATIVE:
            dialogueManager->LoadDialogues("Score_Informative_Start", "Assets/Dialogue/Archibald/MealResult/Archibald_MealResult_Informative.xml");
            scoreDialogueKey = "Score_Informative_Start";
            cout << "Score Informative" << endl;
            break;
        default:
            break;
        }
    }
    void SetInteractDialogue() {


        InteractionLevel level = characterData->getInteractionLevel(Cabin::CABIN3);
        std::cout << "Retrieved interaction level: " << static_cast<int>(level) << std::endl;

        switch (level) {
        case InteractionLevel::LOW:
            std::cout << "Interaction level is LOW." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Low_Start", "Assets/Dialogue/Archibald/Low/Archibald_Low_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Low_MovingLuggage", "Assets/Dialogue/Archibald/Low/Archibald_Low_MovingLuggage.xml");
            dialogueManager->LoadDialogues("Inspect_Low_Newspaper", "Assets/Dialogue/Archibald/Low/Archibald_Low_Newspaper.xml");
            dialogueManager->LoadDialogues("Inspect_Low_MessyClothes", "Assets/Dialogue/Archibald/Low/Archibald_Low_MessyClothes.xml");
            dialogueManager->LoadDialogues("Inspect_Low_End", "Assets/Dialogue/Archibald/Low/Archibald_Low_End.xml");
            inspectStartDialogueKey = "Inspect_Low_Start";
            inspectMovingLuggageDialogueKey = "Inspect_Low_MovingLuggage";
            inspectNewspaperDialogueKey = "Inspect_Low_Newspaper";
            inspectMessyClothesDialogueKey = "Inspect_Low_MessyClothes";    
            inspectEndDialogueKey = "Inspect_Low_End";

            break;
        case InteractionLevel::AVERAGE:
            std::cout << "Interaction level is AVERAGE." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Average_Start", "Assets/Dialogue/Archibald/Average/Archibald_Average_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Average_MovingLuggage", "Assets/Dialogue/Archibald/Average/Archibald_Average_MovingLuggage.xml");
            dialogueManager->LoadDialogues("Inspect_Average_Newspaper", "Assets/Dialogue/Archibald/Average/Archibald_Average_Newspaper.xml");
            dialogueManager->LoadDialogues("Inspect_Average_MessyClothes", "Assets/Dialogue/Archibald/Average/Archibald_Average_MessyClothes.xml");
            dialogueManager->LoadDialogues("Inspect_Average_End", "Assets/Dialogue/Archibald/Average/Archibald_Average_End.xml");
            inspectStartDialogueKey = "Inspect_Average_Start";
            inspectMovingLuggageDialogueKey = "Inspect_Average_MovingLuggage";
            inspectNewspaperDialogueKey = "Inspect_Average_Newspaper";
            inspectMessyClothesDialogueKey = "Inspect_Average_MessyClothes";
            inspectEndDialogueKey = "Inspect_Average_End";

            break;
        case InteractionLevel::INFORMATIVE:
            std::cout << "Interaction level is INFORMATIVE." << std::endl;
            dialogueManager->LoadDialogues("Inspect_Informative_Start", "Assets/Dialogue/Archibald/Informative/Archibald_Informative_Start.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_MovingLuggage", "Assets/Dialogue/Archibald/Informative/Archibald_Informative_MovingLuggage.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_Newspaper", "Assets/Dialogue/Archibald/Informative/Archibald_Informative_Newspaper.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_MessyClothes", "Assets/Dialogue/Archibald/Informative/Archibald_Informative_MessyClothes.xml");
            dialogueManager->LoadDialogues("Inspect_Informative_End", "Assets/Dialogue/Archibald/Informative/Archibald_Informative_End.xml");
            inspectStartDialogueKey = "Inspect_Informative_Start";
            inspectMovingLuggageDialogueKey = "Inspect_Informative_MovingLuggage";
            inspectNewspaperDialogueKey = "Inspect_Informative_Newspaper";
            inspectMessyClothesDialogueKey = "Inspect_Informative_MessyClothes";
            inspectEndDialogueKey = "Inspect_Informative_End";
            break;
        }

    }


    void Update(float dt, long frame) override {

        Scene::Update(dt, frame);
        backgroundParallaxManager->Update(dt);
        ObjectsparallaxManager->UpdateLayers();
        shakingEffect->Update(dt);        
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
        if (gameStateManager.getGameState() != GameState::ROOM3_STATE) return;

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
            shakingEffect->StartShaking();
        }
    }

    void ManageInspectionState()
    {
        // Check if both objects have been inspected
        if (!isMovingLuggageInspected || !isNewspaperInspected || !isMessyClothesInspected) {
            InspectMovingLuggageDialogue();
            InspectNewspaperDialogue();
            InspectMessyClothesDialogue();
            NormalObjectToggle();
            SetInspectionObject();
        }

    }


    void NormalObjectToggle() {
        movingLuggage->setActiveStatus(!movingLuggageInspect->getActiveStatus());
        newspaper->setActiveStatus(!newspaperInspect->getActiveStatus());
    }

    void SetInspectionObject() {

        if (inspectingObject != "")
        {
            SetInstruction("Press [Space] or [Mouse] to continue");
            movingLuggageInspect->setActiveStatus(false);
            newspaperInspect->setActiveStatus(false);
            messyClothesInspect->setActiveStatus(false);
            ObjectsparallaxManager->DisableParallaxEffect();
        }
        else
        {
            SetInstruction("Select an object to inspect");
            movingLuggageInspect->setActiveStatus(!isMovingLuggageInspected);
            newspaperInspect->setActiveStatus(!isNewspaperInspected);
            messyClothesInspect->setActiveStatus(!isMessyClothesInspected);
            ObjectsparallaxManager->EnableParallaxEffect();
        }

    }

    void InspectMovingLuggageDialogue() {
        if (!inspectMovingLuggageDialogueSet && inspectingObject == "MovingLuggage") {
            dialogueManager->SetDialogueSet(inspectMovingLuggageDialogueKey);
            inspectMovingLuggageDialogueSet = true;
        }
        if (inspectMovingLuggageDialogueSet && dialogueManager->IsDialogueFinished(inspectMovingLuggageDialogueKey)) {
            std::cout << "MovingLuggage Inspection Completed" << std::endl;
            inspectMovingLuggageDialogueSet = false; 
            inspectingObject = ""; 
            isMovingLuggageInspected = true; 
            shakingEffect->StopShaking();
            CheckForEndDialogue();
        }

    }

    void InspectNewspaperDialogue() {
        if (!inspectNewspaperDialogueSet && inspectingObject == "Newspaper") {
            dialogueManager->SetDialogueSet(inspectNewspaperDialogueKey);
            inspectNewspaperDialogueSet = true;
        }
        if (inspectNewspaperDialogueSet && dialogueManager->IsDialogueFinished(inspectNewspaperDialogueKey)) {
            std::cout << "Letter Inspection Completed" << std::endl;
            inspectNewspaperDialogueSet = false; 
            inspectingObject = ""; 
            isNewspaperInspected = true; 
            CheckForEndDialogue();
        }

    }

    void InspectMessyClothesDialogue() {
		if (!inspectMessyClothesDialogueSet && inspectingObject == "MessyClothes") {
			dialogueManager->SetDialogueSet(inspectMessyClothesDialogueKey);
			inspectMessyClothesDialogueSet = true;
		}
		if (inspectMessyClothesDialogueSet && dialogueManager->IsDialogueFinished(inspectMessyClothesDialogueKey)) {
			std::cout << "MessyClothes Inspection Completed" << std::endl;
			inspectMessyClothesDialogueSet = false; 
			inspectingObject = ""; 
			isMessyClothesInspected = true; 
			CheckForEndDialogue();
		}

	}

    void CheckForEndDialogue() {
        if (isMovingLuggageInspected && isNewspaperInspected && isMessyClothesInspected  && !inspectEndDialogueSet) {
            std::cout << "All items inspected, moving to final dialogue." << std::endl;
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
        Scene::Render(); 
        dialogueManager->Render();
    }

    void OnExit() override {
        audioManager.PlaySound("slideDoor");
        audioManager.PauseSound("cabinMusic");
        BellManager::GetInstance().StopAllRinging();
        shakingEffect->StopShaking();
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
    string inspectMovingLuggageDialogueKey;
    string inspectNewspaperDialogueKey;
	string inspectMessyClothesDialogueKey;

    string inspectEndDialogueKey;

    bool orderDialogueSet = false;
    bool serveDialogueSet = false;
    bool teaDialogueSet = false;
    bool sandwichDialogueSet = false;
    bool dessertDialogueSet = false;
    bool scoreDialogueSet = false;
    bool inspectStartDialogueSet = false;
    bool inspectEndDialogueSet = false;
    bool inspectMovingLuggageDialogueSet = false;
    bool inspectNewspaperDialogueSet = false;
    bool inspectMessyClothesDialogueSet = false;


    bool isMovingLuggageInspected = false;
    bool isNewspaperInspected = false;
    bool isMessyClothesInspected = false;

    string inspectingObject;

};