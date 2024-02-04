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


enum currentPage {MAIN, CABIN1, CABIN2, CABIN3, CABIN4, CABIN5, GUIDE1, GUIDE2};

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

class Book: public RenderGameObject{

public:

	JournalData journalData;
	

	void drawBook(){

		//DRAW BOOK COVER AND TABS

		//TO FIX WHEN TESTING

		GameObject* JournalCover = new RenderGameObject("JournalCover", "Assets/Images/Journal_Cover.png");
		JournalCover->SetScale(glm::vec3(14.0f, 10.0f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		//m_gameObjects.push_back(JournalCover);

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal_Bookmark_CaseSummary.png", glm::vec3(6.8f, 3.8f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal_Bookmark_Passenger1.png", glm::vec3(6.8f, 2.6f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 1.4f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 0.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal_Bookmark_Passenger 3.png", glm::vec3(6.8f, -1.0f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal_Bookmark_Passenger 4.png", glm::vec3(6.8f, -2.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));

		//m_gameObjects.push_back(Tab1);
		//m_gameObjects.push_back(Tab2);
		//m_gameObjects.push_back(Tab3);
		//m_gameObjects.push_back(Tab4);
		//m_gameObjects.push_back(Tab5);
		//m_gameObjects.push_back(Tab6);


		GameObject* BlankPage = new RenderGameObject("BlankPage", "Assets/Images/Journal_BlankPage.png");
		BlankPage->SetScale(glm::vec3(13.0f, 9.0f, 0.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* JournalSleeve = new RenderGameObject("JounalSleeve", "Assets/Images/Journal_CaseSummary_Sleeve.png");
		JournalSleeve->SetScale(glm::vec3(3.5f, 9.7f, 0.0f));
		JournalSleeve->SetPosition(glm::vec3(-5.3f, 0.0f, 0.0f));

		//m_gameObjects.push_back(JournalSleeve);

		//add all elements above to game object array 

		
		

	}

	void closeBook() {

		activePage = MAIN;

		//make all gameobjects in book inactive

	}

	//void drawMainPage();
	//void drawCharacterPage(currentPage page);
	//void drawTeaGuide();


	void Update(float dt, long frame) override {

		RenderGameObject::Update(dt, frame);

		
		//check which button is clicked and set active page
		


	}


private:

	//status of current page player is on, resets to MAIN everytime player closes book
	currentPage activePage = MAIN;


};