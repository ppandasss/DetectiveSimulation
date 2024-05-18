#pragma once

#include "Page.h"

enum FoodGuide {PAGE1, PAGE2, PAGE3};

class FoodGuidePage : public Page {

public:

	FoodGuidePage() :Page() {

		TeaGuidePage1 = new UIObject("TeaGuidePage1", "Assets/Images/Journal/TeaGuide_Page1.png", true);
		TeaGuidePage1->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		TeaGuidePage2 = new UIObject("TeaGuidePage2", "Assets/Images/Journal/TeaGuide_Page2.png", true);
		TeaGuidePage2->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		TeaGuidePage3 = new UIObject("TeaGuidePage3", "Assets/Images/Journal/TeaGuide_Page3.png", true);
		TeaGuidePage3->SetScale(glm::vec3(12.27f, 7.48f, 0.0f));
		TeaGuidePage3->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		UIButtonEmpty* flipPageButton = new UIButtonEmpty("FlipPageButton", glm::vec3(5.9f, -3.1f, 0.0f), glm::vec3(1.8f, 0.6f, 0.0f), true, false);
		flipPageButton->SetOnClickAction([this]() { incrementPage(); });

		m_gameObjects.push_back(flipPageButton);

		page1 = new DeferredRenderObject();
		page1->gameObj = TeaGuidePage1;
		page1->showObject = true;

		page2 = new DeferredRenderObject();
		page2->gameObj = TeaGuidePage2;
		page2->showObject = false;

		page3 = new DeferredRenderObject();
		page3->gameObj = TeaGuidePage3;
		page3->showObject = false;

		deffered_m_gameObjects.push_back(page1);
		deffered_m_gameObjects.push_back(page2);
		deffered_m_gameObjects.push_back(page3);

	}

	void incrementPage() {

		activePageNo = (activePageNo + 1) % 3;
		updateActivePage();
	}

	void updateActivePage() {

		for (int i = 0; i < 3; i++) {

			if (i == activePageNo) {
				deffered_m_gameObjects.at(i)->showObject = true;
			}
			else {
				deffered_m_gameObjects.at(i)->showObject = false;
			}

		}
	}

private:

	GameObject* TeaGuidePage1;
	GameObject* TeaGuidePage2;
	GameObject* TeaGuidePage3;

	DeferredRenderObject* page1;
	DeferredRenderObject* page2;
	DeferredRenderObject* page3;

	int activePageNo = 0;

};