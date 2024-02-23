#pragma once

#include "Page.h"

class CabinPage5 : public Page {

public:

	CabinPage5() :Page() {

		// LEFT PAGE
		GameObject* P1Picture = new RenderGameObject("P1Picture", "Assets/Images/Journal/PassengerPicture_Octavia.png");
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new RenderGameObject("PaperClip", "Assets/Images/Journal/PaperClip.png");
		PaperClip->SetScale(glm::vec3(0.51f, 0.92f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-3.75f, 3.31f, 0.0f));

		GameObject* InfoPaper = new RenderGameObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png");
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

		GameObject* CabinStamp = new RenderGameObject("CabinStamp", "Assets/Images/Journal/CabinStamp_4.png");
		CabinStamp->SetScale(glm::vec3(2.19f, 1.14f, 0.0f));
		CabinStamp->SetPosition(glm::vec3(-1.75f, -2.75f, 0.0f));


		// RIGHT PAGE
		// CLUES	[O = Octavia, C = Clue]
		Text* O_Clue1 = new Text("O_Clue1", "Opera singer", "Assets/Fonts/ESA-m.ttf");
		O_Clue1->SetPosition(glm::vec3(0.9f, 2.67f, 0.0f));
		O_Clue1->SetColor(glm::vec3(0, 0, 0));
		O_Clue1->SetScale(0.53f);

		Text* O_Clue2 = new Text("O_Clue2", "High cult missionary", "Assets/Fonts/ESA-m.ttf");
		O_Clue2->SetPosition(glm::vec3(0.95f, 2.1f, 0.0f));
		O_Clue2->SetColor(glm::vec3(0, 0, 0));
		O_Clue2->SetScale(0.54f);

		Text* O_Clue3 = new Text("O_Clue3", "Westside's Minister ex-wife", "Assets/Fonts/ESA-smb.ttf");
		O_Clue3->SetPosition(glm::vec3(2.5f, 2.65f, 0.0f));
		O_Clue3->SetColor(glm::vec3(0, 0, 0));
		O_Clue3->SetScale(0.58f);

		Text* O_Clue4_1 = new Text("O_Clue4_1", "Always travelling", "Assets/Fonts/ESA-m.ttf");
		O_Clue4_1->SetPosition(glm::vec3(3.45f, 2.1f, 0.0f));
		O_Clue4_1->SetColor(glm::vec3(0, 0, 0));
		O_Clue4_1->SetScale(0.5f);

		Text* O_Clue4_2 = new Text("O_Clue4_2", "between East and West", "Assets/Fonts/ESA-m.ttf");
		O_Clue4_2->SetPosition(glm::vec3(3.35f, 1.8f, 0.0f));
		O_Clue4_2->SetColor(glm::vec3(0, 0, 0));
		O_Clue4_2->SetScale(0.5f);

		Text* O_Clue5 = new Text("O_Clue5", "The cult obsessively dedicated to Westside", "Assets/Fonts/ESA-smb.ttf");
		O_Clue5->SetPosition(glm::vec3(0.92f, 1.37f, 0.0f));
		O_Clue5->SetColor(glm::vec3(0, 0, 0));
		O_Clue5->SetScale(0.58f);


		GameObject* Divider1 = new RenderGameObject("Divider1", "Assets/Images/Journal/Line_1.png");
		Divider1->SetScale(glm::vec3(4.71f, 0.15f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 1.0f, 0.0f));


		// LAST ACTIVITY	[O = Octavia, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.3f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* O_LA1 = new Text("O_LA1", "Spread the cult ideology", "Assets/Fonts/ESA-smb.ttf");
		O_LA1->SetPosition(glm::vec3(0.82f, -0.23f, 0.0f));
		O_LA1->SetColor(glm::vec3(0, 0, 0));
		O_LA1->SetScale(0.58f);

		Text* O_LA2 = new Text("O_LA2", "Met the devotees at Town Square", "Assets/Fonts/ESA-m.ttf");
		O_LA2->SetPosition(glm::vec3(2.2f, -0.66f, 0.0f));
		O_LA2->SetColor(glm::vec3(0, 0, 0));
		O_LA2->SetScale(0.52f);


		// DIVIDER 2
		GameObject* Divider2 = new RenderGameObject("Divider2", "Assets/Images/Journal/Line_2.png");
		Divider2->SetScale(glm::vec3(4.81f, 0.09f, 0.0f));
		Divider2->SetPosition(glm::vec3(3.2f, -1.0f, 0.0f));


		// LAST VISIT
		Text* LastVisit = new Text("LastVisit", "Last Visit", "Assets/Fonts/mvboli.ttf");
		LastVisit->SetPosition(glm::vec3(0.8f, -1.75f, 0.0f));
		LastVisit->SetColor(glm::vec3(0, 0, 0));
		LastVisit->SetScale(0.85f);

		Text* TownSquare = new Text("TownSquare", "Town Square", "Assets/Fonts/ESA-m.ttf");
		TownSquare->SetPosition(glm::vec3(0.8f, -2.25f, 0.0f));
		TownSquare->SetColor(glm::vec3(0, 0, 0));
		TownSquare->SetScale(0.6f);

		Text* TheHolyChurch = new Text("TheHolyChurch", "The Holy Church", "Assets/Fonts/ESA-m.ttf");
		TheHolyChurch->SetPosition(glm::vec3(2.9f, -2.25f, 0.0f));
		TheHolyChurch->SetColor(glm::vec3(0, 0, 0));
		TheHolyChurch->SetScale(0.6f);

		Text* TheCouncil = new Text("TheCouncil", "The Council", "Assets/Fonts/ESA-m.ttf");
		TheCouncil->SetPosition(glm::vec3(0.8f, -2.75f, 0.0f));
		TheCouncil->SetColor(glm::vec3(0, 0, 0));
		TheCouncil->SetScale(0.6f);

		Text* SupremeCourt = new Text("SupremeCourt", "Supreme Court", "Assets/Fonts/ESA-m.ttf");
		SupremeCourt->SetPosition(glm::vec3(2.9f, -2.75f, 0.0f));
		SupremeCourt->SetColor(glm::vec3(0, 0, 0));
		SupremeCourt->SetScale(0.6f);



		m_gameObjects.push_back(P1Picture);
		m_gameObjects.push_back(PaperClip);
		m_gameObjects.push_back(InfoPaper);

		m_gameObjects.push_back(Name);
		m_gameObjects.push_back(Age);
		m_gameObjects.push_back(Citizen);
		m_gameObjects.push_back(Occupation);
		m_gameObjects.push_back(CabinStamp);

		m_gameObjects.push_back(O_Clue1);
		m_gameObjects.push_back(O_Clue2);
		m_gameObjects.push_back(O_Clue3);
		m_gameObjects.push_back(O_Clue4_1);
		m_gameObjects.push_back(O_Clue4_2);
		m_gameObjects.push_back(O_Clue5);
		m_gameObjects.push_back(Divider1);


		m_gameObjects.push_back(LastActivity);
		m_gameObjects.push_back(O_LA1);
		m_gameObjects.push_back(O_LA2);

		m_gameObjects.push_back(Divider2);
		m_gameObjects.push_back(LastVisit);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);


	}



};