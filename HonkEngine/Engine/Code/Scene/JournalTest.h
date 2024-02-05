#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../UI/UIElement.h"
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../GameObjects/Book.h"

class JournalRoom : public Scene
{
public:

	JournalRoom()
	{

		//RenderGameObject* room = new RenderGameObject("cabin1", "Assets/Images/passenger_room1.png", glm::vec3(0.0f, 0.0f, 0.0f));
		//room->SetScale(glm::vec3(20.0f, 12.0f, 0.0f));

		//UIElement* JournalButtonTest = new UIButton("JournalButtonTest", "Assets/Images/JournalButton.png", glm::vec3(-6.5f, -3.5f, 0.0f), glm::vec3(2.5f, 2.5f, 0.0f));

		//m_gameObjects.push_back(JournalButtonTest);

		//DRAWING JOURNAL JUST TO GET DIMENSIONS RIGHT

		GameObject* JournalCover = new RenderGameObject("JournalCover", "Assets/Images/Journal_Cover.png");
		JournalCover->SetScale(glm::vec3(14.0f, 10.0f, 0.0f));
		JournalCover->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		m_gameObjects.push_back(JournalCover);

		UIButton* Tab1 = new UIButton("Tab1", "Assets/Images/Journal_Bookmark_CaseSummary.png", glm::vec3(6.8f, 3.8f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab2 = new UIButton("Tab2", "Assets/Images/Journal_Bookmark_Passenger1.png", glm::vec3(6.8f, 2.6f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab3 = new UIButton("Tab3", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 1.4f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab4 = new UIButton("Tab4", "Assets/Images/Journal_Bookmark_Passenger2.png", glm::vec3(6.8f, 0.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab5 = new UIButton("Tab5", "Assets/Images/Journal_Bookmark_Passenger 3.png", glm::vec3(6.8f, -1.0f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));
		UIButton* Tab6 = new UIButton("Tab6", "Assets/Images/Journal_Bookmark_Passenger 4.png", glm::vec3(6.8f, -2.2f, 0.0f), glm::vec3(2.3f, 1.0f, 0.0f));

		m_gameObjects.push_back(Tab1);
		m_gameObjects.push_back(Tab2);
		m_gameObjects.push_back(Tab3);
		m_gameObjects.push_back(Tab4);
		m_gameObjects.push_back(Tab5);
		m_gameObjects.push_back(Tab6);

		GameObject* BlankPage = new RenderGameObject("BlankPage", "Assets/Images/Journal_BlankPage.png");
		BlankPage->SetScale(glm::vec3(13.0f, 9.0f, 0.0f));
		BlankPage->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		m_gameObjects.push_back(BlankPage);

		GameObject* JournalSleeve = new RenderGameObject("JounalSleeve", "Assets/Images/Journal_CaseSummary_Sleeve.png");
		JournalSleeve->SetScale(glm::vec3(3.5f, 9.7f, 0.0f));
		JournalSleeve->SetPosition(glm::vec3(-5.3f, 0.0f, 0.0f));

		m_gameObjects.push_back(JournalSleeve);

		Text* TheSpy = new Text("TheSpy", " The Spy", "Assets/Fonts/WD.ttf");
		TheSpy->SetPosition(glm::vec3(0.5f, 3.5f, 0.0f));
		TheSpy->SetColor(glm::vec3(0, 0, 0));
		TheSpy->SetScale(1.0f);

		m_gameObjects.push_back(TheSpy);

		//SPY BUTTONS

		UIButton* Suspect1 = new UIButton("Suspect1", "Assets/Images/Journal_CaseSummary_Icon_Archibald.png", glm::vec3(1.2f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin1 = new Text("Cabin1", "Cabin 1", "Assets/Fonts/WD.ttf");
		Cabin1->SetPosition(glm::vec3(0.7f, 1.1f, 0.0f));
		Cabin1->SetColor(glm::vec3(0, 0, 0));
		Cabin1->SetScale(0.6f);

		m_gameObjects.push_back(Suspect1);
		m_gameObjects.push_back(Cabin1);

		UIButton* Suspect2 = new UIButton("Suspect2", "Assets/Images/Journal_CaseSummary_Icon_Evelyn.png", glm::vec3(3.0f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin21 = new Text("Cabin21", "Cabin 2/1", "Assets/Fonts/WD.ttf");
		Cabin21->SetPosition(glm::vec3(2.3f, 1.1f, 0.0f));
		Cabin21->SetColor(glm::vec3(0, 0, 0));
		Cabin21->SetScale(0.6f);

		m_gameObjects.push_back(Suspect2);
		m_gameObjects.push_back(Cabin21);

		UIButton* Suspect3 = new UIButton("Suspect3", "Assets/Images/Journal_CaseSummary_Icon_Martha.png", glm::vec3(4.8f, 2.3f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin22 = new Text("Cabin22", "Cabin 2/2", "Assets/Fonts/WD.ttf");
		Cabin22->SetPosition(glm::vec3(4.2f, 1.1f, 0.0f));
		Cabin22->SetColor(glm::vec3(0, 0, 0));
		Cabin22->SetScale(0.6f);

		m_gameObjects.push_back(Suspect3);
		m_gameObjects.push_back(Cabin22);

		UIButton* Suspect4 = new UIButton("Suspect4", "Assets/Images/Journal_CaseSummary_Icon_Nathaniel.png", glm::vec3(1.2f, 0.0f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin3 = new Text("Cabin3", "Cabin 3", "Assets/Fonts/WD.ttf");
		Cabin3->SetPosition(glm::vec3(0.7f, -1.2f, 0.0f));
		Cabin3->SetColor(glm::vec3(0, 0, 0));
		Cabin3->SetScale(0.6f);

		m_gameObjects.push_back(Suspect4);
		m_gameObjects.push_back(Cabin3);

		UIButton* Suspect5 = new UIButton("Suspect5", "Assets/Images/Journal_CaseSummary_Icon_Octavia.png", glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.2f, 1.2f, 0.0f));

		Text* Cabin4 = new Text("Cabin4", "Cabin 4", "Assets/Fonts/WD.ttf");
		Cabin4->SetPosition(glm::vec3(2.3f, -1.2, 0.0f));
		Cabin4->SetColor(glm::vec3(0, 0, 0));
		Cabin4->SetScale(0.6f);

		m_gameObjects.push_back(Suspect5);
		m_gameObjects.push_back(Cabin4);

		//Suspect1->setActiveStatus(false);


	}

	void Update(float dt, long frame) {

		Scene::Update(dt, frame); // Call the base class update


		if (input.Get().GetKeyDown(GLFW_KEY_J))
		{

			std::cout << "Journal Button Test Room" << std::endl;
			Application::Get().SetScene("Hallway");

		}
	}

	Input& input = Application::GetInput();
};