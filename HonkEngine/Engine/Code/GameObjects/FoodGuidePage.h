#pragma once

#include "Page.h"

enum FoodGuide {PAGE1, PAGE2};

class FoodGuidePage : public Page {

public:

	FoodGuidePage() :Page() {

		TeaGuidePage1 = new UIObject("TeaGuidePage1", "Assets/Images/Journal/TeaGuide_Page1_Mockup.png", true);
		TeaGuidePage1->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		TeaGuidePage2 = new UIObject("TeaGuidePage2", "Assets/Images/Journal/TeaGuide_Page2.png", true);
		TeaGuidePage2->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		UIButtonEmpty* flipPageButton = new UIButtonEmpty("FlipPageButton", glm::vec3(5.6f, -2.8f, 0.0f), glm::vec3(1.4f, 0.5f, 0.0f), true, false);
		flipPageButton->SetOnClickAction([this]() { flipFoodPage(); });

		m_gameObjects.push_back(TeaGuidePage1);
		m_gameObjects.push_back(TeaGuidePage2);
		m_gameObjects.push_back(flipPageButton);


	}

	virtual void Update(float dt, long frame) override {

		Page::Update(dt, frame);

		if (activePage == PAGE1) {

			TeaGuidePage1->setActiveStatus(true);
			TeaGuidePage2->setActiveStatus(false);

		}
		else if (activePage == PAGE2) {

			TeaGuidePage2->setActiveStatus(true);
			TeaGuidePage1->setActiveStatus(false);

		}


	}

	void flipFoodPage() {

		
		if (activePage == PAGE1) {
			activePage = PAGE2;
		}
		else {
			activePage = PAGE1;
		}


	}

private:

	GameObject* TeaGuidePage1;
	GameObject* TeaGuidePage2;

	FoodGuide activePage = PAGE1;

};