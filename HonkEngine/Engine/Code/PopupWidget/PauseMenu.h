#pragma once

#include "Interface.h"
#include "OptionsMenu.h"
#include "ExitMenu.h"

class PauseMenu : public Interface {
public:
    PauseMenu() : Interface("PauseMenu"), shouldReopenPauseMenu(false), optionsMenu(new OptionsMenu()), exitConfirmation(new ExitMenu()) {
        UIButton* GreyBackground = new UIButton("GreyBackground2", "Assets/Images/Interface/Grey_Background.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(19.2f, 10.8f, 0.0f), true, false, "");
        GreyBackground->SetOnClickAction([this]() { EmptyFunction(); });

        GameObject* PauseBackground = new UIObject("ExitBackground", "Assets/Images/Interface/Interface_Background_PopUp.png", true);
        PauseBackground->SetScale(glm::vec3(8.0f, 8.0f, 0.0f));
        PauseBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        UIButton* ContinueButton = new UIButton("ContinueButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
        ContinueButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
        ContinueButton->SetButtonText("Continue Game");
        ContinueButton->SetOnClickAction([this]() { ClickContinue(); });

        UIButton* OptionsButton = new UIButton("OptionsButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
        OptionsButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
        OptionsButton->SetButtonText("Options");
        OptionsButton->SetOnClickAction([this]() { ShowOptions(); });

        UIButton* MainMenuButton = new UIButton("MainMenuButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
        MainMenuButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
        MainMenuButton->SetButtonText("Main Menu");
        MainMenuButton->SetOnClickAction([this]() { Application::Get().SetScene("MainMenu"); });

        UIButton* ExitGameButton = new UIButton("MainMenuButton", "Assets/Images/MainMenu/MainMenu_Button_Play.png", glm::vec3(0.0f, -2.5f, 0.0f), glm::vec3(2.78f, 0.86f, 0.0f), true, true, "Assets/Fonts/Jibril.ttf");
        ExitGameButton->SetHoverTexture("Assets/Images/MainMenu/MainMenu_Button_Start_Hover.png");
        ExitGameButton->SetButtonText("Exit Game");
        ExitGameButton->SetOnClickAction([this]() { ShowExitConfirmation(); });

        m_gameObjects.push_back(GreyBackground);
        m_gameObjects.push_back(PauseBackground);
        m_gameObjects.push_back(ContinueButton);
        m_gameObjects.push_back(OptionsButton);
        m_gameObjects.push_back(MainMenuButton);
        m_gameObjects.push_back(ExitGameButton);

    }

    void EmptyFunction() {
        return;
    }

    void ClickContinue() {
        Hide();
        shouldReopenPauseMenu = false;
    }

    void ShowOptions() {
        optionsMenu->Show();
        if (IsVisible()) {
            shouldReopenPauseMenu = true;
            Hide();
        }
    }

    void ShowExitConfirmation() {
        exitConfirmation->Show();
        if (IsVisible()) {
            shouldReopenPauseMenu = true;
            Hide();
        }
    }

    virtual void Render() override {
        Interface::Render();
        // Render other popups if needed
        if (optionsMenu->IsVisible()) {
            optionsMenu->Render();
        }
        if (exitConfirmation->IsVisible()) {
            exitConfirmation->Render();
        }
    }

    virtual void Update(float dt, long frame) override {
        Interface::Update(dt, frame);
        // Update other popups if needed
        if (optionsMenu->IsVisible()) {
            optionsMenu->Update(dt, frame);
        }
        if (exitConfirmation->IsVisible()) {
            exitConfirmation->Update(dt, frame);
        }

        // Reopen the pause menu if needed
        if (!optionsMenu->IsVisible() && !exitConfirmation->IsVisible() && shouldReopenPauseMenu) {
            Show();
            shouldReopenPauseMenu = false;
        }
    }

private:
    std::unique_ptr<OptionsMenu> optionsMenu;
    std::unique_ptr<ExitMenu> exitConfirmation;
    bool shouldReopenPauseMenu;
};