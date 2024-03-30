#pragma once

#include "Page.h"

class FoodGuidePage : public Page {

public:

	FoodGuidePage() :Page() {

		GameObject* TeaGuidePage1 = new UIObject("TeaGuidePage1", "Assets/Images/Journal/TeaGuide_Page1_Mockup.png", true);
		TeaGuidePage1->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage1->SetPosition(glm::vec3(-0.0f, 0.0f, 0.0f));

		GameObject* TeaGuidePage2 = new UIObject("TeaGuidePage2", "Assets/Images/Journal/TeaGuide_Page2_Mockup.png", true);
		TeaGuidePage2->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage2->SetPosition(glm::vec3(-0.0f, 0.0f, 0.0f));

		//m_gameObjects.push_back(TeaGuidePage1);
		m_gameObjects.push_back(TeaGuidePage2);

	}



};