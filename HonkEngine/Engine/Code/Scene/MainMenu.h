#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"

#include "../UI/UIButton.h"

#include "../PopupWidget/OptionsMenu.h"
#include "../PopupWidget/ExitMenu.h"
#include "../PopupWidget/PauseMenu.h"

#include "../Application.h"


class MainMenu : public Scene {

public:

	MainMenu() :audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("menuMusic", "Assets/Sounds/Music/BGmusic_Cabin2.mp3", Music, 0.6f);
		audioManager.LoadSound("buttonClick2", "Assets/Sounds/SFX_ButtonClick.mp3", SFX, 9.0f);

		GameObject* MainMenuBackground = new UIObject("MainMenuBackground", "Assets/Images/MainMenu/MainMenu_BG.jpg", true);
		MainMenuBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		MainMenuBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		PlayButton = new UIButton("PlayButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.9f, -0.1f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		PlayButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		PlayButton->SetButtonText("Start");
		PlayButton->SetTextSize(0.65);
		PlayButton->SetTextPosition(glm::vec3(-6.9f, -0.2f, 0.0f));
		PlayButton->SetOnClickAction([this]() { clickPlay(); });

		OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Setting.png", glm::vec3(-6.9f, -1.3f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Setting_Hover.png");
		OptionsButton->SetButtonText("Options");
		OptionsButton->SetTextSize(0.65);
		OptionsButton->SetTextPosition(glm::vec3(-6.9f, -1.42f, 0.0f));
		OptionsButton->SetOnClickAction([this]() { clickOptions(); });

		QuitButton = new UIButton("QuitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.9f, -2.5f, 0.0f), glm::vec3(3.78f, 1.06f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		QuitButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Exit_Hover.png");
		QuitButton->SetButtonText("Quit");
		QuitButton->SetTextSize(0.65);
		QuitButton->SetTextPosition(glm::vec3(-6.9f, -2.63f, 0.0f));
		QuitButton->SetOnClickAction([this]() { clickExit(); });
		
		clickToBegin = new Text("clickToBegin", "Click anywhere to begin", "Assets/Fonts/mvboli.ttf");
		clickToBegin->SetPosition(glm::vec3(-8.42f, -3.6f, 0.0f));
		clickToBegin->SetColor(glm::vec3(1, 1, 1));
		clickToBegin->SetScale(0.7f);

		transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
		transitionEffects = std::make_unique<TransitionEffects>(transitionObject);

		m_gameObjects.push_back(MainMenuBackground);
		m_gameObjects.push_back(PlayButton);
		m_gameObjects.push_back(OptionsButton);
		m_gameObjects.push_back(QuitButton);
		m_gameObjects.push_back(clickToBegin);

		//INTERFACES IN MAIN MENU

		m_gameObjects.push_back(transitionObject);

		m_gameObjects.push_back(&optionsMenu);
		m_gameObjects.push_back(&exitMenu);

		setMainMenuState();

	}

	void Update(float dt, long frame)
	{
		Scene::Update(dt, frame);

		transitionEffects->Update(dt);

		Input& input = Application::GetInput();

		if (startOfGame) {
			
			if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0))
			{
				startOfGame = false;
				setMainMenuState();
				AudioManager::GetInstance().PlaySound("buttonClick2");
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
		transitioning = true;
		transitionEffects->FadeIn(3.0f, [this]() {
			std::cout << "Fade in complete" << std::endl;
			transitioning = false;
			});
	}

    void OnExit() override {
		audioManager.StopSound("menuMusic");

	}

private:

	AudioManager& audioManager;

	//BUTTON FUNCTIONS

	void clickPlay() {
		if (!transitioning) {
			transitioning = true;
			//transitioning = true;
			AudioManager::GetInstance().PlaySound("buttonClick2");
			transitionEffects->FadeOut(2.0f, [this]() {
				Application::Get().SetScene("OpenScene");
				});
		}
	}

	void clickOptions() { 
		AudioManager::GetInstance().PlaySound("buttonClick2");
;		optionsMenu.Show();
		//ACTIVATE OPTIONS MENU
	}

	void clickExit() { 
		AudioManager::GetInstance().PlaySound("buttonClick2");

		exitMenu.Show();

		/*transitionEffects->FadeOut(3.0f, [this]() {
			Application::Get().exitGame();
		});*/

		//ACTIVATE EXIT MENU
	
	}


	bool startOfGame = true;
	bool transitioning = false;

	UIButton* PlayButton;
	UIButton* OptionsButton; 
	UIButton* QuitButton;

	Text* clickToBegin;

	UIElement* transitionObject;
	std::unique_ptr<TransitionEffects> transitionEffects;

	OptionsMenu optionsMenu;
	ExitMenu exitMenu;

};


