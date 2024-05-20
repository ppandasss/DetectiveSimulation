#pragma once

#include "Interface.h"

class OptionsInterface : public Interface {

	OptionsInterface() {

		GameObject* OptionsBackground = new UIObject("OptionsBackground", "Assets/Images/Interface/Interface_Background_Options.png", true);
		OptionsBackground->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		OptionsBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));



		m_gameObjects.push_back(OptionsBackground);

	}

private:

	

};