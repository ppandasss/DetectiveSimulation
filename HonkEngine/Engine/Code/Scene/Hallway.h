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
	#include "../UI/UIElement.h"
	#include "../GameObjects/Book.h"

	class Hallway : public Scene
	{

	private:
		std::unique_ptr<TextRenderer> textRenderer;
		AudioManager& audioManager;

		Book* Journal;


	public:
		Hallway() :audioManager(AudioManager::GetInstance())
		{
			audioManager.LoadSound("backgroundMusic", "Assets/Sounds/MembersOnly.mp3",0.2f);
			audioManager.LoadSound("trainAmbience", "Assets/Sounds/Train_Ambience.mp3", 0.2f);
			audioManager.PlaySound("backgroundMusic", true);
			audioManager.PlaySound("trainAmbience", true);
			
			GameObject* hallway = new RenderGameObject("Cabin", "Assets/Images/Environment_Corridor_Hallway.png");
			GameObject* hallwaylights = new RenderGameObject("CabinLights", "Assets/Images/Environment_Corridor_Light.png");

			Player* player = new Player("waiter", "Assets/Images/waiter_spritesheet_test.png",2,8);
			
			Text* helloText = new Text("GameTitle", " Welcome To Ticking Tea Time", "Assets/Fonts/WD.ttf");

			UIButton* journalButton = new UIButton("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-6.5f, -4.5f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), true);
			
			

			UIElement* ticket = new UIDraggable("ticket", "Assets/Images/Journal_CaseSummary_Ticket_WithText.png", glm::vec3(6.0f, -4.0f, 0.0f), glm::vec3(2.0f, 1.0f, 0.0f), true, glm::vec3(6.0f, -4.0f, 0.0f));
			
			hallway->SetScale(glm::vec3(45.0f, 10.5f, 0.0f));
			hallway->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));
			hallwaylights->SetScale(glm::vec3(45.0f, 10.5f, 0.0f));
			hallwaylights->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));
			helloText->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			helloText->SetColor(glm::vec3(1,1,1));
			
			//Journal = new Book();

			m_gameObjects.push_back(hallway);
			m_gameObjects.push_back(player);
			m_gameObjects.push_back(hallwaylights);

			m_gameObjects.push_back(helloText);

			m_gameObjects.push_back(journalButton);
			m_gameObjects.push_back(ticket);

			//m_gameObjects.push_back(Journal);

		}

		void Update(float dt, long frame) {
			Scene::Update(dt, frame); // Call the base class update

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
					std::cout<<camera.GetZoom() << std::endl;
					
					// Clamp the camera's x position within the bounds
					float clampedX = std::max(leftBound, std::min(playerPos.x, rightBound));
					camera.SetPosition(clampedX, camera.GetPosY());
					
				}
			}
		}

		void OpenJournal() {

			m_gameObjects.push_back(Journal);

		}

	};