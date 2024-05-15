#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../UI/UIButton.h"

class MainMenu : public Scene {

public:

	MainMenu() {

		GameObject* MainMenuBackground = new UIObject("MainMenuBackground", "Assets/Images/MainMenu/MainMenu_BG.jpg", true);
		MainMenuBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		MainMenuBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* PlayButton = new UIButton("PlayButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.0f, -0.5f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		PlayButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		PlayButton->SetButtonText("Start Game");

		UIButton* OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Setting.png", glm::vec3(-6.0f, -1.7f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Setting_Hover.png");
		OptionsButton->SetButtonText("Options");

		UIButton* QuitButton = new UIButton("QuitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-6.0f, -2.9f, 0.0f), glm::vec3(4.5f, 1.2f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		QuitButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Exit_Hover.png");
		QuitButton->SetButtonText("Quit");
		

		m_gameObjects.push_back(MainMenuBackground);
		m_gameObjects.push_back(PlayButton);
		m_gameObjects.push_back(OptionsButton);
		m_gameObjects.push_back(QuitButton);


	}

private:



};