#pragma once

#include "GameObject.h"
#include "RenderGameObject.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include "../Input/Input.h"
#include <iostream>
#include "../Application.h"
#include"../Scene/Scene.h"
#include "../Text/Text.h"
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"

#include "Book.h"
#include "JournalData.h"


class MainPage : public Book {


	void DrawPage() {

		Text* TheSpy = new Text("TheSpy", " The Spy", "Assets/Fonts/WD.ttf");
		TheSpy->SetPosition(glm::vec3(0.5f, 3.5f, 0.0f));
		TheSpy->SetColor(glm::vec3(0, 0, 0));
		TheSpy->SetScale(1.0f);

		//SPY BUTTONS

		UIButton* Suspect1 = new UIButton("Suspect1", "Assets/Images/Journal_CaseSummary_Icon_Archibald.png", glm::vec3(1.2f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin1 = new Text("Cabin1", "Cabin 1", "Assets/Fonts/WD.ttf");
		Cabin1->SetPosition(glm::vec3(0.7f, 1.1f, 0.0f));
		Cabin1->SetColor(glm::vec3(0, 0, 0));
		Cabin1->SetScale(0.6f);


		UIButton* Suspect2 = new UIButton("Suspect2", "Assets/Images/Journal_CaseSummary_Icon_Evelyn.png", glm::vec3(3.0f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin21 = new Text("Cabin21", "Cabin 2/1", "Assets/Fonts/WD.ttf");
		Cabin21->SetPosition(glm::vec3(2.3f, 1.1f, 0.0f));
		Cabin21->SetColor(glm::vec3(0, 0, 0));
		Cabin21->SetScale(0.6f);


		UIButton* Suspect3 = new UIButton("Suspect3", "Assets/Images/Journal_CaseSummary_Icon_Martha.png", glm::vec3(4.8f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin22 = new Text("Cabin22", "Cabin 2/2", "Assets/Fonts/WD.ttf");
		Cabin22->SetPosition(glm::vec3(4.2f, 1.1f, 0.0f));
		Cabin22->SetColor(glm::vec3(0, 0, 0));
		Cabin22->SetScale(0.6f);
	

		UIButton* Suspect4 = new UIButton("Suspect4", "Assets/Images/Journal_CaseSummary_Icon_Nathaniel.png", glm::vec3(1.2f, 0.0f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin3 = new Text("Cabin3", "Cabin 3", "Assets/Fonts/WD.ttf");
		Cabin3->SetPosition(glm::vec3(0.7f, -1.2f, 0.0f));
		Cabin3->SetColor(glm::vec3(0, 0, 0));
		Cabin3->SetScale(0.6f);
		

		UIButton* Suspect5 = new UIButton("Suspect5", "Assets/Images/Journal_CaseSummary_Icon_Octavia.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin4 = new Text("Cabin4", "Cabin 4", "Assets/Fonts/WD.ttf");
		Cabin4->SetPosition(glm::vec3(2.3f, -1.2, 0.0f));
		Cabin4->SetColor(glm::vec3(0, 0, 0));
		Cabin4->SetScale(0.6f);

		//check journal data and draw circle around chosen suspect

		//check journal data and draw line
		
		

		
	}

	void Update(float dt, long frame) override {

		Book::Update(dt, frame);

		//check which button is clicked and set data in journal data

		



	}

};