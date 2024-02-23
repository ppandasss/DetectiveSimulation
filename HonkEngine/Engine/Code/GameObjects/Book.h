#pragma once

#include "GameObject.h"
#include "RenderGameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "../Input/Input.h"
#include "JournalData.h"
#include <iostream>
#include "Application.h"
#include"../Scene/Scene.h"
#include "../Text/Text.h"

#include "MainPage.h"
#include "CabinPage1.h"
#include "CabinPage2.h"
#include "CabinPage3.h"
#include "CabinPage4.h"
#include "CabinPage5.h"
#include "FoodGuidePage.h"


enum currentPage {MAIN, CABIN1, CABIN2, CABIN3, CABIN4, CABIN5, GUIDE1, GUIDE2};

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

class Book: public GameObject{

public:

	GameObject* JournalCover;
	
	Book() : GameObject("Book") {

		JournalCover = new RenderGameObject("JournalCover", "Assets/Images/Journal/Cover.png");
		JournalCover->SetScale(glm::vec3(14.0f, 10.0f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal/Bookmark_CaseSummary.png", glm::vec3(6.8f, 3.8f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal/Bookmark_P1.png", glm::vec3(6.8f, 2.6f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal/Bookmark_P2.png", glm::vec3(6.8f, 1.4f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal/Bookmark_P2_2.png", glm::vec3(6.8f, 0.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal/Bookmark_P3.png", glm::vec3(6.8f, -1.0f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal/Bookmark_P4.png", glm::vec3(6.8f, -2.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		//ADD FOOD GUIDE

		Tab1->SetOnClickAction([this]() { setActiveTab1(); });
		Tab2->SetOnClickAction([this]() { setActiveTab2(); });
		Tab3->SetOnClickAction([this]() { setActiveTab3(); });
		Tab4->SetOnClickAction([this]() { setActiveTab4(); });
		Tab5->SetOnClickAction([this]() { setActiveTab5(); });
		Tab6->SetOnClickAction([this]() { setActiveTab6(); });

		GameObject* BlankPage = new RenderGameObject("BlankPage", "Assets/Images/Journal/BlankPage.png");
		BlankPage->SetScale(glm::vec3(13.0f, 9.0f, 1.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* JournalSleeve = new RenderGameObject("JounalSleeve", "Assets/Images/Journal/CaseSummary_Sleeve.png");
		JournalSleeve->SetScale(glm::vec3(3.5f, 9.7f, 0.0f));
		JournalSleeve->SetPosition(glm::vec3(-5.3f, 0.0f, 0.0f));

		m_gameObjects.push_back(JournalCover);
		m_gameObjects.push_back(Tab1);
		m_gameObjects.push_back(Tab2);
		m_gameObjects.push_back(Tab3);
		m_gameObjects.push_back(Tab4);
		m_gameObjects.push_back(Tab5);
		m_gameObjects.push_back(Tab6);
		m_gameObjects.push_back(JournalSleeve);
		m_gameObjects.push_back(BlankPage);

		Page* mainPage = new MainPage();
		Page* cabinPage1 = new CabinPage1();
		Page* cabinPage2 = new CabinPage2();
		Page* cabinPage3 = new CabinPage3();
		Page* cabinPage4 = new CabinPage4();
		Page* cabinPage5 = new CabinPage5();
		Page* foodGuide = new FoodGuidePage();
		
		allPages.push_back(mainPage);
		allPages.push_back(cabinPage1);
		allPages.push_back(cabinPage2);
		allPages.push_back(cabinPage3);
		allPages.push_back(cabinPage4);
		allPages.push_back(cabinPage5);
		allPages.push_back(foodGuide);


	}

	//----------------------------------- OPEN & CLOSE ------------------------------------

	void drawBook(){

		for (auto& object : m_gameObjects) {

			if (!object->getActiveStatus()) { //IF NOT ACTIVE SET AS ACTIVE

				object->setActiveStatus(true);

			}

		}

		for (auto& object : allPages) {

			object->setActiveStatus(true);


		}

		openStatus = true;

	}

	void closeBook() {

		activePage = MAIN;

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //IF ACTIVE SET AS INACTIVE

				object->setActiveStatus(false);

			}

		}

		for (auto& object : allPages) {

			object->setActiveStatus(false);


		}

		openStatus = false;

		//make all gameobjects in book inactive

	}

	bool clickOutOfJournal(glm::vec2 mousePos){

		glm::vec2 newPos = UIElement::MousetoScreen(mousePos.x, mousePos.y);

		glm::vec3 journalPos = JournalCover->GetPosition();
		glm::vec3 journalScale = JournalCover->GetScale();

		float minX = journalPos.x - (journalScale.x / 2.0f);
		float maxX = journalPos.x + (journalScale.x / 2.0f);
		float minY = journalPos.y - (journalScale.y / 2.0f);
		float maxY = journalPos.y + (journalScale.y / 2.0f);

		//returns true if click inside of book
		return ((newPos.x >= minX && newPos.x <= maxX) && (newPos.y >= minY && newPos.y <= maxY));

	}



	//--------------------------------UPDATE & RENDER-----------------------------------------------------

	virtual void Render() override
	{

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		allPages[activePage]->Render();

	}

	virtual void Update(float dt, long frame) override {

		Input& input = Application::GetInput();

		for (auto& object : m_gameObjects) {
			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS
				object->Update(dt, frame);
			}
		}

		allPages[activePage]->Update(dt, frame);

		//BUTTON CLICKS OUTSIDE OF JOURNAL -> CLOSE BOOK

		mousePos = Application::Get().CursorPos();

		if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
			if (!clickOutOfJournal(mousePos)) { 
				if (openStatus == true) {
					closeBook();
				}
			}
		}

	
	}

	//-----------------------BOOK UI BUTTON FUNCTIONS-----------------------------------

	void setActiveTab1() { if (activePage != MAIN) { activePage = MAIN; } };
	void setActiveTab2() { if (activePage != CABIN1) { activePage = CABIN1; } };
	void setActiveTab3() { if (activePage != CABIN2) { activePage = CABIN2; } };
	void setActiveTab4() { if (activePage != CABIN3) { activePage = CABIN3; } };
	void setActiveTab5() { if (activePage != CABIN4) { activePage = CABIN4; } };
	void setActiveTab6() { if (activePage != CABIN5) { activePage = CABIN5; } };



protected:

	std::vector<GameObject*> m_gameObjects;
	std::vector<Page*> allPages;

	currentPage activePage = MAIN;

	bool openStatus = true; //true - open, false - closed

	glm::vec2 mousePos;

};