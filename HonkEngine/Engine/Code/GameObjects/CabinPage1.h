#pragma once

#include "Page.h"

class CabinPage1 : public Page {

public:

	CabinPage1() :Page() {

		UIButton* Suspect1 = new UIButton("Suspect1", "Assets/Images/Journal_CaseSummary_Icon_Archibald.png", glm::vec3(1.2f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f), true);

		Text* Cabin1 = new Text("Cabin1", "Cabin 1", "Assets/Fonts/WD.ttf");
		Cabin1->SetPosition(glm::vec3(0.7f, 1.1f, 0.0f));
		Cabin1->SetColor(glm::vec3(0, 0, 0));
		Cabin1->SetScale(0.6f);

		m_gameObjects.push_back(Cabin1);
		m_gameObjects.push_back(Suspect1);


	}



};