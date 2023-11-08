	#pragma once

	#include "Scene.h"
	#include "../GameObjects/RenderGameObject.h"
	#include"../GameObjects/AnimateGameObject.h"	

	#include "../GameObjects/Player.h"
	#include "../Text/TextRenderer.h"
	#include "../Text/Text.h"

	class LevelScene : public Scene
	{

	private:
		std::unique_ptr<TextRenderer> textRenderer;
	public:
		LevelScene()
		{ 
			
			//textRenderer = std::make_unique<TextRenderer>();
			//textRenderer->Initialize("Assets/Fonts/WD.ttf");  // Initialize with the path to your font
			//RenderGameObject* boss = new RenderGameObject("Boss", "Assets/Images/waiter_spritesheet_test.png");
			GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");
			Player* Bus = new Player("waiter", "Assets/Images/waiter_spritesheet_test.png",1,8);

			Text* helloText = new Text("GameTitle", "Ticking Tea Time", "Assets/Fonts/WD.ttf");

			
			cabin->SetScale(glm::vec3(10.0f, 5.0f, 0.0f));
			cabin->SetPosition(glm::vec3(0.0f, 0.7f, 0.0f));
			//helloText->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));
			helloText->SetPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
		
		
		
			//boss->SetOrientation(1.7);
			m_gameObjects.push_back(cabin);
			//m_gameObjects.push_back(boss);
			m_gameObjects.push_back(Bus);
			m_gameObjects.push_back(helloText);
		}
	};