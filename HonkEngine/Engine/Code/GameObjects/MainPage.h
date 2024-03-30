#pragma once

#include "Page.h"

class MainPage : public Page {

public:

	MainPage() :Page() {

		// DRAGGABLE PAPERS

		UIDraggable* CaseNews = new UIDraggable("CaseNews", "Assets/Images/Journal/CaseSummary_News.png", glm::vec3(-3.2f, 0.0f, 0.0f), glm::vec3(5.34f, 6.85f, 0.0f), true);

		UIDraggable* Ticket = new UIDraggable("Ticket", "Assets/Images/Journal/CaseSummary_Ticket.png", glm::vec3(-3.7f, 0.75f, 1.0f), glm::vec3(4.18f, 1.65f, 0.0f), true);

		//JOURNAL PART
		GameObject* JournalSleeve = new UIObject("JounalSleeve", "Assets/Images/Journal/CaseSummary_Sleeve.png", true);
		JournalSleeve->SetScale(glm::vec3(2.68f, 8.09f, 0.0f));
		JournalSleeve->SetPosition(glm::vec3(-5.8f, 0.0f, 0.0f));

		// HEADINGS
		Text* TheSpy = new Text("TheSpy", "The Spy", "Assets/Fonts/mvboli.ttf");
		TheSpy->SetPosition(glm::vec3(0.8f, 2.8f, 0.0f));
		TheSpy->SetColor(glm::vec3(0, 0, 0));
		TheSpy->SetScale(0.85f);

		Text* Evidence = new Text("Evidence", "Evidence", "Assets/Fonts/mvboli.ttf");
		Evidence->SetPosition(glm::vec3(0.8f, -0.5f, 0.0f));
		Evidence->SetColor(glm::vec3(0, 0, 0));
		Evidence->SetScale(0.85f);

		Text* BombLocation = new Text("BombLocation", "Bomb Location", "Assets/Fonts/mvboli.ttf");
		BombLocation->SetPosition(glm::vec3(0.8f, -1.75f, 0.0f));
		BombLocation->SetColor(glm::vec3(0, 0, 0));
		BombLocation->SetScale(0.85f);


		//SPY BUTTONS

		UIButton* Suspect1 = new UIButton("Suspect1", "Assets/Images/Journal/CaseSummary_Icon_Martha.png", glm::vec3(1.25f, 2.15f, 0.0f), glm::vec3(0.864f, 0.81f, 0.0f), true, false, "");
		Suspect1->SetOnClickAction([this]() { setSpy1(); });

		Text* Cabin1 = new Text("Cabin1", "Cabin 1", "Assets/Fonts/ESA-m.ttf");
		Cabin1->SetPosition(glm::vec3(0.85f, 1.5f, 0.0f));
		Cabin1->SetColor(glm::vec3(0, 0, 0));
		Cabin1->SetScale(0.55f);


		UIButton* Suspect2 = new UIButton("Suspect2", "Assets/Images/Journal/CaseSummary_Icon_Nathaniel.png", glm::vec3(2.65f, 2.15f, 0.0f), glm::vec3(0.864f, 0.81f, 0.0f), true, false, "");
		Suspect2->SetOnClickAction([this]() { setSpy21(); });

		Text* Cabin21 = new Text("Cabin21", "Cabin 2/1", "Assets/Fonts/ESA-m.ttf");
		Cabin21->SetPosition(glm::vec3(2.25f, 1.5f, 0.0f));
		Cabin21->SetColor(glm::vec3(0, 0, 0));
		Cabin21->SetScale(0.5f);


		UIButton* Suspect3 = new UIButton("Suspect3", "Assets/Images/Journal/CaseSummary_Icon_Evelyn.png", glm::vec3(4.2f, 2.15f, 0.0f), glm::vec3(0.864f, 0.81f, 0.0f), true, false, "");
		Suspect3->SetOnClickAction([this]() { setSpy22(); });

		Text* Cabin22 = new Text("Cabin22", "Cabin 2/2", "Assets/Fonts/ESA-m.ttf");
		Cabin22->SetPosition(glm::vec3(3.75f, 1.5f, 0.0f));
		Cabin22->SetColor(glm::vec3(0, 0, 0));
		Cabin22->SetScale(0.5f);


		UIButton* Suspect4 = new UIButton("Suspect4", "Assets/Images/Journal/CaseSummary_Icon_Archibald.png", glm::vec3(1.25f, 0.85f, 0.0f), glm::vec3(0.864f, 0.81f, 0.0f), true, false, "");
		Suspect4->SetOnClickAction([this]() { setSpy3(); });

		Text* Cabin3 = new Text("Cabin3", "Cabin 3", "Assets/Fonts/ESA-m.ttf");
		Cabin3->SetPosition(glm::vec3(0.9f, 0.2f, 0.0f));
		Cabin3->SetColor(glm::vec3(0, 0, 0));
		Cabin3->SetScale(0.5f);


		UIButton* Suspect5 = new UIButton("Suspect5", "Assets/Images/Journal/CaseSummary_Icon_Octavia.png", glm::vec3(2.65f, 0.85f, 0.0f), glm::vec3(0.864f, 0.81f, 0.0f), true, false, "");
		Suspect5->SetOnClickAction([this]() { setSpy4(); });

		Text* Cabin4 = new Text("Cabin4", "Cabin 4", "Assets/Fonts/ESA-m.ttf");
		Cabin4->SetPosition(glm::vec3(2.3f, 0.2f, 0.0f));
		Cabin4->SetColor(glm::vec3(0, 0, 0));
		Cabin4->SetScale(0.5f);

		RedCircle = new UIObject("RedCircle", "Assets/Images/Journal/Journal_CaseSummary_Icon_Red_Circle_3.png", true);
		RedCircle->setActiveStatus(false);
		RedCircle->SetScale(glm::vec3(1.44f, 0.44f, 0.0f));
		RedCircle->SetPosition(glm::vec3(1.15f, 1.55f, 0.0f));

		// BOMB LOCATIONS

		UIButtonEmpty* TownSquare = new UIButtonEmpty("TownSquare", glm::vec3(1.4f, -2.25f, 0.0f), glm::vec3(1.4f, 0.4f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
		TownSquare->SetButtonText("Town Square");
		TownSquare->SetTextSize(0.6f);
		TownSquare->SetOnClickAction([this]() { setLocationTownSquare(); });

		UIButtonEmpty* TheHolyChurch = new UIButtonEmpty("TheHolyChurch", glm::vec3(3.5f, -2.25f, 0.0f), glm::vec3(1.4f, 0.4f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
		TheHolyChurch->SetButtonText("The Holy Church");
		TheHolyChurch->SetTextSize(0.6f);
		TheHolyChurch->SetOnClickAction([this]() { setLocationHolyChurch(); });

		UIButtonEmpty* TheCouncil = new UIButtonEmpty("TheCouncil", glm::vec3(1.4f, -2.75f, 0.0f), glm::vec3(1.4f, 0.4f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
		TheCouncil->SetButtonText("The Council");
		TheCouncil->SetTextSize(0.6f);
		TheCouncil->SetOnClickAction([this]() { setLocationCouncil(); });

		UIButtonEmpty* SupremeCourt = new UIButtonEmpty("SupremeCourt", glm::vec3(3.5f, -2.75f, 0.0f), glm::vec3(1.4f, 0.4f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
		SupremeCourt->SetButtonText("Supreme Court");
		SupremeCourt->SetTextSize(0.6f);
		SupremeCourt->SetOnClickAction([this]() { setLocationSupremeCourt(); });

		RedUnderline = new UIObject("RedUnderline", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline->setActiveStatus(false);
		RedUnderline->SetScale(glm::vec3(1.7f, 0.1f, 0.0f));
		RedUnderline->SetPosition(glm::vec3(1.1f, -2.0f, 0.0f));
		// EVIDENCE TEXT

		EvidenceButton = new UIButtonEmpty("EvidenceText", glm::vec3(3.2f, -1.0f, 0.0f), glm::vec3(5.0f, 0.5f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
		EvidenceButton->SetButtonText(JournalData::GetInstance()->getEvidenceText());
		EvidenceButton->SetTextSize(0.6f);
		EvidenceButton->SetOnClickAction([this]() { updateEvidence(); });


		/*UIObject* testBox = new UIObject("testBox", "Assets/Images/Square_Border.png", true);
		testBox->SetScale(glm::vec3(5.0f, 0.5f, 0.0f));
		testBox->SetPosition(glm::vec3(3.2f, -1.0f, 0.0f));*/


		m_gameObjects.push_back(TheSpy);

		m_gameObjects.push_back(Cabin1);
		m_gameObjects.push_back(Suspect1);

		m_gameObjects.push_back(Cabin21);
		m_gameObjects.push_back(Suspect2);

		m_gameObjects.push_back(Cabin22);
		m_gameObjects.push_back(Suspect3);

		m_gameObjects.push_back(Cabin3);
		m_gameObjects.push_back(Suspect4);

		m_gameObjects.push_back(Cabin4);
		m_gameObjects.push_back(Suspect5);

		m_gameObjects.push_back(RedCircle);

		m_gameObjects.push_back(Evidence);
		m_gameObjects.push_back(EvidenceButton);

		m_gameObjects.push_back(BombLocation);

		//m_gameObjects.push_back(testBox);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);

		m_gameObjects.push_back(RedUnderline);


		m_gameObjects.push_back(CaseNews);

		m_gameObjects.push_back(Ticket);

		m_gameObjects.push_back(JournalSleeve);


	}

	//--------------------- SUSPECT BUTTON FUNCTIONS -----------------------

	void setSpy1() {
		JournalData::GetInstance()->SetPlayerSpyChoice(SPY1);

		if (!RedCircle->getActiveStatus()) {RedCircle->setActiveStatus(true);}
		
		RedCircle->SetPosition(glm::vec3(1.15f, 1.55f, 0.0f));
	};

	void setSpy21() {
		JournalData::GetInstance()->SetPlayerSpyChoice(SPY21);
		if (!RedCircle->getActiveStatus()) { RedCircle->setActiveStatus(true); }
		RedCircle->SetPosition(glm::vec3(2.65f, 1.55f, 0.0f));
		
	};

	void setSpy22() {
		JournalData::GetInstance()->SetPlayerSpyChoice(SPY22);
		if (!RedCircle->getActiveStatus()) { RedCircle->setActiveStatus(true); }
		RedCircle->SetPosition(glm::vec3(4.15f, 1.55f, 0.0f));
	};

	void setSpy3() {
		JournalData::GetInstance()->SetPlayerSpyChoice(SPY3);
		if (!RedCircle->getActiveStatus()) { RedCircle->setActiveStatus(true); }
		RedCircle->SetPosition(glm::vec3(1.15f, 0.25f, 0.0f));
	};

	void setSpy4() {
		JournalData::GetInstance()->SetPlayerSpyChoice(SPY4);
		if (!RedCircle->getActiveStatus()) { RedCircle->setActiveStatus(true); }
		RedCircle->SetPosition(glm::vec3(2.65f, 0.25f, 0.0f));
	};

	////--------------------- BOMB LOCATION FUNCTIONS ------------------------

	void setLocationTownSquare() {
		JournalData::GetInstance()->SetPlayerBombLocation(TOWNSQUARE);
		if (!RedUnderline->getActiveStatus()) { RedUnderline->setActiveStatus(true); }
		RedUnderline->SetPosition(glm::vec3(1.4f, -2.45f, 0.0f));
		
	};

	void setLocationHolyChurch() {
		JournalData::GetInstance()->SetPlayerBombLocation(HOLYCHURCH);
		if (!RedUnderline->getActiveStatus()) { RedUnderline->setActiveStatus(true); }
		RedUnderline->SetPosition(glm::vec3(3.5f, -2.45f, 0.0f));
		
	};

	void setLocationCouncil() {
		JournalData::GetInstance()->SetPlayerBombLocation(COUNCIL);
		if (!RedUnderline->getActiveStatus()) { RedUnderline->setActiveStatus(true); }
		RedUnderline->SetPosition(glm::vec3(1.4f, -2.95f, 0.0f));
		
	};

	void setLocationSupremeCourt() {
		JournalData::GetInstance()->SetPlayerBombLocation(SUPREMECOURT);
		if (!RedUnderline->getActiveStatus()) { RedUnderline->setActiveStatus(true); }
		RedUnderline->SetPosition(glm::vec3(3.5f, -2.95f, 0.0f));
		
	};
	
	//------------------------EVIDENCE FUNCTIONS--------------------

	void updateEvidence() {

		JournalData::GetInstance()->incrementEvidence();

		EvidenceButton->SetButtonText(JournalData::GetInstance()->getEvidenceText());

	}


	virtual void Update(float dt, long frame) override {

		Page::Update(dt, frame);

		MainPageData main = JournalData::GetInstance()->GetMainPageData();

		if (main.player_Spy == SPY_EMPTY) {
			RedCircle->setActiveStatus(false);
		}	

		if (main.player_BombLocation == LOCATION_EMPTY) {
			RedUnderline->setActiveStatus(false);
		}
		

	}



private:

	UIObject* RedCircle;
	UIObject* RedUnderline;
	UIButtonEmpty* EvidenceButton;

};