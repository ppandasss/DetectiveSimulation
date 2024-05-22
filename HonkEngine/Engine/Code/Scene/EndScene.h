#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	
#include "../Text/Text.h"

#include "../Application.h"

#include "../GameObjects/JournalData.h"

class EndScene : public Scene {

public:

	EndScene() :audioManager(AudioManager::GetInstance())
	{

		audioManager.LoadSound("EndSceneBGMusic", "Assets/Sounds//Music/BGmusic_EndingCutscene.mp3",Music, 1.0f);
		audioManager.LoadSound("NewspaperSlam", "Assets/Sounds/SFX_EndingNewspaperSlam.mp3",SFX, 1.0f);

		GameObject* EndingSceneBackground = new UIObject("EndingSceneBackground", "Assets/Images/Ending/EndingSelect_Background.png", true);
		EndingSceneBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		EndingSceneBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		MissingPoster = new UIObject("MissingPoster", "Assets/Images/Ending/MissingPoster.png", true);
		MissingPoster->SetScale(glm::vec3(6.24f, 10.24f, 0.0f));
		MissingPoster->SetPosition(glm::vec3(-7.0f, -3.1f, 0.0f));

		Ending1 = new UIObject("Ending1", "Assets/Images/Ending/Ending1.png", true);
		Ending1->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending2 = new UIObject("Ending2", "Assets/Images/Ending/Ending1.png", true);
		Ending2->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending3 = new UIObject("Ending3", "Assets/Images/Ending/Ending1.png", true);
		Ending3->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending3->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending4 = new UIObject("Ending4", "Assets/Images/Ending/Ending1.png", true);
		Ending4->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending4->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending5 = new UIObject("Ending5", "Assets/Images/Ending/Ending1.png", true);
		Ending5->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending5->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Ending6 = new UIObject("Ending6", "Assets/Images/Ending/Ending1.png", true);
		Ending6->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		Ending6->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		Endings[END1] = Ending1;
		Endings[END2] = Ending2;
		Endings[END3] = Ending3;
		Endings[END4] = Ending4;
		Endings[END5] = Ending5;
		Endings[END6] = Ending6;

		m_gameObjects.push_back(EndingSceneBackground);
		m_gameObjects.push_back(MissingPoster);
		m_gameObjects.push_back(Ending1);
		m_gameObjects.push_back(Ending2);
		m_gameObjects.push_back(Ending3);
		m_gameObjects.push_back(Ending4);
		m_gameObjects.push_back(Ending5);
		m_gameObjects.push_back(Ending6);

	}

	void OnEnter() override {

		audioManager.PlaySound("NewspaperSlam");
		audioManager.PlaySound("EndSceneBGMusic", true);
		final_ending = journal_data->checkMainPageEntry();
		SetFinalScene(final_ending);
		currentTime = 0.0f;

	}


	void OnExit() override {

		audioManager.StopSound("EndSceneBGMusic");

	}

	void SetFinalScene(int ending) {

		for (int i = 0; i < 6; i++) {
			if (ending == i) {
				Endings[i]->setActiveStatus(true);
				ChosenEndingPoster = Endings[i];
				ChosenEndingPoster->SetScale(glm::vec3(14.36f * 1.8f, 8.24f * 1.8f, 0.0f)); // 180% of the original scale
			}
			else {
				Endings[i]->setActiveStatus(false);
			}
		}

		if (ending == END1 || ending == END6) {
			MissingPoster->setActiveStatus(true);
		}
		else {
			MissingPoster->setActiveStatus(false);
		}

	}

	void Update(float dt, long frame)
	{

		Scene::Update(dt, frame);


		if (ChosenEndingPoster && currentTime <= zoomInDuration) {

			currentTime += dt;
			float progress = currentTime / zoomInDuration;
			// Interpolating from 180% to 100%
			float targetScaleX = 25.848f - (11.488f * progress); // Decreasing from 25.848 to 14.36
			float targetScaleY = 14.832f - (6.592f * progress); // Decreasing from 14.832 to 8.24
			ChosenEndingPoster->SetScale(glm::vec3(targetScaleX, targetScaleY, 0.0f));
		}

		Input& input = Application::GetInput();

		if (input.Get().GetKey(GLFW_KEY_SPACE))
		{
			Application::Get().SetScene("MainMenu");
		}

		if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		{
			Application::Get().SetScene("MainMenu");
		}


	}


private:

	AudioManager& audioManager;

	JournalData* journal_data = JournalData::GetInstance();

	int final_ending;

	GameObject* Ending1;
	GameObject* Ending2;
	GameObject* Ending3;
	GameObject* Ending4;
	GameObject* Ending5;
	GameObject* Ending6;
	GameObject* MissingPoster;

	GameObject* Endings[6];

	GameObject* ChosenEndingPoster;

	float zoomInDuration = 0.5f;  // Duration for zoom in effect in seconds
	float currentTime = 0.0f;     // Current time elapsed

};