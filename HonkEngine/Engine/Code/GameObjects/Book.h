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


enum currentPage {MAIN = 0, CABIN1, CABIN2, CABIN3, CABIN4, CABIN5, GUIDE1, GUIDE2};

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

//SUBCLASS - MAINPAGE
//SUBCLASS - CHARACTERPAGE
//SUBCLASS - TEAGUIDE

class Book: public RenderGameObject{

public:

	void drawBook(){

		//DRAW BOOK COVER AND TABS

		//TO FIX WHEN TESTING

		GameObject* JournalCover = new RenderGameObject("JournalCover", "Assets/Images/Journal_Cover.png");
		JournalCover->SetScale(glm::vec3(1.0f, 1.0f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		GameObject* BlankPage = new RenderGameObject("BlankPage", "Assets/Images/Journal_BlankPage.png");
		BlankPage->SetScale(glm::vec3(0.8f, 0.8f, 0.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		//add all elements above to game object array 

		UIButton* Tab1 = new UIButton("Tab1","Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));

		GameObject* BlankPage2 = new RenderGameObject("BlankPage2", "Assets/Images/Journal_BlankPage.png");
		BlankPage2->SetScale(glm::vec3(0.8f, 0.8f, 0.0f));
		BlankPage2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		GameObject* JournalSleeve = new RenderGameObject("JounalSleeve", "Assets/Images/Journal_CaseSummary_Sleeve.png");
		BlankPage->SetScale(glm::vec3(0.8f, 0.8f, 0.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		if (activePage == MAIN) {

			//move current tab to the front

			//--THE SPY--

			Text* TheSpy = new Text("TheSpy", " The Spy", "Assets/Fonts/WD.ttf");
			//TheSpy->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//TheSpy->SetColor(glm::vec3(1, 1, 1));
			//TheSpy->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));

			//UIButton* Suspect1 = new UIButton("Suspect1", "Assets/Images/Journal_CaseSummary_Icon_Archibald.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));
			
			//Text* Cabin1 = new Text("Cabin1", "Cabin 1", "Assets/Fonts/WD.ttf");
			//Cabin1->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//Cabin1->SetColor(glm::vec3(1, 1, 1));
			//Cabin1->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));

			//UIButton* Suspect2 = new UIButton("Suspect2", "Assets/Images/Journal_CaseSummary_Icon_Evelyn.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));

			//Text* Cabin21 = new Text("Cabin21", "Cabin 2/1", "Assets/Fonts/WD.ttf");
			//Cabin21->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//Cabin21->SetColor(glm::vec3(1, 1, 1));
			//Cabin21->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));

			//UIButton* Suspect3 = new UIButton("Suspect3", "Assets/Images/Journal_CaseSummary_Icon_Martha.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));

			//Text* Cabin22 = new Text("Cabin22", "Cabin 2/2", "Assets/Fonts/WD.ttf");
			//Cabin22->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//Cabin22->SetColor(glm::vec3(1, 1, 1));
			//Cabin22->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));

			//UIButton* Suspect4 = new UIButton("Suspect4", "Assets/Images/Journal_CaseSummary_Icon_Nathaniel.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));

			//Text* Cabin3 = new Text("Cabin3", "Cabin 3", "Assets/Fonts/WD.ttf");
			//Cabin3->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//Cabin3->SetColor(glm::vec3(1, 1, 1));
			//Cabin3->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));

			//UIButton* Suspect5 = new UIButton("Suspect5", "Assets/Images/Journal_CaseSummary_Icon_Octavia.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));

			//Text* Cabin4 = new Text("Cabin4", "Cabin 4", "Assets/Fonts/WD.ttf");
			//Cabin4->SetPosition(glm::vec3(-3.7f, 3.8f, 0.0f));
			//Cabin4->SetColor(glm::vec3(1, 1, 1));
			//Cabin4->SetScale(glm::vec3(-3.7f, 3.8f, 0.0f));




		}
		
		


		//UIElement* journalButton = new UIButton("JournalButton", "Assets/Images/JournalButton.png", glm::vec3(-6.0f, -4.5f, 0.0f), glm::vec3(4.0f, 4.0f, 0.0f));



	}

	void closeBook() {

		activePage = MAIN;

	}

	//void drawMainPage();
	//void drawCharacterPage(currentPage page);
	//void drawTeaGuide();


	virtual void Update(float dt, long frame) override {

		RenderGameObject::Update(dt, frame);

		


	}


private:

	//status of current page player is on, resets to MAIN everytime player closes book
	currentPage activePage = MAIN;

};