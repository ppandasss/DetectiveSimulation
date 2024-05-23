#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"

#include "../UI/UIButton.h"

#include "../Application.h"


class JournalEntry : public Scene {

public:

	JournalEntry() :audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3", 4.0f);
		audioManager.LoadSound("CaseCloseStamp", "Assets/Sounds/SFX_CaseCloseStamp.mp3", 1.0f);

		GameObject* EntrySceneBackground = new UIObject("EntrySceneBackground", "Assets/Images/Ending/EndingSelect_Background.png", true);
		EntrySceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EntrySceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		CloseCaseButton = new UIButton("CloseCaseButton", "Assets/Images/Ending/EndingSelect_StampCut.png", glm::vec3(-7.0f, -3.1f, 0.0f), glm::vec3(2.5f, 4.06f, 0.0f), true, false, "");
		CloseCaseButton->SetHoverTexture("Assets/Images/Ending/EndingSelect_StampBorCut.png");
		CloseCaseButton->SetOnClickAction([this]() { SubmitEvidence(); });

		Journal = new Book();


		m_gameObjects.push_back(EntrySceneBackground); 



	}


	void OnEnter() override {

		m_gameObjects.push_back(Journal);
		Journal->drawBook();

		m_gameObjects.push_back(CloseCaseButton);

		audioManager.PlaySound("cabinMusic", true);	
		JournalData::GetInstance()->SetBookState(true); //Lock book	

	}



	void SubmitEvidence() {
		std::cout << "Submit Evidence" << std::endl;
		audioManager.PlaySound("CaseCloseStamp");
		Application::Get().SetScene("EndingScene");
		return;
	}

	void OnExit() override{

		audioManager.StopSound("cabinMusic");

	}


private:

	AudioManager& audioManager;
	Book* Journal;
	UIButton* CloseCaseButton;

};


