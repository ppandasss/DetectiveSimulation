#pragma once

#include "Interface.h"

#include "../PopupWidget/InterfaceManager.h"

class OptionsInterface : public Interface {

public:

	OptionsInterface() {

		GameObject* OptionsBackground = new UIObject("OptionsBackground", "Assets/Images/Interface/Interface_Background_Options.png", true);
		OptionsBackground->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		OptionsBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		UIButton* CloseOptionsButton = new UIButton("CloseOptionsButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(5.25f, 4.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		CloseOptionsButton->SetOnClickAction([this]() { Interface_Manager.closeCurrentInterface(); });

		//UIButton* openSecondInterface = new UIButton("CloseOptionsButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		//openSecondInterface->SetOnClickAction([this]() { Interface_Manager.ActivateInterface(EXIT); });


		m_gameObjects.push_back(OptionsBackground);
		m_gameObjects.push_back(CloseOptionsButton);
		//m_gameObjects.push_back(openSecondInterface);

	}


private:

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};