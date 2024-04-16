#pragma once

#include "GameObject.h"
#include "RenderGameObject.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include "../Input/Input.h"
#include "JournalData.h"
#include <iostream>
#include "../Application.h"
#include"../Scene/Scene.h"
#include "../Text/Text.h"

#include "MainPage.h"
#include "CabinPage1.h"
#include "CabinPage2.h"
#include "CabinPage3.h"
#include "CabinPage4.h"
#include "CabinPage5.h"
#include "FoodGuidePage.h"


enum currentPage { MAIN, CABIN1, CABIN2, CABIN3, CABIN4, CABIN5, FOODGUIDE };

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

class Book : public GameObject {

public:
	AudioManager& audioManager;

public:

	GameObject* JournalCover;

	//UIObject* JournalCoverUI;

	Book() : GameObject("Book"), audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("openJournal", "Assets/Sounds/SFX_OpenJournal.mp3", 0.55f);
		audioManager.LoadSound("pageSwitch", "Assets/Sounds/SFX_PageSwitch.mp3", 0.5f);

		JournalCover = new UIObject("JournalCover", "Assets/Images/Journal/Cover.png", true);
		JournalCover->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal/Bookmark_CaseSummary.png", glm::vec3(6.57f, 2.87f, 0.0f), glm::vec3(2.25f, 0.96f, 0.0f), true, false, "");
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal/Bookmark_P1.png", glm::vec3(6.57f, 1.85f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal/Bookmark_P2.png", glm::vec3(6.55f, 0.92f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal/Bookmark_P2_2.png", glm::vec3(6.61f, 0.0f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal/Bookmark_P3.png", glm::vec3(6.55f, -0.93f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal/Bookmark_P4.png", glm::vec3(6.55f, -1.85f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		UIButton* Tab7 = new UIButton("Tab6", "Assets/Images/Journal/Bookmark_TeaGuide.png", glm::vec3(6.49f, -2.8f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");

		Tab1->SetOnClickAction([this]() { setActiveTab1(); });
		Tab2->SetOnClickAction([this]() { setActiveTab2(); });
		Tab3->SetOnClickAction([this]() { setActiveTab3(); });
		Tab4->SetOnClickAction([this]() { setActiveTab4(); });
		Tab5->SetOnClickAction([this]() { setActiveTab5(); });
		Tab6->SetOnClickAction([this]() { setActiveTab6(); });
		Tab7->SetOnClickAction([this]() { setActiveTab7(); });

		GameObject* BackGround = new UIObject("JournalBG", "Assets/Images/Journal/BlackAlpha.png", true);
		BackGround->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		BackGround->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* BlankPage = new UIObject("BlankPage", "Assets/Images/Journal/BlankPage.png", true);
		BlankPage->SetScale(glm::vec3(12.68f, 7.45f, 1.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		m_gameObjects.push_back(BackGround);
		m_gameObjects.push_back(JournalCover);
		m_gameObjects.push_back(Tab1);
		m_gameObjects.push_back(Tab2);
		m_gameObjects.push_back(Tab3);
		m_gameObjects.push_back(Tab4);
		m_gameObjects.push_back(Tab5);
		m_gameObjects.push_back(Tab6);
		m_gameObjects.push_back(Tab7);
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

	void drawBook() {

		audioManager.PlaySound("openJournal", false);

		openStatus = true;

		for (auto& object : m_gameObjects) {

			if (!object->getActiveStatus()) { //IF NOT ACTIVE SET AS ACTIVE

				object->setActiveStatus(true);

			}

		}

		for (auto& object : allPages) {

			object->setActiveStatus(true);

		}

		//std::cout << "OPEN BOOKK" << std::endl;
	}

	void closeBook() {

		//make all gameobjects in book inactive

		audioManager.PlaySound("openJournal", false);

		openStatus = false;
		activePage = currentPage::MAIN;

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //IF ACTIVE SET AS INACTIVE

				object->setActiveStatus(false);

			}

		}


		for (auto& object : allPages)
		{
			object->setActiveStatus(false);
		}

		//std::cout << "CLOSE BOOKK" << std::endl;

	}

	bool isOpen()
	{
		return openStatus;
	}

	bool clickOutOfJournal(glm::vec2 mousePos) {

		glm::vec2 newPos = Application::Get().MousetoWorld();

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
		if (openStatus == false) {
			return;

		}
		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		allPages[activePage]->Render();

	}

	virtual void Update(float dt, long frame) override {

		if (openStatus == false) {
			return;
		}

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

	void setActiveTab1() { if (activePage != MAIN) { activePage = currentPage::MAIN; } audioManager.PlaySound("pageSwitch", false);};
	void setActiveTab2() { if (activePage != CABIN1) { activePage = currentPage::CABIN1; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab3() { if (activePage != CABIN2) { activePage = currentPage::CABIN2; } audioManager.PlaySound("pageSwitch", false);};
	void setActiveTab4() { if (activePage != CABIN3) { activePage = currentPage::CABIN3; } audioManager.PlaySound("pageSwitch", false);};
	void setActiveTab5() { if (activePage != CABIN4) { activePage = currentPage::CABIN4; } audioManager.PlaySound("pageSwitch", false);};
	void setActiveTab6() { if (activePage != CABIN5) { activePage = currentPage::CABIN5; } audioManager.PlaySound("pageSwitch", false);};
	void setActiveTab7() { if (activePage != FOODGUIDE) { activePage = currentPage::FOODGUIDE; } audioManager.PlaySound("pageSwitch", false); };


protected:

	std::vector<GameObject*> m_gameObjects;
	std::vector<Page*> allPages;

	currentPage activePage = currentPage::MAIN;

	bool openStatus = false; //true - open, false - closed

	glm::vec2 mousePos;

};