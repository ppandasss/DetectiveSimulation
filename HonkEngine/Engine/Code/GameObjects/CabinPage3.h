#pragma once

#include "Page.h"

class CabinPage3 : public Page {

public:

	CabinPage3() :Page(CABIN22) {

		GameObject* BlankPage2 = new UIObject("BlankPage2", "Assets/Images/Journal/Journal_BlankPage2.png", true);
		BlankPage2->SetScale(glm::vec3(12.68f, 7.45f, 1.0f));
		BlankPage2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		// LEFT PAGE
		GameObject* P1Picture = new UIObject("P1Picture", "Assets/Images/Journal/PassengerPicture_Evelyn.png", true);
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new UIObject("PaperClip", "Assets/Images/Journal/Journal_Paperclip04.png", true);
		PaperClip->SetScale(glm::vec3(0.49f, 0.91f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-4.35f, 3.46f, 0.0f));

		GameObject* InfoPaper = new UIObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png", true);
		InfoPaper->SetScale(glm::vec3(5.41f, 3.30f, 0.0f));
		InfoPaper->SetPosition(glm::vec3(-3.1f, -1.7f, 0.0f));

		Text* Name = new Text("Name", "Evelyn Hartington", "Assets/Fonts/JMH.ttf");
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
		CabinStamp->SetPosition(glm::vec3(-3.1f, -2.8f, 0.0f));


		// RIGHT PAGE
		// CLUES	[E = Evelyn, C = Clue]
		Text* E_Clue1 = new Text("E_Clue1", "Moving to Westside withb only one small luggage", "Assets/Fonts/ESA-smb.ttf");
		E_Clue1->SetPosition(glm::vec3(0.87f, 2.65f, 0.0f));
		E_Clue1->SetColor(glm::vec3(0.58, 0.04, 0.00));
		E_Clue1->SetScale(0.55f);

		Text* E_Clue2 = new Text("E_Clue2", "Seems very close with her mother", "Assets/Fonts/ESA-m.ttf");
		E_Clue2->SetPosition(glm::vec3(0.87f, 2.2f, 0.0f));
		E_Clue2->SetColor(glm::vec3(0, 0, 0));
		E_Clue2->SetScale(0.58f);

		Text* E_Clue3 = new Text("E_Clue3", "Afraid to talk about National Day event", "Assets/Fonts/ESA-m.ttf");
		E_Clue3->SetPosition(glm::vec3(0.87f, 1.75f, 0.0f));
		E_Clue3->SetColor(glm::vec3(0, 0, 0));
		E_Clue3->SetScale(0.58f);

		Text* E_Clue4 = new Text("E_Clue4", "Strangely scared of the bomb situation", "Assets/Fonts/ESA-smb.ttf");
		E_Clue4->SetPosition(glm::vec3(0.85f, 1.27f, 0.0f));
		E_Clue4->SetColor(glm::vec3(0, 0, 0));
		E_Clue4->SetScale(0.62f);


		textClues.push_back(E_Clue1);
		textClues.push_back(E_Clue2);
		textClues.push_back(E_Clue3);
		textClues.push_back(E_Clue4);

		m_journalData->addEvidenceToJournal(CABIN22, 0, E_Clue1->GetContent());




		// LAST ACTIVITY	[E = Evelyn, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.1f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* E_LA1 = new Text("E_LA1", "Listen to the court verdict with their father", "Assets/Fonts/ESA-m.ttf");
		E_LA1->SetPosition(glm::vec3(0.8f, -0.4f, 0.0f));
		E_LA1->SetColor(glm::vec3(0, 0, 0));
		E_LA1->SetScale(0.58f);

		Text* E_LA2 = new Text("E_LA2", "Met his brother at National Day Event", "Assets/Fonts/ESA-smb.ttf");
		E_LA2->SetPosition(glm::vec3(1.05f, -0.8f, 0.0f));
		E_LA2->SetColor(glm::vec3(0.58, 0.04, 0.00));
		E_LA2->SetScale(0.48f);

		textClues.push_back(E_LA1);
		textClues.push_back(E_LA2);

		m_journalData->addEvidenceToJournal(CABIN22, 5, E_LA2->GetContent());




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

		RedUnderline_Cabin3 = new UIObject("UnderlineCabin3", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline_Cabin3->setActiveStatus(false);
		RedUnderline_Cabin3->SetScale(glm::vec3(1.77f, 0.13f, 0.0f));
		RedUnderline_Cabin3->SetPosition(glm::vec3(3.72f, -3.05f, 0.0f));

		textClues.push_back(RedUnderline_Cabin3);

		m_gameObjects.push_back(BlankPage2);
		m_gameObjects.push_back(P1Picture);
		m_gameObjects.push_back(PaperClip);
		m_gameObjects.push_back(InfoPaper);

		m_gameObjects.push_back(Name);
		m_gameObjects.push_back(Age);
		m_gameObjects.push_back(Citizen);
		m_gameObjects.push_back(Occupation);
		m_gameObjects.push_back(CabinStamp);

		m_gameObjects.push_back(LastActivity);
		m_gameObjects.push_back(LastVisit);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);


	}


private:

	UIObject* RedUnderline_Cabin3;



};