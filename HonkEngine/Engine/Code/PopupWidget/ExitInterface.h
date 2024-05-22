#pragma once

#include "Interface.h"

#include "../PopupWidget/InterfaceManager.h"

class ExitInterface : public Interface {

public:

	ExitInterface() {

		GameObject* ExitBackground = new UIObject("ExitBackground", "Assets/Images/Interface/Interface_Background_PopUp.png", true);
		ExitBackground->SetScale(glm::vec3(8.0f, 8.0f, 0.0f));
		ExitBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Text* QuestionText = new Text("QuestionText", "Are you sure you want to quit?", "Assets/Fonts/mvboli.ttf");
		QuestionText->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		QuestionText->SetColor(glm::vec3(0, 0, 0));
		QuestionText->SetScale(0.7f);

		UIButton* CancelButton = new UIButton("CloseExitButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(5.25f, 4.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		CancelButton->SetOnClickAction([this]() { Interface_Manager.closeCurrentInterface(); });

		UIButton* ConfirmExitButton = new UIButton("ConfirmExitButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(5.25f, 4.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		ConfirmExitButton->SetOnClickAction([this]() { Application::Get().exitGame(); });

		m_gameObjects.push_back(ExitBackground);
		m_gameObjects.push_back(QuestionText);
		m_gameObjects.push_back(CancelButton);

	}


private:

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};