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

		FlipRightButton = new UIButton("FlipRightButton", "Assets/Images/Journal/Tea_Guide_Arrow_Right.png", glm::vec3(5.0f, -2.9f, 0.0f), glm::vec3(1.0f, 0.3f, 0.0f), true, false, "");
		FlipRightButton->SetHoverTexture("Assets/Images/Journal/Tea_Guide_Arrow_Right_Highlight.png");
		FlipRightButton->SetOnClickAction([this]() { incrementPage(); });

		FlipLeftButton = new UIButton("FlipLeftButton", "Assets/Images/Journal/Tea_Guide_Arrow_Left.png", glm::vec3(5.0f, -2.9f, 0.0f), glm::vec3(1.0f, 0.3f, 0.0f), true, false, "");
		FlipLeftButton->SetHoverTexture("Assets/Images/Journal/Tea_Guide_Arrow_Left_Highlight.png");
		FlipLeftButton->SetOnClickAction([this]() {  incrementPage(); });

		page1 = new DeferredRenderObject();
		page1->gameObj = TeaGuidePage1;
		page1->showObject = true;

		page2 = new DeferredRenderObject();
		page2->gameObj = TeaGuidePage2;
		page2->showObject = false;

		page3 = new DeferredRenderObject();
		page3->gameObj = TeaGuidePage3;
		page3->showObject = false;

		rightButton = new DeferredRenderObject();
		rightButton->gameObj = FlipRightButton;
		rightButton->showObject = true;

		leftButton = new DeferredRenderObject();
		leftButton->gameObj = FlipLeftButton;
		leftButton->showObject = false;

		deffered_m_gameObjects.push_back(page1);
		deffered_m_gameObjects.push_back(page2);
		deffered_m_gameObjects.push_back(page3);

		deffered_m_gameObjects.push_back(rightButton);
		deffered_m_gameObjects.push_back(leftButton);

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

		if (activePageNo == 0 || activePageNo == 1) {
			rightButton->showObject = true;
			rightButton->gameObj->setActiveStatus(true);
			leftButton->showObject = false;
			leftButton->gameObj->setActiveStatus(false);
		}
		else {
			rightButton->showObject = false;
			rightButton->gameObj->setActiveStatus(false);
			leftButton->showObject = true;
			leftButton->gameObj->setActiveStatus(true);
		}
	}

private:

	GameObject* TeaGuidePage1;
	GameObject* TeaGuidePage2;
	GameObject* TeaGuidePage3;

	UIButton* FlipRightButton;
	UIButton* FlipLeftButton;

	DeferredRenderObject* page1;
	DeferredRenderObject* page2;
	DeferredRenderObject* page3;

	DeferredRenderObject* rightButton;
	DeferredRenderObject* leftButton;


	int activePageNo = 0;

};