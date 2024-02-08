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

	JournalData journalData;
	
	Book() : GameObject("Book") {

		GameObject* JournalCover = new RenderGameObject("JournalCover", "Assets/Images/Journal_Cover.png");
		JournalCover->SetScale(glm::vec3(14.0f, 10.0f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal_Bookmark_CaseSummary.png", glm::vec3(6.8f, 3.8f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal_Bookmark_Passenger1.png", glm::vec3(6.8f, 2.6f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 1.4f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 0.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal_Bookmark_Passenger 3.png", glm::vec3(6.8f, -1.0f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal_Bookmark_Passenger 4.png", glm::vec3(6.8f, -2.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f), true);

		m_gameObjects.push_back(JournalCover);

		m_gameObjects.push_back(Tab1);
		m_gameObjects.push_back(Tab2);
		m_gameObjects.push_back(Tab3);
		m_gameObjects.push_back(Tab4);
		m_gameObjects.push_back(Tab5);
		m_gameObjects.push_back(Tab6);


		GameObject* BlankPage = new RenderGameObject("BlankPage", "Assets/Images/Journal_BlankPage.png");
		BlankPage->SetScale(glm::vec3(13.0f, 9.0f, 0.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* JournalSleeve = new RenderGameObject("JounalSleeve", "Assets/Images/Journal_CaseSummary_Sleeve.png");
		JournalSleeve->SetScale(glm::vec3(3.5f, 9.7f, 0.0f));
		JournalSleeve->SetPosition(glm::vec3(-5.3f, 0.0f, 0.0f));

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


	void drawBook(){


		for (auto& object : m_gameObjects) {

			if (!object->getActiveStatus()) { //IF NOT ACTIVE SET AS ACTIVE

				object->setActiveStatus(true);

			}

		}

		//add all elements above to game object array 


	}

	void closeBook() {

		activePage = MAIN;

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //IF ACTIVE SET AS INACTIVE

				object->setActiveStatus(false);

			}

		}

		//make all gameobjects in book inactive

	}

	virtual void Render() override
	{

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		allPages[activePage]->Render();

	}

protected:

	std::vector<GameObject*> m_gameObjects;

	std::vector<Page*> allPages;

	currentPage activePage = MAIN;


};