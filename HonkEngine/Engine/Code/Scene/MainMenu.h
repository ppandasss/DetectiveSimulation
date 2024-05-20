#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"

#include "../UI/UIButton.h"

#include "../Application.h"


class MainMenu : public Scene {

public:

	MainMenu() {

		GameObject* MainMenuBackground = new UIObject("MainMenuBackground", "Assets/Images/MainMenu/MainMenu_BG.jpg", true);
		MainMenuBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		MainMenuBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		PlayButton = new UIButton("PlayButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.0f, -0.5f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		PlayButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		PlayButton->SetButtonText("Start Game");
		PlayButton->SetOnClickAction([this]() { clickPlay(); });
		
		OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Setting.png", glm::vec3(-6.0f, -1.7f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Setting_Hover.png");
		OptionsButton->SetButtonText("Options");

		QuitButton = new UIButton("QuitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.0f, -2.9f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		QuitButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Exit_Hover.png");
		QuitButton->SetButtonText("Quit");
		QuitButton->SetOnClickAction([this]() { clickExit(); });

		clickToBegin = new Text("clickToBegin", "Click to begin", "Assets/Fonts/mvboli.ttf");
		clickToBegin->SetPosition(glm::vec3(-8.0f, -2.9f, 0.0f));
		clickToBegin->SetColor(glm::vec3(1, 1, 1));
		clickToBegin->SetScale(0.7f);

		m_gameObjects.push_back(MainMenuBackground);
		m_gameObjects.push_back(PlayButton);
		m_gameObjects.push_back(OptionsButton);
		m_gameObjects.push_back(QuitButton);
		m_gameObjects.push_back(clickToBegin);

		setMainMenuState();

	}

	void Update(float dt, long frame)
	{
		Scene::Update(dt, frame);

		Input& input = Application::GetInput();

		if (startOfGame) {
			
			if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
			{
				startOfGame = false;
				setMainMenuState();
			}
		}		

	}

	void setMainMenuState() {

		if (startOfGame) {

			PlayButton->setActiveStatus(false);
			QuitButton->setActiveStatus(false);
			OptionsButton->setActiveStatus(false); 
			clickToBegin->setActiveStatus(true);

		}
		else {
			PlayButton->setActiveStatus(true);
			QuitButton->setActiveStatus(true);
			OptionsButton->setActiveStatus(true);
			clickToBegin->setActiveStatus(false);
		}

	}

private:

	//BUTTON FUNCTIONS

	void clickPlay() {
		Application::Get().SetScene("Hallway");
	}

	void clickOptions() {

	}

	void clickExit() {
		Application::Get().exitGame();
	}


	bool startOfGame = true;

	UIButton* PlayButton;
	UIButton* OptionsButton; 
	UIButton* QuitButton;

	Text* clickToBegin;


};


