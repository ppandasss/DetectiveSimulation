#pragma once

#include "Page.h"

class CabinPage2 : public Page {

public:

	CabinPage2() :Page() {

		// LEFT PAGE
		GameObject* P1Picture = new UIObject("P1Picture", "Assets/Images/Journal/PassengerPicture_Nathaniel.png", true);
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new UIObject("PaperClip", "Assets/Images/Journal/PaperClip.png", true);
		PaperClip->SetScale(glm::vec3(0.51f, 0.92f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-5.0f, 3.31f, 0.0f));

		GameObject* InfoPaper = new UIObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png", true);
		InfoPaper->SetScale(glm::vec3(5.41f, 3.30f, 0.0f));
		InfoPaper->SetPosition(glm::vec3(-3.1f, -1.7f, 0.0f));

		Text* Name = new Text("Name", "Nathaniel Hartington", "Assets/Fonts/JMH.ttf");
		Name->SetPosition(glm::vec3(-5.3f, -0.75f, 0.0f));
		Name->SetColor(glm::vec3(0, 0, 0));
		Name->SetScale(0.6f);

		Text* Age = new Text("Age", "Age: 15", "Assets/Fonts/JMH.ttf");
		Age->SetPosition(glm::vec3(-5.3f, -1.25f, 0.0f));
		Age->SetColor(glm::vec3(0, 0, 0));
		Age->SetScale(0.47f);

		Text* Citizen = new Text("Citizen", "Citizen: Eastside", "Assets/Fonts/JMH.ttf");
		Citizen->SetPosition(glm::vec3(-5.3f, -1.65f, 0.0f));
		Citizen->SetColor(glm::vec3(0, 0, 0));
		Citizen->SetScale(0.47f);

		Text* Occupation = new Text("Occupation", "Occupation: Student", "Assets/Fonts/JMH.ttf");
		Occupation->SetPosition(glm::vec3(-5.3f, -2.05f, 0.0f));
		Occupation->SetColor(glm::vec3(0, 0, 0));
		Occupation->SetScale(0.47f);

		GameObject* CabinStamp = new UIObject("CabinStamp", "Assets/Images/Journal/CabinStamp_2.png", true);
		CabinStamp->SetScale(glm::vec3(2.25f, 1.13f, 0.0f));
		CabinStamp->SetPosition(glm::vec3(-2.2f, -2.8f, 0.0f));


		// RIGHT PAGE
		// CLUES	[N = Nathaniel, C = Clue]
		Text* N_Clue1 = new Text("N_Clue1", "Moving to Westside to stay with his mother", "Assets/Fonts/ESA-smb.ttf");
		N_Clue1->SetPosition(glm::vec3(0.87f, 2.7f, 0.0f));
		N_Clue1->SetColor(glm::vec3(0.5, 0, 0));
		N_Clue1->SetScale(0.55f);

		Text* N_Clue2 = new Text("N_Clue2", "Not very close with his sister as seemed", "Assets/Fonts/ESA-m.ttf");
		N_Clue2->SetPosition(glm::vec3(0.87f, 2.2f, 0.0f));
		N_Clue2->SetColor(glm::vec3(0, 0, 0));
		N_Clue2->SetScale(0.58f);

		Text* N_Clue3 = new Text("N_Clue3", "Doesn't care about the bomb situation", "Assets/Fonts/ESA-m.ttf");
		N_Clue3->SetPosition(glm::vec3(0.87f, 1.7f, 0.0f));
		N_Clue3->SetColor(glm::vec3(0, 0, 0));
		N_Clue3->SetScale(0.58f);

		Text* N_Clue4 = new Text("N_Clue4", "Take medicine daily Chronic illness?", "Assets/Fonts/ESA-smb.ttf");
		N_Clue4->SetPosition(glm::vec3(0.85f, 1.2f, 0.0f));
		N_Clue4->SetColor(glm::vec3(0, 0, 0));
		N_Clue4->SetScale(0.62f);

		ClueData* cabin21_clue1 = new ClueData();
		cabin21_clue1->showClue = true;
		cabin21_clue1->clueObject = N_Clue1;
		cabin21_clue1->isEvidence = true;

		ClueData* cabin21_clue2 = new ClueData();
		cabin21_clue2->showClue = true;
		cabin21_clue2->clueObject = N_Clue2;

		ClueData* cabin21_clue3 = new ClueData();
		cabin21_clue3->showClue = true;
		cabin21_clue3->clueObject = N_Clue3;

		ClueData* cabin21_clue4 = new ClueData();
		cabin21_clue4->showClue = true;
		cabin21_clue4->clueObject = N_Clue4;


		// DIVIDER 1
		GameObject* Divider1 = new UIObject("Divider1", "Assets/Images/Journal/Line_1.png", true);
		Divider1->SetScale(glm::vec3(4.78f, 0.08f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 0.7f, 0.0f));


		// LAST ACTIVITY	[N = Nathaniel, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.1f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* N_LA1 = new Text("N_LA1", "Listen to the court verdict with their father", "Assets/Fonts/ESA-m.ttf");
		N_LA1->SetPosition(glm::vec3(0.8f, -0.4f, 0.0f));
		N_LA1->SetColor(glm::vec3(0, 0, 0));
		N_LA1->SetScale(0.58f);

		Text* N_LA2 = new Text("N_LA2", "After visiting National Day Event with his sister", "Assets/Fonts/ESA-smb.ttf");
		N_LA2->SetPosition(glm::vec3(1.15f, -0.8f, 0.0f));
		N_LA2->SetColor(glm::vec3(0.5, 0, 0));
		N_LA2->SetScale(0.5f);

		ClueData* cabin21_clue5 = new ClueData();
		cabin21_clue5->showClue = true;
		cabin21_clue5->clueObject = N_LA1;

		ClueData* cabin21_clue6 = new ClueData();
		cabin21_clue6->showClue = true;
		cabin21_clue6->clueObject = N_LA2;
		cabin21_clue6->isEvidence = true;

		textClues.push_back(cabin21_clue1);
		textClues.push_back(cabin21_clue2);
		textClues.push_back(cabin21_clue3);
		textClues.push_back(cabin21_clue4);

		textClues.push_back(cabin21_clue5);
		textClues.push_back(cabin21_clue6);

		m_journalData->addClueToJournalData(CABIN21, cabin21_clue1);
		m_journalData->addClueToJournalData(CABIN21, cabin21_clue2);
		m_journalData->addClueToJournalData(CABIN21, cabin21_clue3);
		m_journalData->addClueToJournalData(CABIN21, cabin21_clue4);

		m_journalData->addClueToJournalData(CABIN21, cabin21_clue5);
		m_journalData->addClueToJournalData(CABIN21, cabin21_clue6);


		// DIVIDER 2
		GameObject* Divider2 = new UIObject("Divider2", "Assets/Images/Journal/Line_2.png", true);
		Divider2->SetScale(glm::vec3(4.8f, 0.06f, 0.0f));
		Divider2->SetPosition(glm::vec3(3.2f, -1.25f, 0.0f));


		// LAST VISIT
		Text* LastVisit = new Text("LastVisit", "Last Visit", "Assets/Fonts/mvboli.ttf");
		LastVisit->SetPosition(glm::vec3(0.8f, -1.95f, 0.0f));
		LastVisit->SetColor(glm::vec3(0, 0, 0));
		LastVisit->SetScale(0.85f);

		Text* TownSquare = new Text("TownSquare", "Town Square", "Assets/Fonts/ESA-m.ttf");
		TownSquare->SetPosition(glm::vec3(0.8f, -2.45f, 0.0f));
		TownSquare->SetColor(glm::vec3(0, 0, 0));
		TownSquare->SetScale(0.6f);

		Text* TheHolyChurch = new Text("TheHolyChurch", "The Holy Church", "Assets/Fonts/ESA-m.ttf");
		TheHolyChurch->SetPosition(glm::vec3(2.9f, -2.45f, 0.0f));
		TheHolyChurch->SetColor(glm::vec3(0, 0, 0));
		TheHolyChurch->SetScale(0.6f);

		Text* TheCouncil = new Text("TheCouncil", "The Council", "Assets/Fonts/ESA-m.ttf");
		TheCouncil->SetPosition(glm::vec3(0.8f, -2.95f, 0.0f));
		TheCouncil->SetColor(glm::vec3(0, 0, 0));
		TheCouncil->SetScale(0.6f);

		Text* SupremeCourt = new Text("SupremeCourt", "Supreme Court", "Assets/Fonts/ESA-m.ttf");
		SupremeCourt->SetPosition(glm::vec3(2.9f, -2.95f, 0.0f));
		SupremeCourt->SetColor(glm::vec3(0, 0, 0));
		SupremeCourt->SetScale(0.6f);

		RedUnderline_Cabin2 = new UIObject("UnderlineCabin2", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline_Cabin2->setActiveStatus(false);
		RedUnderline_Cabin2->SetScale(glm::vec3(1.7f, 0.1f, 0.0f));
		RedUnderline_Cabin2->SetPosition(glm::vec3(1.1f, -2.0f, 0.0f));


		ClueData* cabin21_clue7 = new ClueData();
		cabin21_clue7->showClue = false;
		cabin21_clue7->clueObject = RedUnderline_Cabin2;

		textClues.push_back(cabin21_clue7);
		m_journalData->addClueToJournalData(CABIN21, cabin21_clue7);

		m_gameObjects.push_back(P1Picture);
		m_gameObjects.push_back(PaperClip);
		m_gameObjects.push_back(InfoPaper);

		m_gameObjects.push_back(Name);
		m_gameObjects.push_back(Age);
		m_gameObjects.push_back(Citizen);
		m_gameObjects.push_back(Occupation);
		m_gameObjects.push_back(CabinStamp);

		m_gameObjects.push_back(Divider1);

		m_gameObjects.push_back(LastActivity);

		m_gameObjects.push_back(Divider2);
		m_gameObjects.push_back(LastVisit);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);

	}



private:

	UIObject* RedUnderline_Cabin2;
	


};