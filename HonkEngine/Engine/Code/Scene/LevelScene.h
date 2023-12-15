	#pragma once

	#include "Scene.h"
	#include "../GameObjects/RenderGameObject.h"
	#include"../GameObjects/AnimateGameObject.h"	

	#include "../GameObjects/Player.h"
	#include "../Text/TextRenderer.h"
	#include "../Text/Text.h"
	#include"../Audio/AudioManager.h"	

	class LevelScene : public Scene
	{

	private:
		std::unique_ptr<TextRenderer> textRenderer;
		AudioManager& audioManager;
	public:
		LevelScene() :audioManager(AudioManager::GetInstance())
		{
			audioManager.LoadSound("backgroundMusic", "Assets/Sounds/MembersOnly.mp3",0.2f);
			audioManager.LoadSound("trainAmbience", "Assets/Sounds/Train_Ambience.mp3", 0.2f);
			audioManager.PlaySound("backgroundMusic", true);
			audioManager.PlaySound("trainAmbience", true);
			
			GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Environment_Corridor_Hallway.png");
			Player* player = new Player("waiter", "Assets/Images/waiter_spritesheet_test.png",2,8);
			
			//Text* helloText = new Text("GameTitle", "Ticking Tea Time", "Assets/Fonts/WD.ttf");

			
			cabin->SetScale(glm::vec3(45.0f, 10.5f, 0.0f));
			cabin->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));
			//helloText->SetPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
		
		
		
		
			m_gameObjects.push_back(cabin);
			m_gameObjects.push_back(player);
			//m_gameObjects.push_back(helloText);
		}

		void Update(float dt, long frame) {
			Scene::Update(dt, frame); // Call the base class update

			// Retrieve the player object by name
			GameObject* playerObject = GetGameObjectByName("waiter");
			if (playerObject) {
				// Cast to Player* if necessary, or directly use if GetPosition is part of GameObject
				Player* player = dynamic_cast<Player*>(playerObject);
				if (player) {

					std::cout << "Found player object" << std::endl;
					// Get the player's position
					glm::vec3 playerPos = player->GetPosition();
					std::cout << player->GetPosition().x << std::endl;
					// Get the camera and update its position
					Camera& camera = Application::GetCamera();

					const float leftBound = -12.74f;
					const float rightBound = 12.91f;
					
					// Clamp the camera's x position within the bounds
					float clampedX = std::max(leftBound, std::min(playerPos.x, rightBound));
					camera.SetPosition(clampedX, camera.GetPosY());
					
				}
			}
		}

	};