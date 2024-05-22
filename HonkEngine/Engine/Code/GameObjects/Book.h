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


enum currentPage { MAIN_PAGE, CABIN1_PAGE, CABIN2_PAGE, CABIN3_PAGE, CABIN4_PAGE, CABIN5_PAGE, FOODGUIDE_PAGE };

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

class Book : public GameObject {

public:
	AudioManager& audioManager;

public:

	GameObject* JournalCover;

	Book() : GameObject("Book"), audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("openJournal", "Assets/Sounds/Journal/SFX_OpenJournal.mp3",SFX, 0.3f);
		audioManager.LoadSound("pageSwitch", "Assets/Sounds/Journal/SFX_PageSwitch.mp3",SFX, 0.2f);

		JournalCover = new UIObject("JournalCover", "Assets/Images/Journal/Cover.png", true);
		JournalCover->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal/Bookmark_CaseSummary.png", glm::vec3(6.57f, 2.87f, 0.0f), glm::vec3(2.25f, 0.96f, 0.0f), true, false, "");
		Tab1->SetHoverTexture("Assets/Images/Journal/Bookmark_CaseSummary_Highlight.png");

		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal/Bookmark_P1.png", glm::vec3(6.57f, 1.85f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab2->SetHoverTexture("Assets/Images/Journal/Bookmark_P1_Highlight.png");

		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal/Bookmark_P2_1.png", glm::vec3(6.55f, 0.92f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab3->SetHoverTexture("Assets/Images/Journal/Bookmark_P2_1_Highlight.png");

		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal/Bookmark_P2_2.png", glm::vec3(6.61f, 0.0f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab4->SetHoverTexture("Assets/Images/Journal/Bookmark_P2_2_Highlight.png");

		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal/Bookmark_P3.png", glm::vec3(6.55f, -0.93f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab5->SetHoverTexture("Assets/Images/Journal/Bookmark_P3_Highlight.png");

		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal/Bookmark_P4.png", glm::vec3(6.55f, -1.85f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab6->SetHoverTexture("Assets/Images/Journal/Bookmark_P4_Highlight.png");

		UIButton* Tab7 = new UIButton("Tab6", "Assets/Images/Journal/Bookmark_TeaGuide.png", glm::vec3(6.49f, -2.8f, 0.0f), glm::vec3(2.13f, 0.91f, 0.0f), true, false, "");
		Tab7->SetHoverTexture("Assets/Images/Journal/Bookmark_TeaGuide_Highlight.png");

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

		UIButton* CloseJournalButton = new UIButton("CloseButton", "Assets/Images/Journal/Journal_CloseButton.png", glm::vec3(5.25f, 4.0f, 0.0f), glm::vec3(1.04f, 1.70f, 0.0f), true, false, "");
		CloseJournalButton->SetOnClickAction([this]() { closeJournal(); });
		CloseJournalButton->SetHoverTexture("Assets/Images/Journal/Journal_CloseButton_Highlight.png");

		m_gameObjects.push_back(BackGround);
		m_gameObjects.push_back(JournalCover);
		m_gameObjects.push_back(Tab1);
		m_gameObjects.push_back(Tab2);
		m_gameObjects.push_back(Tab3);
		m_gameObjects.push_back(Tab4);
		m_gameObjects.push_back(Tab5);
		m_gameObjects.push_back(Tab6);
		m_gameObjects.push_back(Tab7);
		m_gameObjects.push_back(CloseJournalButton);
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

		//draggableClues.push_back(Cabin3Newspaper);
		//draggableClues.push_back(Cabin4Pamphlet);

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

		for (int i = 0; i < 2; i++) {

			if (m_journal->getBookClueState(i)) {
				draggableClues[i]->setActiveStatus(true);
			}

		}

		//std::cout << "OPEN BOOKK" << std::endl;
	}

	void closeBook() {

		//make all gameobjects in book inactive

		audioManager.PlaySound("openJournal", false);

		openStatus = false;
		activePage = currentPage::MAIN_PAGE;

		for (auto& object : m_gameObjects) {
			if (object->getActiveStatus()) { //IF ACTIVE SET AS INACTIVE
				object->setActiveStatus(false);
			}
		}

		for (auto& object : allPages)
		{
			object->setActiveStatus(false);
		}

		for (auto& object : draggableClues)
		{
			object->setActiveStatus(false);
		}

		//std::cout << "CLOSE BOOKK" << std::endl;

	}

	bool isOpen()
	{
		return openStatus;
	}

	void EmptyFunction() {
		return;
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

		for (int i = 0; i < 2; i++) {

			if (m_journal->getBookClueState(i)) {
				draggableClues[i]->Render();
			}

		}

	}

	virtual void Update(float dt, long frame) override {

		if (openStatus == false) {
			return;
		}


		//for (auto& object : m_gameObjects) {
		//	if (object->getActiveStatus()) { //CHECK ACTIVE STATUS
		//		object->Update(dt, frame);
		//	}
		//}

		for (auto it = m_gameObjects.rbegin(); it != m_gameObjects.rend(); ++it) {
			GameObject* object = *it;
			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS
				object->Update(dt, frame);
			}
		}

		for (int i = 0; i < 2; i++) {

			if (m_journal->getBookClueState(i)) {

				if (draggableClues[i]->getActiveStatus()) { //CHECK ACTIVE STATUS

					draggableClues[i]->Update(dt, frame);

				}

			}

		}



		allPages[activePage]->Update(dt, frame);

	}

	//-----------------------BOOK UI BUTTON FUNCTIONS-----------------------------------

	void setActiveTab1() { if (activePage != MAIN_PAGE) { activePage = currentPage::MAIN_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab2() { if (activePage != CABIN1_PAGE) { activePage = currentPage::CABIN1_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab3() { if (activePage != CABIN2_PAGE) { activePage = currentPage::CABIN2_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab4() { if (activePage != CABIN3_PAGE) { activePage = currentPage::CABIN3_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab5() { if (activePage != CABIN4_PAGE) { activePage = currentPage::CABIN4_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab6() { if (activePage != CABIN5_PAGE) { activePage = currentPage::CABIN5_PAGE; } audioManager.PlaySound("pageSwitch", false); };
	void setActiveTab7() { if (activePage != FOODGUIDE_PAGE) { activePage = currentPage::FOODGUIDE_PAGE; } audioManager.PlaySound("pageSwitch", false); };

	void closeJournal() {
		if (openStatus == true) {
			if (!m_journal->GetBookState()) { //If book is not locked
				closeBook();
			}
		}
	}



protected:

	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> draggableClues;

	std::vector<Page*> allPages;

	currentPage activePage = currentPage::MAIN_PAGE;

	bool openStatus = false; //true - open, false - closed 

	glm::vec2 mousePos;

	JournalData* m_journal = JournalData::GetInstance();

};