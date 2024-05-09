#pragma once

#include "Page.h"

class CabinPage4 : public Page {

public:

	CabinPage4() :Page() {

		// LEFT PAGE
		GameObject* P1Picture = new UIObject("P1Picture", "Assets/Images/Journal/PassengerPicture_Archibald.png", true);
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new UIObject("PaperClip", "Assets/Images/Journal/PaperClip.png", true);
		PaperClip->SetScale(glm::vec3(0.51f, 0.92f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-4.85f, 3.31f, 0.0f));

		GameObject* InfoPaper = new UIObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png", true);
		InfoPaper->SetScale(glm::vec3(5.41f, 3.30f, 0.0f));
		InfoPaper->SetPosition(glm::vec3(-3.1f, -1.7f, 0.0f));

		Text* Name = new Text("Name", "Sir Archibald Pompington III", "Assets/Fonts/JMH.ttf");
		Name->SetPosition(glm::vec3(-5.3f, -0.75f, 0.0f));
		Name->SetColor(glm::vec3(0, 0, 0));
		Name->SetScale(0.58f);

		Text* Age = new Text("Age", "Age: 27", "Assets/Fonts/JMH.ttf");
		Age->SetPosition(glm::vec3(-5.3f, -1.25f, 0.0f));
		Age->SetColor(glm::vec3(0, 0, 0));
		Age->SetScale(0.47f);

		Text* Citizen = new Text("Citizen", "Citizen: Westside", "Assets/Fonts/JMH.ttf");
		Citizen->SetPosition(glm::vec3(-5.3f, -1.65f, 0.0f));
		Citizen->SetColor(glm::vec3(0, 0, 0));
		Citizen->SetScale(0.47f);

		Text* Occupation = new Text("Occupation", "Occupation: Business Owner", "Assets/Fonts/JMH.ttf");
		Occupation->SetPosition(glm::vec3(-5.3f, -2.05f, 0.0f));
		Occupation->SetColor(glm::vec3(0, 0, 0));
		Occupation->SetScale(0.47f);

		GameObject* CabinStamp = new UIObject("CabinStamp", "Assets/Images/Journal/CabinStamp_3.png", true);
		CabinStamp->SetScale(glm::vec3(2.16f, 1.13f, 0.0f));
		CabinStamp->SetPosition(glm::vec3(-1.3f, -2.7f, 0.0f));


		// RIGHT PAGE
		// CLUES	[A = Archibald, C = Clue]
		Text* A_Clue1 = new Text("A_Clue1", "Wealthy background with a large business", "Assets/Fonts/ESA-m.ttf");
		A_Clue1->SetPosition(glm::vec3(0.9f, 2.7f, 0.0f));
		A_Clue1->SetColor(glm::vec3(0, 0, 0));
		A_Clue1->SetScale(0.56f);

		Text* A_Clue2 = new Text("A_Clue2", "Expert in explosive", "Assets/Fonts/ESA-smb.ttf");
		A_Clue2->SetPosition(glm::vec3(0.9f, 2.2f, 0.0f));
		A_Clue2->SetColor(glm::vec3(0.5, 0, 0));
		A_Clue2->SetScale(0.64f);

		Text* A_Clue3 = new Text("A_Clue3", "Messy attire", "Assets/Fonts/ESA-smb.ttf");
		A_Clue3->SetPosition(glm::vec3(0.9f, 1.7f, 0.0f));
		A_Clue3->SetColor(glm::vec3(0, 0, 0));
		A_Clue3->SetScale(0.6f);

		Text* A_Clue4 = new Text("A_Clue4", "Politic insider newspapers", "Assets/Fonts/ESA-m.ttf");
		A_Clue4->SetPosition(glm::vec3(3.1f, 1.7f, 0.0f));
		A_Clue4->SetColor(glm::vec3(0, 0, 0));
		A_Clue4->SetScale(0.53f);

		Text* A_Clue5 = new Text("A_Clue5", "Carrying a strange gadget with his luggage", "Assets/Fonts/ESA-smb.ttf");
		A_Clue5->SetPosition(glm::vec3(0.88f, 1.2f, 0.0f));
		A_Clue5->SetColor(glm::vec3(0, 0, 0));
		A_Clue5->SetScale(0.6f);

		ClueData* cabin3_clue1 = new ClueData();
		cabin3_clue1->showText = false;
		cabin3_clue1->clueText = A_Clue1;

		ClueData* cabin3_clue2 = new ClueData();
		cabin3_clue2->showText = false;
		cabin3_clue2->clueText = A_Clue2;
		cabin3_clue2->isEvidence = true;

		ClueData* cabin3_clue3 = new ClueData();
		cabin3_clue3->showText = false;
		cabin3_clue3->clueText = A_Clue3;

		ClueData* cabin3_clue4 = new ClueData();
		cabin3_clue4->showText = false;
		cabin3_clue4->clueText = A_Clue4;

		ClueData* cabin3_clue5 = new ClueData();
		cabin3_clue5->showText = false;
		cabin3_clue5->clueText = A_Clue5;


		textClues.push_back(cabin3_clue1);
		textClues.push_back(cabin3_clue2);
		textClues.push_back(cabin3_clue3);
		textClues.push_back(cabin3_clue4);
		textClues.push_back(cabin3_clue5);

		m_journalData->addClueToJournalData(CABIN3, cabin3_clue1);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue2);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue3);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue4);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue5);

		// DIVIDER 1
		GameObject* Divider1 = new UIObject("Divider1", "Assets/Images/Journal/Line_1.png", true);
		Divider1->SetScale(glm::vec3(4.78f, 0.08f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 0.7f, 0.0f));


		// LAST ACTIVITY	[A = Archibald, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.1f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* A_LA1_1 = new Text("A_LA1_1", "Business meeting", "Assets/Fonts/ESA-smb.ttf");
		A_LA1_1->SetPosition(glm::vec3(0.82f, -0.4f, 0.0f));
		A_LA1_1->SetColor(glm::vec3(0, 0, 0));
		A_LA1_1->SetScale(0.58f);

		Text* A_LA1_2 = new Text("A_LA1_2", "with senior officials", "Assets/Fonts/ESA-smb.ttf");
		A_LA1_2->SetPosition(glm::vec3(0.82f, -0.72f, 0.0f));
		A_LA1_2->SetColor(glm::vec3(0, 0, 0));
		A_LA1_2->SetScale(0.58f);

		Text* A_LA2_1 = new Text("A_LA2_1", "Deliver a product", "Assets/Fonts/ESA-smb.ttf");
		A_LA2_1->SetPosition(glm::vec3(3.4f, -0.47, 0.0f));
		A_LA2_1->SetColor(glm::vec3(0.5, 0, 0));
		A_LA2_1->SetScale(0.62f);

		Text* A_LA2_2 = new Text("A_LA2_2", "to Westside client", "Assets/Fonts/ESA-smb.ttf");
		A_LA2_2->SetPosition(glm::vec3(3.4f, -0.8f, 0.0f));
		A_LA2_2->SetColor(glm::vec3(0.5, 0, 0));
		A_LA2_2->SetScale(0.62f);

		ClueData* cabin3_clue6 = new ClueData();
		cabin3_clue6->showText = false;
		cabin3_clue6->clueText = A_LA1_1;

		ClueData* cabin3_clue7 = new ClueData();
		cabin3_clue7->showText = false;
		cabin3_clue7->clueText = A_LA1_2;

		ClueData* cabin3_clue8 = new ClueData();
		cabin3_clue8->showText = false;
		cabin3_clue8->clueText = A_LA2_1;
		cabin3_clue8->isEvidence = true;

		ClueData* cabin3_clue9 = new ClueData();
		cabin3_clue9->showText = false;
		cabin3_clue9->clueText = A_LA2_2;

		textClues.push_back(cabin3_clue6);
		textClues.push_back(cabin3_clue7);
		textClues.push_back(cabin3_clue8);
		textClues.push_back(cabin3_clue9);

		m_journalData->addClueToJournalData(CABIN3, cabin3_clue6);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue7);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue8);
		m_journalData->addClueToJournalData(CABIN3, cabin3_clue9);


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

		RedUnderline_Cabin4 = new UIObject("UnderlineCabin4", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline_Cabin4->setActiveStatus(false);
		RedUnderline_Cabin4->SetScale(glm::vec3(1.7f, 0.1f, 0.0f));
		RedUnderline_Cabin4->SetPosition(glm::vec3(1.1f, -2.0f, 0.0f));

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
		m_gameObjects.push_back(A_LA1_1);
		m_gameObjects.push_back(A_LA1_2);
		m_gameObjects.push_back(A_LA2_1);
		m_gameObjects.push_back(A_LA2_2);

		m_gameObjects.push_back(Divider2);
		m_gameObjects.push_back(LastVisit);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);

		m_gameObjects.push_back(RedUnderline_Cabin4);


	}

	virtual void Update(float dt, long frame) override {

		Page::Update(dt, frame);

		CabinPageData cabinData = m_journalData->GetCabinPageData(Cabin::CABIN3);

		if (!cabinData.ShowLastActivity) {

			RedUnderline_Cabin4->setActiveStatus(false);

		}
		else {

			RedUnderline_Cabin4->setActiveStatus(true);

		}

	}

private:

	UIObject* RedUnderline_Cabin4;


};