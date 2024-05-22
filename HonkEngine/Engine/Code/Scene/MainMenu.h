#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"

#include "../UI/UIButton.h"
#include "../PopupWidget/InterfaceManager.h"
#include "../PopupWidget/OptionsInterface.h"
#include "../PopupWidget/ExitInterface.h"


#include "../Application.h"


class MainMenu : public Scene {

public:

	MainMenu() :audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("menuMusic", "Assets/Sounds/Music/BGmusic_Cabin2.mp3",Music, 0.6f);

		GameObject* MainMenuBackground = new UIObject("MainMenuBackground", "Assets/Images/MainMenu/MainMenu_BG.jpg", true);
		MainMenuBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		MainMenuBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		PlayButton = new UIButton("PlayButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.9f, -0.1f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		PlayButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		PlayButton->SetButtonText("Start");
		PlayButton->SetTextSize(0.7);
		PlayButton->SetTextPosition(glm::vec3(-6.9f, -0.2f, 0.0f));
		PlayButton->SetOnClickAction([this]() { clickPlay(); });

		 OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Setting.png", glm::vec3(-6.9f, -1.3f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Setting_Hover.png");
		OptionsButton->SetButtonText("Options");
		OptionsButton->SetTextSize(0.7);
		OptionsButton->SetTextPosition(glm::vec3(-6.9f, -1.42f, 0.0f));

		QuitButton = new UIButton("QuitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.9f, -2.5f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		QuitButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Exit_Hover.png");
		QuitButton->SetButtonText("Quit");
		QuitButton->SetTextSize(0.7);
		QuitButton->SetTextPosition(glm::vec3(-6.9f, -2.63f, 0.0f));
		QuitButton->SetOnClickAction([this]() { clickExit(); });
		
		clickToBegin = new Text("clickToBegin", "Click anywhere to begin", "Assets/Fonts/mvboli.ttf");
		clickToBegin->SetPosition(glm::vec3(-8.42f, -3.6f, 0.0f));
		clickToBegin->SetColor(glm::vec3(1, 1, 1));
		clickToBegin->SetScale(0.7f);

		m_gameObjects.push_back(MainMenuBackground);
		m_gameObjects.push_back(PlayButton);
		m_gameObjects.push_back(OptionsButton);
		m_gameObjects.push_back(QuitButton);
		m_gameObjects.push_back(clickToBegin);

		//INTERFACES IN MAIN MENU

		OptionsInterface* optionsInterface = new OptionsInterface();
		Interface_Manager.AddInterface(OPTIONS, optionsInterface);

		ExitInterface* exitInterface = new ExitInterface();
		Interface_Manager.AddInterface(EXIT, exitInterface);
		
		m_gameObjects.push_back(optionsInterface);
		m_gameObjects.push_back(exitInterface);

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

	void OnEnter() override {
		audioManager.PlaySound("menuMusic", true);
	}

    void OnExit() override {
		audioManager.StopSound("menuMusic");
	}

private:

	AudioManager& audioManager;

	//BUTTON FUNCTIONS

	void clickPlay() { Application::Get().SetScene("Hallway"); }

	void clickOptions() { 
		//Interface_Manager.ActivateInterface(OPTIONS);	
	}

	void clickExit() { 

		//Interface_Manager.ActivateInterface(EXIT); 

		Application::Get().exitGame();
	
	}


	bool startOfGame = true;

	UIButton* PlayButton;
	UIButton* OptionsButton; 
	UIButton* QuitButton;

	Text* clickToBegin;

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};


