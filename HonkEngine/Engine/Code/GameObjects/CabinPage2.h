#pragma once

#include "Page.h"

class CabinPage2 : public Page {

public:

	CabinPage2() :Page() {

		UIButton* Suspect5 = new UIButton("Suspect5", "Assets/Images/Journal_CaseSummary_Icon_Octavia.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f), true);

		Text* Cabin4 = new Text("Cabin4", "Cabin 4", "Assets/Fonts/WD.ttf");
		Cabin4->SetPosition(glm::vec3(2.3f, -1.2, 0.0f));
		Cabin4->SetColor(glm::vec3(0, 0, 0));
		Cabin4->SetScale(0.6f);

		m_gameObjects.push_back(Cabin4);
		m_gameObjects.push_back(Suspect5);




	}



};