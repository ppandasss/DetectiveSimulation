	#pragma once

	#include "../Scene.h"
	#include "../RenderGameObject.h"
	#include"../AnimateGameObject.h"	

	#include "../Player.h"
	#include "../TextRenderer.h"
	#include "../Text.h"

	class LevelScene : public Scene
	{

	private:
		TextRenderer textRenderer;
	public:
		LevelScene()
		{ 
			
			textRenderer.Initialize();
			//RenderGameObject* boss = new RenderGameObject("Boss", "Assets/Images/awesomeface.png");
			//GameObject* cabin = new RenderGameObject("Cabin", "Assets/Images/Cabin.png");
			Player* Bus = new Player("Bus", "Assets/Images/spritesheet_test.png",4.0f,4.0f);

			Text* helloText = new Text("HelloText", "Hello, World!", textRenderer);
			helloText->SetPosition(glm::vec3(5.0f, 5.0f, 0.0f));
		
		
		
			//boss->SetOrientation(1.7);
			//m_gameObjects.push_back(cabin);
			//m_gameObjects.push_back(boss);
			m_gameObjects.push_back(Bus);
			m_gameObjects.push_back(helloText);
		}
	};