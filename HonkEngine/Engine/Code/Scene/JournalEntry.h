#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"
#include "../Effects/TransitionEffects.h"
#include "../UI/UIElement.h"

#include "../UI/UIButton.h"

#include "../Application.h"


class JournalEntry : public Scene {

public:

	JournalEntry() :audioManager(AudioManager::GetInstance()) {

		audioManager.LoadSound("cabinMusic", "Assets/Sounds/Music/BGmusic_Cabin.mp3", Music, 4.0f);
		audioManager.LoadSound("CaseCloseStamp", "Assets/Sounds/SFX_CaseCloseStamp.mp3", SFX, 1.0f);

		GameObject* EntrySceneBackground = new UIObject("EntrySceneBackground", "Assets/Images/Ending/EndingSelect_Background.png", true);
		EntrySceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EntrySceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		CloseCaseButton = new UIButton("CloseCaseButton", "Assets/Images/Ending/EndingSelect_StampCut_Rotate.png", glm::vec3(9.0f, -3.2f, 0.0f), glm::vec3(3.63f, 4.71f, 0.0f), true, false, "");
		CloseCaseButton->SetHoverTexture("Assets/Images/Ending/EndingSelect_StampBorCut_Rotate.png");
		CloseCaseButton->SetOnClickAction([this]() { SubmitEvidence(); });


		transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
		transitionEffects = std::make_unique<TransitionEffects>(transitionObject);

		instructionText = new Text("instruction", "Submit your Final Case Summary", "Assets/Fonts/mvboli.ttf", true);
		instructionText->SetScale(0.7f);
		instructionText->SetPosition(glm::vec3(0.0f, 4.5f, 0.0f));
		instructionText->SetColor(glm::vec3(1, 1, 1));


		Journal = new Book();

		m_gameObjects.push_back(EntrySceneBackground);

		m_gameObjects.push_back(instructionText);
		

	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame);
		transitionEffects->Update(dt);

	}
	void OnEnter() override {

		JournalData::GetInstance()->ActivateLastScene();
		m_gameObjects.push_back(Journal);
		Journal->drawBook();
		m_gameObjects.push_back(CloseCaseButton);
		m_gameObjects.push_back(transitionObject);

		audioManager.PlaySound("cabinMusic", true);
		//JournalData::GetInstance()->SetBookState(true); //Lock book	


		transitionEffects->FadeIn(2.0f, [this]() {
			std::cout << "Fade in complete" << std::endl;
			});
		audioManager.StopSound("trainAmbience");
	}



	void SubmitEvidence() {
		std::cout << "Submit Evidence" << std::endl;
		audioManager.PlaySound("CaseCloseStamp");
		transitionEffects->FadeOut(2.0f, [this]() {
			std::cout << "Fade Out complete" << std::endl;
		Application::Get().SetScene("EndScene");
			});
		return;
	}

	void OnExit() override {

		audioManager.StopSound("cabinMusic");

	}


private:

	UIElement* transitionObject;
	std::unique_ptr<TransitionEffects> transitionEffects;
	AudioManager& audioManager;
	Book* Journal;
	Text* instructionText;
	UIButton* CloseCaseButton;

};