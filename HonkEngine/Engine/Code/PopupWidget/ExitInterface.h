#pragma once

#include "Interface.h"

#include "../PopupWidget/InterfaceManager.h"

class ExitInterface : public Interface {

public:

	ExitInterface() {

		UIButton* GreyBackground = new UIButton("GreyBackground2", "Assets/Images/Interface/Grey_Background.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.2f, 10.8f, 0.0f), true, false, "");
		GreyBackground->SetOnClickAction([this]() { EmptyFunction(); });

		GameObject* ExitBackground = new UIObject("ExitBackground", "Assets/Images/Interface/Interface_Background_PopUp.png", true);
		ExitBackground->SetScale(glm::vec3(8.0f, 8.0f, 0.0f));
		ExitBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Text* QuestionText = new Text("QuestionText", "Are you sure you want to quit?", "Assets/Fonts/mvboli.ttf");
		QuestionText->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		QuestionText->SetColor(glm::vec3(0, 0, 0));
		QuestionText->SetScale(0.7f);

		UIButton* CancelButton = new UIButton("CloseExitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -0.7f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		CancelButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		CancelButton->SetButtonText("Cancel");
		CancelButton->SetOnClickAction([this]() { Interface_Manager.closeCurrentInterface(); });

		UIButton* ConfirmExitButton = new UIButton("ConfirmExitButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		ConfirmExitButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		ConfirmExitButton->SetButtonText("Yes");
		ConfirmExitButton->SetOnClickAction([this]() { Application::Get().exitGame(); });

		m_gameObjects.push_back(GreyBackground);
		m_gameObjects.push_back(ExitBackground);
		m_gameObjects.push_back(QuestionText);
		m_gameObjects.push_back(CancelButton);
		m_gameObjects.push_back(ConfirmExitButton);

	}

	void EmptyFunction() {
		return;
	}


private:

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};