#pragma once

#include "Interface.h"

#include "../PopupWidget/InterfaceManager.h"

class OptionsTwoInterface : public Interface {

public:

	OptionsTwoInterface() {

		UIButton* GreyBackground = new UIButton("GreyBackground", "Assets/Images/Interface/Grey_Background.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.2f, 10.8f, 0.0f), true, false, "");
		GreyBackground->SetOnClickAction([this]() { EmptyFunction(); });

		GameObject* OptionsBackground = new UIObject("OptionsBackground", "Assets/Images/Interface/Interface_Background_Options.png", true);
		OptionsBackground->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		OptionsBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		UIButton* CloseOptionsButton = new UIButton("CloseOptionsButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(5.25f, 4.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		CloseOptionsButton->SetOnClickAction([this]() { Interface_Manager.closeCurrentInterface(); });

		m_gameObjects.push_back(GreyBackground);
		m_gameObjects.push_back(OptionsBackground);
		m_gameObjects.push_back(CloseOptionsButton);

	}

	void EmptyFunction() {
		return;
	}


private:

	InterfaceManager& Interface_Manager = InterfaceManager::getInstance();


};