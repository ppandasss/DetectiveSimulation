#pragma once

#include "Page.h"

class CabinPage5 : public Page {

public:

	CabinPage5() :Page(CABIN4) {

		GameObject* BlankPage2 = new UIObject("BlankPage2", "Assets/Images/Journal/Journal_BlankPage2.png", true);
		BlankPage2->SetScale(glm::vec3(12.68f, 7.45f, 1.0f));
		BlankPage2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		// LEFT PAGE
		GameObject* P1Picture = new UIObject("P1Picture", "Assets/Images/Journal/PassengerPicture_Octavia.png", true);
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new UIObject("PaperClip", "Assets/Images/Journal/Journal_Paperclip04.png", true);
		PaperClip->SetScale(glm::vec3(0.49f, 0.91f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-3.75f, 3.47f, 0.0f));

		GameObject* InfoPaper = new UIObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png", true);
		InfoPaper->SetScale(glm::vec3(5.41f, 3.30f, 0.0f));
		InfoPaper->SetPosition(glm::vec3(-3.1f, -1.7f, 0.0f));

		Text* Name = new Text("Name", "Lady Octavia Montgomery", "Assets/Fonts/JMH.ttf");
		Name->SetPosition(glm::vec3(-5.3f, -0.75f, 0.0f));
		Name->SetColor(glm::vec3(0, 0, 0));
		Name->SetScale(0.6f);

		Text* Age = new Text("Age", "Age: 33", "Assets/Fonts/JMH.ttf");
		Age->SetPosition(glm::vec3(-5.3f, -1.25f, 0.0f));
		Age->SetColor(glm::vec3(0, 0, 0));
		Age->SetScale(0.47f);

		Text* Citizen = new Text("Citizen", "Citizen: Westside", "Assets/Fonts/JMH.ttf");
		Citizen->SetPosition(glm::vec3(-5.3f, -1.65f, 0.0f));
		Citizen->SetColor(glm::vec3(0, 0, 0));
		Citizen->SetScale(0.47f);

		Text* Occupation = new Text("Occupation", "Occupation: Theatrical Performer", "Assets/Fonts/JMH.ttf");
		Occupation->SetPosition(glm::vec3(-5.3f, -2.05f, 0.0f));
		Occupation->SetColor(glm::vec3(0, 0, 0));
		Occupation->SetScale(0.47f);

		GameObject* CabinStamp = new UIObject("CabinStamp", "Assets/Images/Journal/CabinStamp_4.png", true);
		CabinStamp->SetScale(glm::vec3(2.19f, 1.14f, 0.0f));
		CabinStamp->SetPosition(glm::vec3(-1.75f, -2.75f, 0.0f));


		// RIGHT PAGE
		// CLUES	[O = Octavia, C = Clue]
		Text* O_Clue1 = new Text("O_Clue1", "Westside's Minister ex-wife", "Assets/Fonts/ESA-smb.ttf");
		O_Clue1->SetPosition(glm::vec3(0.9f, 2.65f, 0.0f));
		O_Clue1->SetColor(glm::vec3(0, 0, 0));
		O_Clue1->SetScale(0.53f);

		Text* O_Clue2 = new Text("O_Clue2", "Opera singer, travelling between East and West", "Assets/Fonts/ESA-m.ttf");
		O_Clue2->SetPosition(glm::vec3(0.9f, 2.2f, 0.0f));
		O_Clue2->SetColor(glm::vec3(0.58, 0.04, 0.00));
		O_Clue2->SetScale(0.54f);

		Text* O_Clue3 = new Text("O_Clue3", "High cult missionary", "Assets/Fonts/ESA-m.ttf");
		O_Clue3->SetPosition(glm::vec3(0.9f, 1.75f, 0.0f));
		O_Clue3->SetColor(glm::vec3(0, 0, 0));
		O_Clue3->SetScale(0.58f);

		Text* O_Clue4 = new Text("O_Clue4", "The cult obsessively dedicated to Westside", "Assets/Fonts/ESA-smb.ttf");
		O_Clue4->SetPosition(glm::vec3(0.88f, 1.27f, 0.0f));
		O_Clue4->SetColor(glm::vec3(0.58, 0.04, 0.00));
		O_Clue4->SetScale(0.58f);

		textClues.push_back(O_Clue1);
		textClues.push_back(O_Clue2);
		textClues.push_back(O_Clue3);
		textClues.push_back(O_Clue4);

		m_journalData->addEvidenceToJournal(CABIN4, 1, O_Clue2->GetContent());
		m_journalData->addEvidenceToJournal(CABIN4, 3, O_Clue4->GetContent());



		// LAST ACTIVITY	[O = Octavia, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.1f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* O_LA1 = new Text("O_LA1", "Spread the cult ideology", "Assets/Fonts/ESA-smb.ttf");
		O_LA1->SetPosition(glm::vec3(0.82f, -0.4f, 0.0f));
		O_LA1->SetColor(glm::vec3(0, 0, 0));
		O_LA1->SetScale(0.58f);

		Text* O_LA2 = new Text("O_LA2", "Meet the devotees at Town Square afterward", "Assets/Fonts/ESA-m.ttf");
		O_LA2->SetPosition(glm::vec3(1.8f, -0.8f, 0.0f));
		O_LA2->SetColor(glm::vec3(0, 0, 0));
		O_LA2->SetScale(0.52f);

		textClues.push_back(O_LA1);
		textClues.push_back(O_LA2);



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

		RedUnderline_Cabin5 = new UIObject("UnderlineCabin5", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline_Cabin5->setActiveStatus(false);
		RedUnderline_Cabin5->SetScale(glm::vec3(1.77f, 0.13f, 0.0f));
		RedUnderline_Cabin5->SetPosition(glm::vec3(3.72f, -2.535f, 0.0f));

		textClues.push_back(RedUnderline_Cabin5);

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

	UIObject* RedUnderline_Cabin5;

};