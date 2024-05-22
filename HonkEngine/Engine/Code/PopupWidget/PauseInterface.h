#pragma once

#include "Interface.h"

#include "../PopupWidget/InterfaceManager.h"

class PauseInterface : public Interface {

public:

	PauseInterface() {

		UIButton* GreyBackground = new UIButton("GreyBackground2", "Assets/Images/Interface/Grey_Background.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.2f, 10.8f, 0.0f), true, false, "");
		GreyBackground->SetOnClickAction([this]() { EmptyFunction(); });

		GameObject* PauseBackground = new UIObject("ExitBackground", "Assets/Images/Interface/Interface_Background_PopUp.png", true);
		PauseBackground->SetScale(glm::vec3(8.0f, 8.0f, 0.0f));
		PauseBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* ContinueButton = new UIButton("ContinueButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		ContinueButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		ContinueButton->SetButtonText("Continue Game");
		ContinueButton->SetOnClickAction([this]() { ContinueGame(); });

		UIButton* OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		OptionsButton->SetButtonText("Options");
		OptionsButton->SetOnClickAction([this]() { Interface_Manager.ActivateInterface(OPTIONSTWO); });

		UIButton* MainMenuButton = new UIButton("MainMenuButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		MainMenuButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		MainMenuButton->SetButtonText("Main Menu");
		MainMenuButton->SetOnClickAction([this]() { Application::Get().SetScene("MainMenu"); });


		m_gameObjects.push_back(GreyBackground);
		m_gameObjects.push_back(PauseBackground);
		m_gameObjects.push_back(ContinueButton);
		m_gameObjects.push_back(OptionsButton);
		m_gameObjects.push_back(MainMenuButton);

	}

	void EmptyFunction() {
		return;
	}

	void ContinueGame() {

		Interface_Manager.closeCurrentInterface();

		//continue timer
		//unlock player movement
		//pause bell ringing

	}


private:

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};