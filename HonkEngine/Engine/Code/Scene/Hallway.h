#pragma once

#include "Scene.h"
#include <memory>

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../GameObjects/Player.h"
#include "../Text/TextRenderer.h"
#include "../Text/Text.h"
#include"../Audio/AudioManager.h"	
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../UI/UINormal.h"
#include "../UI/UIElement.h"
#include "../GameObjects/Book.h"
#include "../UI/UIButtonEmpty.h"
#include "../GameObjects/Door.h"
#include "../GameObjects/DoorsManager.h"
#include "../GameObjects/OrderData.h"
#include "../GameObjects/Timer.h"
#include "../Effects/BackgroundParallax.h"

class Hallway : public Scene
{

private:

	std::unique_ptr<TextRenderer> textRenderer;
	std::unique_ptr<BackgroundParallax> BackgroundparallaxManager;
	AudioManager& audioManager;

	Player* player;
	Book* Journal;

	Text* orderNoText;
	Text* teaOrderText;
	Text* sandwichOrderText;
	Text* pastryOrderText;
	UIElement* orderPaper;

	Text* timerText;
    UIElement* timerUI;
	Text* instructionText;
public:
	Hallway() :audioManager(AudioManager::GetInstance())
	{
		/*--------------------------------------------------------------🔊LOAD AUDDIO🔊------------------------------------------------------------------------------------------------------- */
		audioManager.LoadSound("hallwayMusic", "Assets/Sounds/Music/BGmusic_Corridor_NoTimer.mp3", 0.15f);
		audioManager.LoadSound("trainAmbience", "Assets/Sounds/Ambience/Ambience_Train.mp3", 0.1f);


		/*--------------------------------------------------------------📦CREATE GAMEOBJECT📦------------------------------------------------------------------------------------------------------- */
		/*-------------------------------------------------------------🌲CREATE ENVIRONMENT🌲------------------------------------------------------------------------------------------------------- */
		GameObject* background1a = new RenderGameObject("BG1", "Assets/Images/BG/Cabin_Background_01.png");
		GameObject* background2a = new RenderGameObject("BG2", "Assets/Images/BG/Cabin_Background_02.png");
		GameObject* background1b = new RenderGameObject("BG3", "Assets/Images/BG/Cabin_Background_01.png");
		GameObject* background2b = new RenderGameObject("BG4", "Assets/Images/BG/Cabin_Background_02.png");

		background1a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f));background1a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f)); 
		background2a->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2a->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
		background1b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background1b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));
		background2b->SetScale(glm::vec3(76.6f, 10.8f, 0.0f)); background2b->SetPosition(glm::vec3(76.6f, 3.0f, 0.0f));

		BackgroundparallaxManager = std::make_unique<BackgroundParallax>();

		BackgroundparallaxManager->AddBackgroundPair(0, background1a, background1b, 0.5f);
		BackgroundparallaxManager->AddBackgroundPair(1, background2a, background2b, 1.0f);


		GameObject* hallway = new RenderGameObject("Cabin", "Assets/Images/Corridor/Corridor_Background.png");
		GameObject* hallwaylights = new RenderGameObject("CabinLights", "Assets/Images/Corridor/Corridor_Light.png");

		GameObject* bellCabin1 = new RenderGameObject("bellCabin1", "Assets/Images/Corridor/Bell_Normal.png");
		GameObject* bellCabin2 = new RenderGameObject("bellCabin2", "Assets/Images/Corridor/Bell_Normal.png");
		GameObject* bellCabin3 = new RenderGameObject("bellCabin3", "Assets/Images/Corridor/Bell_Normal.png");
		GameObject* bellCabin4 = new RenderGameObject("bellCabin4", "Assets/Images/Corridor/Bell_Normal.png");

		

		/*-------------------------------------------------------------🚪CREATE DOORS🚪------------------------------------------------------------------------------------------------------- */
		GameObject* roomdoor1Highlight = new RenderGameObject("RoomdoorHighlight", "Assets/Images/Corridor/PassengerDoor_Highlight.png");
		GameObject* roomdoor2Highlight = new RenderGameObject("RoomdoorHighlight", "Assets/Images/Corridor/PassengerDoor_Highlight.png");
		GameObject* roomdoor3Highlight = new RenderGameObject("RoomdoorHighlight", "Assets/Images/Corridor/PassengerDoor_Highlight.png");
		GameObject* roomdoor4Highlight = new RenderGameObject("RoomdoorHighlight", "Assets/Images/Corridor/PassengerDoor_Highlight.png");
		GameObject* kitchendoorHighlight = new RenderGameObject("KitchendoorHighlight", "Assets/Images/Corridor/KitchenDoor_Highlight.png");

		Door* room1Door = new Door("Room1Door", roomdoor1Highlight, glm::vec3(-17.58f, -0.632f, 0.0f), glm::vec3(2.29f * 1.2f, 4.65f * 1.2f, 0.0f), "Room1");
		DoorManager::GetInstance().AddDoor(room1Door);

		Door* room2Door = new Door("Room2Door", roomdoor2Highlight, glm::vec3(-8.588f, -0.632f, 0.0f), glm::vec3(2.29f * 1.2f, 4.65f * 1.2f, 0.0f), "Room1");
		DoorManager::GetInstance().AddDoor(room2Door);

		Door* room3Door = new Door("Room3Door", roomdoor3Highlight, glm::vec3(0.38f, -0.632f, 0.0f), glm::vec3(2.29f * 1.2f, 4.65f * 1.2f, 0.0f), "Room2");
		DoorManager::GetInstance().AddDoor(room3Door);

		Door* room4Door = new Door("Room4Door", roomdoor4Highlight, glm::vec3(9.358f, -0.632f, 0.0f), glm::vec3(2.29f * 1.2f, 4.65f * 1.2f, 0.0f), "Room1");
		DoorManager::GetInstance().AddDoor(room4Door);

		Door* kitchenDoor = new Door("KitchenDoor", kitchendoorHighlight, glm::vec3(18.31f, -0.629f, 0.0f), glm::vec3(2.29f * 1.2f, 4.65f * 1.2f, 0.0f), "Kitchen");
		DoorManager::GetInstance().AddDoor(kitchenDoor);
		

		Journal = new Book();
		
	 

		//activate clue in journal
		/*JournalData::GetInstance()->ActivateClue(CLUE_CABIN1, 0);
		JournalData::GetInstance()->ActivateClue(CLUE_CABIN1, 1);*/

		/*-------------------------------------------------------------🎮CREATE PLAYER🎮------------------------------------------------------------------------------------------------------- */

		player = new Player("waiter", "Assets/Images/Waiter_Sprite_Walk.png", 2, 8, Journal);

		/*-------------------------------------------------------------💬CREATE TEXT💬------------------------------------------------------------------------------------------------------- */

		
		orderNoText = new Text("orderNo", "", "Assets/Fonts/mvboli.ttf",true);
		teaOrderText = new Text("TeaOrder", "", "Assets/Fonts/mvboli.ttf", true);
		sandwichOrderText = new Text("sandwichOrder", "", "Assets/Fonts/mvboli.ttf", true);
		pastryOrderText = new Text("PastryOrder", "", "Assets/Fonts/mvboli.ttf", true);

		// OrderData Setup
		OrderData& orderData = OrderData::GetInstance();
		orderData.AddObserver([this, &orderData]() {
			this->orderNoText->SetContent(orderData.GetRoomNumber());
			this->teaOrderText->SetContent(orderData.GetTeaOrder());
			this->sandwichOrderText->SetContent(orderData.GetSandwichOrder());
			this->pastryOrderText->SetContent(orderData.GetPastryOrder());
			});

		//Timer Setup
		Timer& timer = Timer::GetInstance();
		timerText = new Text("timerText", "", "Assets/Fonts/Jibril.ttf", true);
		timer.Initialize(timerText);

		timer.AddObserver([this, &timer]() {
			this->timerText->SetContent(timer.GetTime());
		});

		instructionText = new Text("instruction", "Press [E] to enter","Assets/Fonts/mvboli.ttf", true);
		instructionText->SetScale(0.6f);
		instructionText->SetPosition(glm::vec3(7.52f, -4.3f, 0.0f));
		instructionText->SetColor(glm::vec3(1, 1, 1));
		

		/*-------------------------------------------------------------💬CREATE UI💬------------------------------------------------------------------------------------------------------- */
		 orderPaper = new UINormal("OrderPaper", "Assets/Images/UI/OrderPaper.png",
			glm::vec3(-7.65f, 4.0f, 0.0f), glm::vec3(3.55f, 2.54f, 0.0f), true); // Start inactive
		orderData.SetOrderPaper(orderPaper);
		 timerUI = new UINormal("Timer", "Assets/Images/UI/Timer.png", glm::vec3(7.3f, 5.1f, 0.0f), glm::vec3(4.37f, 3.13f, 0.0f), true);
		timer.SetTimerUI(this->timerUI);
		UIElement* screenUI = new UINormal("ScreenUI", "Assets/Images/ScreenUI.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f * 1.19f, 9.0f * 1.19f, 0.0f), true);
		UIButton* journalButton = new UIButton("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-8.32f, -4.8f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), true, false, "");
		journalButton->SetOnClickAction([this]() { Journal->drawBook(); });

		

		//TO TEST DRAW EMPTY UI
		/*GameObject* box = new RenderGameObject("textbox", "Assets/Images/Square_Border.png");
		box->SetScale(glm::vec3(2.8f, 5.7f, 0.0f));
		box->SetPosition(glm::vec3(18.35f, -0.55f, 0.0f));
		m_gameObjects.push_back(box);*/

		/*-------------------------------------------------------------➡️SET TRANSFORMATION➡️------------------------------------------------------------------------------------------------------- */

		hallway->SetScale(glm::vec3(50.00f, 10.8f, 0.0f));
		hallway->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		hallwaylights->SetScale(glm::vec3(50.0f, 10.8f, 0.0f));
		hallwaylights->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));

		bellCabin1->SetScale(glm::vec3(1.6f * 1.2f, 1.6f * 1.2f, 0.0f)); bellCabin1->SetPosition(glm::vec3(-16.54f, 1.49f, 0.0f));
		bellCabin2->SetScale(glm::vec3(1.6f * 1.2f, 1.6f * 1.2f, 0.0f)); bellCabin2->SetPosition(glm::vec3(-7.54f, 1.49f, 0.0f));
		bellCabin3->SetScale(glm::vec3(1.6f * 1.2f, 1.6f * 1.2f, 0.0f)); bellCabin3->SetPosition(glm::vec3(1.41f, 1.49f, 0.0f));
		bellCabin4->SetScale(glm::vec3(1.6f * 1.2f, 1.6f * 1.2f, 0.0f)); bellCabin4->SetPosition(glm::vec3(10.44f, 1.49f, 0.0f));

		
		orderNoText->SetPosition(glm::vec3(-8.8f, 4.5f, 0.0f));
		orderNoText->SetColor(glm::vec3(0.5, 0, 0));
		teaOrderText->SetPosition(glm::vec3(-7.1f, 4.5f, 0.0f));
		teaOrderText->SetScale(0.6f);
		sandwichOrderText->SetPosition(glm::vec3(-7.6f, 3.9f, 0.0f));
		sandwichOrderText->SetScale(0.55f);
		pastryOrderText->SetPosition(glm::vec3(-7.6f, 3.28f, 0.0f));
		pastryOrderText->SetScale(0.55f);

		timerText->SetPosition(glm::vec3(6.65f, 4.12f, 0.0f));
		timerText->SetColor(glm::vec3(0.78039, 0.72549, 0.44314));
		timerText->SetScale(1.45f);

		/*--------------------------------------------------------------✅PUSH BACK✅------------------------------------------------------------------------------------------------------- */
		//Environment
		m_gameObjects.push_back(background1a);
		m_gameObjects.push_back(background1b);
		m_gameObjects.push_back(background2a);
		m_gameObjects.push_back(background2b);
		m_gameObjects.push_back(hallway);

		//Doors
		m_gameObjects.push_back(kitchenDoor);
		m_gameObjects.push_back(room1Door);
		m_gameObjects.push_back(room2Door);
		m_gameObjects.push_back(room3Door);
		m_gameObjects.push_back(room4Door);
		m_gameObjects.push_back(roomdoor1Highlight);
		m_gameObjects.push_back(roomdoor2Highlight);
		m_gameObjects.push_back(roomdoor3Highlight);
		m_gameObjects.push_back(roomdoor4Highlight);
		m_gameObjects.push_back(kitchendoorHighlight);

		//Bells
		m_gameObjects.push_back(bellCabin1);
		m_gameObjects.push_back(bellCabin2);
		m_gameObjects.push_back(bellCabin3);
		m_gameObjects.push_back(bellCabin4);

		m_gameObjects.push_back(player);
		m_gameObjects.push_back(hallwaylights);

		//UIs
		m_gameObjects.push_back(journalButton);
		m_gameObjects.push_back(timerUI);
		m_gameObjects.push_back(orderPaper);

		
		//UITexts
		m_gameObjects.push_back(orderNoText);
		m_gameObjects.push_back(teaOrderText);
		m_gameObjects.push_back(sandwichOrderText);
		m_gameObjects.push_back(pastryOrderText);
		m_gameObjects.push_back(timerText);
		m_gameObjects.push_back(instructionText);

		//Journal
		m_gameObjects.push_back(Journal);
		//Journal->closeBook();

	}

	void OnEnter() override {
		//Scene::OnEnter();
		audioManager.PlaySound("hallwayMusic", true);
		audioManager.PlaySound("trainAmbience", true);
	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); // Call the base class update

		BackgroundparallaxManager->Update(dt);

		Timer& timer = Timer::GetInstance();
	    timer.Update(dt);
		

		// Retrieve the player object by name

		if (player) {
			// Get the player's position
			glm::vec3 playerPos = player->GetPosition();
			// Get the camera and update its position
			Camera& camera = Application::GetCamera();

			const float leftBound = -12.74f;
			const float rightBound = 12.91f;

			// Set the target position for the camera
			float targetX = std::max(leftBound, std::min(playerPos.x, rightBound));

			// Smoothing factor for camera movement
			float smoothingFactor = 0.05f; // Experiment with different values

			// Smoothly interpolate the camera's x position towards the target
			float interpolatedX = camera.GetPosX() + smoothingFactor * (targetX - camera.GetPosX());

			// Set the new camera position
			camera.SetPosition(targetX, camera.GetPosY());

			bool isNearDoor = DoorManager::GetInstance().CheckDoorCollisions(player->GetPosition(), player->GetScale(), [](const std::string& sceneName) {});
			instructionText->setActiveStatus(isNearDoor);

		}

	}

	void OnExit() override {
		//Scene::OnExit(); 
		audioManager.PauseSound("hallwayMusic");
		audioManager.StopSound("Player_footsteps");
	}


};





