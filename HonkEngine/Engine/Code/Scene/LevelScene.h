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
		LevelScene() : audioManager(Application::Get().GetAudioManager())
		{
			audioManager.LoadSound("backgroundMusic", "Assets/Sounds/ophelia.mp3");
			audioManager.PlaySound("backgroundMusic", true);
			audioManager.SetSoundVolume("backgroundMusic",0.3f);
			GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");
			Player* Bus = new Player("waiter", "Assets/Images/waiter_spritesheet_test.png",1,8);

			Text* helloText = new Text("GameTitle", "Ticking Tea Time", "Assets/Fonts/WD.ttf");

			
			cabin->SetScale(glm::vec3(10.0f, 5.0f, 0.0f));
			cabin->SetPosition(glm::vec3(0.0f, 0.7f, 0.0f));
			helloText->SetPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
		
		
		
		
			m_gameObjects.push_back(cabin);
			m_gameObjects.push_back(Bus);
			m_gameObjects.push_back(helloText);
		}
	};