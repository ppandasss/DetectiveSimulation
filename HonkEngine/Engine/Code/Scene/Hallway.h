#pragma once

#include "Scene.h"
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

#include "../GameObjects/CharacterData.h";

class Hallway : public Scene
{

private:
	std::unique_ptr<TextRenderer> textRenderer;
	AudioManager& audioManager;
	Book* Journal;

	Text* orderNoText;
	Text* teaOrderText;
	Text* sandwichOrderText;
	Text* pastryOrderText;

	Text* timerText;

	CharacterData* char_data;
	
public:
	Hallway() :audioManager(AudioManager::GetInstance())
	{
		/*--------------------------------------------------------------🔊LOAD AUDDIO🔊------------------------------------------------------------------------------------------------------- */
		audioManager.LoadSound("hallwayMusic", "Assets/Sounds/BGmusic_Corridor_NoTimer.mp3", 0.3f);
		audioManager.LoadSound("trainAmbience", "Assets/Sounds/Ambience_Train.mp3", 0.3f);
		audioManager.PlaySound("hallwayMusic", true);
		audioManager.PlaySound("trainAmbience", true);

		/*--------------------------------------------------------------📦CREATE GAMEOBJECT📦------------------------------------------------------------------------------------------------------- */

		GameObject* hallway = new RenderGameObject("Cabin", "Assets/Images/Environment_Corridor_Hallway.png");
		GameObject* hallwaylights = new RenderGameObject("CabinLights", "Assets/Images/Environment_Corridor_Light.png");
		Journal = new Book();
		// Inside the Hallway constructor

		char_data = CharacterData::GetInstance();
	

		//activate clue in journal
		/*JournalData::GetInstance()->ActivateClue(CABIN1, 0);
		JournalData::GetInstance()->ActivateClue(CABIN1, 1);*/

		/*-------------------------------------------------------------🎮CREATE PLAYER🎮------------------------------------------------------------------------------------------------------- */

		Player* player = new Player("waiter", "Assets/Images/MainCharacter_WithTray_Walk.png", 2, 8, Journal);

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
		Text* timerText = new Text("timerText", "", "Assets/Fonts/Jibril.ttf", true);

		

		/*-------------------------------------------------------------💬CREATE UI💬------------------------------------------------------------------------------------------------------- */
		UIElement* orderPaper = new UINormal("OrderPaper", "Assets/Images/OrderPaper.png",
			glm::vec3(-7.65f, 4.0f, 0.0f), glm::vec3(3.55f, 2.54f, 0.0f), true); // Start inactive
		orderData.SetOrderPaper(orderPaper);
		UIElement* timerUI = new UINormal("Timer", "Assets/Images/Timer.png", glm::vec3(7.3f, 5.1f, 0.0f), glm::vec3(4.37f, 3.13f, 0.0f), true);
		timer.Initialize(timerText,timerUI);
		UIElement* screenUI = new UINormal("ScreenUI", "Assets/Images/ScreenUI.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(16.0f * 1.19f, 9.0f * 1.19f, 0.0f), true);
		UIButton* journalButton = new UIButton("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-8.32f, -4.8f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), true, false, "");
		journalButton->SetOnClickAction([this]() { Journal->drawBook(); });
		//journalButton->SetHoverTexture("Assets/Images/Timer.png");


		Door* kitchenDoor = new Door("KitchenDoor", glm::vec3(18.35f, -0.55f, 0.0f), glm::vec3(2.8f, 5.7f, 0.0f), "Kitchen");
		DoorManager::GetInstance().AddDoor(kitchenDoor);

		Door* room1Door = new Door("Room1Door", glm::vec3(-18.35f, -0.55f, 0.0f), glm::vec3(2.8f, 5.7f, 0.0f), "Room1");
		DoorManager::GetInstance().AddDoor(room1Door);

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


		
		orderNoText->SetPosition(glm::vec3(-8.8f, 4.5f, 0.0f));
		orderNoText->SetColor(glm::vec3(0.5, 0, 0));

		teaOrderText->SetPosition(glm::vec3(-6.8f, 4.6f, 0.0f));
		teaOrderText->SetScale(0.6f);

		sandwichOrderText->SetPosition(glm::vec3(-7.8f, 4.0f, 0.0f));
		sandwichOrderText->SetScale(0.6f);

		pastryOrderText->SetPosition(glm::vec3(-7.8f, 3.3f, 0.0f));
		pastryOrderText->SetScale(0.6f);


		timerText->SetPosition(glm::vec3(6.65f, 4.12f, 0.0f));
		timerText->SetColor(glm::vec3(1, 1, 1));
		timerText->SetScale(1.4f);

		/*--------------------------------------------------------------✅PUSH BACK✅------------------------------------------------------------------------------------------------------- */
		//Environment
		m_gameObjects.push_back(hallway);
		m_gameObjects.push_back(player);
		m_gameObjects.push_back(hallwaylights);

		//UIs
		m_gameObjects.push_back(journalButton);
		m_gameObjects.push_back(timerUI);
		m_gameObjects.push_back(orderPaper);
		m_gameObjects.push_back(kitchenDoor);
		m_gameObjects.push_back(room1Door);
		
		
		//UITexts
		m_gameObjects.push_back(orderNoText);
		m_gameObjects.push_back(teaOrderText);
		m_gameObjects.push_back(sandwichOrderText);
		m_gameObjects.push_back(pastryOrderText);
		m_gameObjects.push_back(timerText);

		//Journal
		m_gameObjects.push_back(Journal);

	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); // Call the base class update

		Timer& timer = Timer::GetInstance();
	    timer.Update(dt);
		

		// Retrieve the player object by name
		GameObject* playerObject = GetGameObjectByName("waiter");
		if (playerObject) {
			// Cast to Player* if necessary, or directly use if GetPosition is part of GameObject
			Player* player = dynamic_cast<Player*>(playerObject);
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

			}
		}

	}

};





