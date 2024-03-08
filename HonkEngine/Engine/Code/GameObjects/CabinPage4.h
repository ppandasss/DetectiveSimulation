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
		Text* A_Clue1_1 = new Text("A_Clue1_1", "Wealthy background", "Assets/Fonts/ESA-m.ttf");
		A_Clue1_1->SetPosition(glm::vec3(0.9f, 2.67f, 0.0f));
		A_Clue1_1->SetColor(glm::vec3(0, 0, 0));
		A_Clue1_1->SetScale(0.5f);

		Text* A_Clue1_2 = new Text("A_Clue1_2", "with large business", "Assets/Fonts/ESA-m.ttf");
		A_Clue1_2->SetPosition(glm::vec3(0.89f, 2.35f, 0.0f));
		A_Clue1_2->SetColor(glm::vec3(0, 0, 0));
		A_Clue1_2->SetScale(0.5f);

		Text* A_Clue2 = new Text("A_Clue2", "Messy attire?", "Assets/Fonts/ESA-smb.ttf");
		A_Clue2->SetPosition(glm::vec3(1.0f, 1.6f, 0.0f));
		A_Clue2->SetColor(glm::vec3(0, 0, 0));
		A_Clue2->SetScale(0.62f);

		Text* A_Clue3 = new Text("A_Clue3", "Expert in explosive", "Assets/Fonts/ESA-smb.ttf");
		A_Clue3->SetPosition(glm::vec3(3.2f, 2.65f, 0.0f));
		A_Clue3->SetColor(glm::vec3(0, 0, 0));
		A_Clue3->SetScale(0.6f);

		Text* A_Clue4 = new Text("A_Clue4", "Politic insider newspapers", "Assets/Fonts/ESA-m.ttf");
		A_Clue4->SetPosition(glm::vec3(3.2f, 2.17f, 0.0f));
		A_Clue4->SetColor(glm::vec3(0, 0, 0));
		A_Clue4->SetScale(0.53f);

		Text* A_Clue5_1 = new Text("A_Clue5_1", "Carrying a strange", "Assets/Fonts/ESA-smb.ttf");
		A_Clue5_1->SetPosition(glm::vec3(3.25f, 1.68f, 0.0f));
		A_Clue5_1->SetColor(glm::vec3(0, 0, 0));
		A_Clue5_1->SetScale(0.5f);

		Text* A_Clue5_2 = new Text("A_Clue5_2", "gadget with his luggage", "Assets/Fonts/ESA-smb.ttf");
		A_Clue5_2->SetPosition(glm::vec3(3.24f, 1.39f, 0.0f));
		A_Clue5_2->SetColor(glm::vec3(0, 0, 0));
		A_Clue5_2->SetScale(0.5f);

		GameObject* Divider1 = new UIObject("Divider1", "Assets/Images/Journal/Line_1.png", true);
		Divider1->SetScale(glm::vec3(4.71f, 0.15f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 1.0f, 0.0f));


		// LAST ACTIVITY	[A = Archibald, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.3f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		Text* A_LA1_1 = new Text("A_LA1_1", "Business meeting", "Assets/Fonts/ESA-smb.ttf");
		A_LA1_1->SetPosition(glm::vec3(0.82f, -0.23f, 0.0f));
		A_LA1_1->SetColor(glm::vec3(0, 0, 0));
		A_LA1_1->SetScale(0.58f);

		Text* A_LA1_2 = new Text("A_LA1_2", "with important clients", "Assets/Fonts/ESA-smb.ttf");
		A_LA1_2->SetPosition(glm::vec3(0.82f, -0.6f, 0.0f));
		A_LA1_2->SetColor(glm::vec3(0, 0, 0));
		A_LA1_2->SetScale(0.58f);

		Text* A_LA2 = new Text("A_LA2", "from Westside", "Assets/Fonts/ESA-m.ttf");
		A_LA2->SetPosition(glm::vec3(3.4f, -0.59f, 0.0f));
		A_LA2->SetColor(glm::vec3(0, 0, 0));
		A_LA2->SetScale(0.62f);


		// DIVIDER 2
		GameObject* Divider2 = new UIObject("Divider2", "Assets/Images/Journal/Line_2.png", true);
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

		/*m_gameObjects.push_back(A_Clue1_1);
		m_gameObjects.push_back(A_Clue1_2);
		m_gameObjects.push_back(A_Clue2);
		m_gameObjects.push_back(A_Clue3);
		m_gameObjects.push_back(A_Clue4);
		m_gameObjects.push_back(A_Clue5_1);
		m_gameObjects.push_back(A_Clue5_2);*/
		m_gameObjects.push_back(Divider1);


		m_gameObjects.push_back(LastActivity);
		/*m_gameObjects.push_back(A_LA1_1);
		m_gameObjects.push_back(A_LA1_2);
		m_gameObjects.push_back(A_LA2);*/

		m_gameObjects.push_back(Divider2);
		m_gameObjects.push_back(LastVisit);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);


	}



};