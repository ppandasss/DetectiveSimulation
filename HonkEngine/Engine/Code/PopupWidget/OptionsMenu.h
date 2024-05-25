#pragma once

#include "Interface.h"

#include "../UI/UISlider.h"


class OptionsMenu : public Interface {

public:

	OptionsMenu() : Interface("OptionsMenu") {

		UIButton* GreyBackground = new UIButton("GreyBackground", "Assets/Images/Interface/Grey_Background.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.2f, 10.8f, 0.0f), true, false, "");
		GreyBackground->SetOnClickAction([this]() { EmptyFunction(); });

		GameObject* OptionsBackground = new UIObject("OptionsBackground", "Assets/Images/Interface/Interface_Background_Options.png", true);
		OptionsBackground->SetScale(glm::vec3(14.36f, 8.24f, 0.0f));
		OptionsBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIButtonEmpty* BackButton = new UIButtonEmpty("BackButton", glm::vec3(4.0f, -3.5f, 0.0f), glm::vec3(1.5f, 3.0f, 0.0f), true, true, "Assets/Fonts/mvboli.ttf");
		BackButton->SetButtonText("Back");
		BackButton->SetOnClickAction([this]() { Hide(); });

		//VOLUME 

		Text* MasterVolumeText = new Text("MasterVolumeText", "Master Volume", "Assets/Fonts/mvboli.ttf", true);
		MasterVolumeText->SetPosition(glm::vec3(3.0f, 2.0f, 0.0f));
		MasterVolumeText->SetColor(glm::vec3(0, 0, 0));
		MasterVolumeText->SetScale(0.85f);

		MasterVolumeSlider = new UISlider("MasterVolumeSlider", "Assets/Images/Interface/Slider_Handle.png", glm::vec3(3.0f, 1.0f, 0.0f), glm::vec3(0.6f, 0.6f, 0.0f), true, MasterVolume);
		MasterVolumeSlider->SetOnValueChangedCallback([this](float value) {
			AudioManager::GetInstance().SetMasterVolume(value);
		});

		Text* SFXVolumeText = new Text("SFXVolumeText", "SFX Volume", "Assets/Fonts/mvboli.ttf", true);
		SFXVolumeText->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
		SFXVolumeText->SetColor(glm::vec3(0, 0, 0));
		SFXVolumeText->SetScale(0.85f);

		SFXVolumeSlider = new UISlider("SFXVolumeSlider", "Assets/Images/Interface/Slider_Handle.png", glm::vec3(3.0f, -1.0f, 0.0f), glm::vec3(0.6f, 0.6f, 0.0f), true, SFXVolume);
		SFXVolumeSlider->SetOnValueChangedCallback([this](float value) {
			AudioManager::GetInstance().SetSFXVolumeMultiplier(value);
		});

		Text* MusicVolumeText = new Text("MusicVolumeText", "Master Volume", "Assets/Fonts/mvboli.ttf", true);
		MusicVolumeText->SetPosition(glm::vec3(3.0f, -2.0f, 0.0f));
		MusicVolumeText->SetColor(glm::vec3(0, 0, 0));
		MusicVolumeText->SetScale(0.85f);

		MusicVolumeSlider = new UISlider("MusicVolumeSlider", "Assets/Images/Interface/Slider_Handle.png", glm::vec3(3.0f, -3.0f, 0.0f), glm::vec3(0.6f, 0.6f, 0.0f), true, MusicVolume);
		MusicVolumeSlider->SetOnValueChangedCallback([this](float value) {
			AudioManager::GetInstance().SetMusicVolumeMultiplier(value);
		});

		//SCREEN MODE

		Text* WindowMode = new Text("WindowModeText", "Window Mode", "Assets/Fonts/mvboli.ttf", true);
		WindowMode->SetPosition(glm::vec3(-3.0f, 2.0f, 0.0f));
		WindowMode->SetColor(glm::vec3(0, 0, 0));
		WindowMode->SetScale(0.85f);

		UIButton* FullScreenButton = new UIButton("FullScreenButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-3.0f, 1.0f, 0.0f), glm::vec3(2.78f, 0.66f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		FullScreenButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		FullScreenButton->SetButtonText("Full Screen Mode");
		FullScreenButton->SetOnClickAction([this]() { FullScreen(); });

		UIButton* WindowedButton = new UIButton("FullScreenButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(-3.0f, -0.5f, 0.0f), glm::vec3(2.78f, 0.66f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
		WindowedButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
		WindowedButton->SetButtonText("Windowed");
		WindowedButton->SetOnClickAction([this]() { Windowed(); });

		//PUSH BACK OBJECTS 

		m_gameObjects.push_back(GreyBackground);
		m_gameObjects.push_back(OptionsBackground);
		m_gameObjects.push_back(BackButton);

		m_gameObjects.push_back(MasterVolumeText);
		m_gameObjects.push_back(SFXVolumeText);
		m_gameObjects.push_back(MusicVolumeText);

		m_gameObjects.push_back(MasterVolumeSlider);
		m_gameObjects.push_back(SFXVolumeSlider);
		m_gameObjects.push_back(MusicVolumeSlider);

		m_gameObjects.push_back(WindowMode);
		m_gameObjects.push_back(FullScreenButton);
		m_gameObjects.push_back(WindowedButton);

	}

	void EmptyFunction() {
		return;
	}

	void Show() override {
		Interface::Show();
		MasterVolumeSlider->UpdateKnobPosition();
		SFXVolumeSlider->UpdateKnobPosition();
		MusicVolumeSlider->UpdateKnobPosition();
		
	}

	void FullScreen() {
		Application::Get().SetFullScreen();
		return;
	}

	void Windowed() {
		Application::Get().SetWindowedMode();
		return;
	}



protected:

	UISlider* MasterVolumeSlider;
	UISlider* SFXVolumeSlider;
	UISlider* MusicVolumeSlider;

};