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
			Player* Bus = new Player("waiter", "Assets/Images/waiter_spritesheet_test.png",2,8);
			
			//Text* helloText = new Text("GameTitle", "Ticking Tea Time", "Assets/Fonts/WD.ttf");

			
			cabin->SetScale(glm::vec3(45.0f, 10.5f, 0.0f));
			cabin->SetPosition(glm::vec3(0.0f, -0.2f, 0.0f));
			//helloText->SetPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
		
		
		
		
			m_gameObjects.push_back(cabin);
			m_gameObjects.push_back(Bus);
			//m_gameObjects.push_back(helloText);
		}

		void Update(float dt, long frame) {
			std::cout<<"LevelScene Update"<<std::endl;
			Scene::Update(dt, frame); // Call the base class update
			// Assuming 'Player' is the type of your player object
			for (auto& object : m_gameObjects) {
				Player* player = dynamic_cast<Player*>(object);
				if (player) {
					Camera& camera = Application::GetCamera();
					glm::vec3 playerPos = player->GetPosition();
					camera.SetPosition(playerPos.x, camera.GetPosY());
					break; // Assuming there is only one player
				}
			}
		}

	};