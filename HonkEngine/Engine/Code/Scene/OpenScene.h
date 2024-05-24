#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include "../GameObjects/AnimateGameObject.h"
#include "../Dialogue/Dialoguemanager.h"
#include "../Text/Text.h"
#include "../UI/UIElement.h"
#include "../Application.h"

class OpenScene : public Scene {

private:
    Input& input = Application::GetInput();
    unique_ptr<DialogueManager> dialogueManager;
    AudioManager& audioManager;
    std::vector<UIObject*> scenes;
    std::vector<std::string> dialogueKeys = { "scene1", "scene2", "scene3", "scene4" };
    UIElement* transitionObject;
    std::unique_ptr<TransitionEffects> transitionEffects;
    int currentSceneIndex = 0;

public:

    OpenScene() :audioManager(AudioManager::GetInstance())
    {
        audioManager.LoadSound("OpenSceneBGMusic", "Assets/Sounds/Music/BGmusic_Cutscene.mp3", Music, 1.0f);

        // Load scenes
        GameObject* OpenScene1 = new UIObject("OpenScene1", "Assets/Images/Ending/EndingSelect_Background.png", true);
        OpenScene1->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene1));

        GameObject* OpenScene2 = new UIObject("OpenScene2", "Assets/Images/Ending/EndingSelect_Background.png", true);
        OpenScene2->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene2));

        GameObject* OpenScene3 = new UIObject("OpenScene3", "Assets/Images/Ending/EndingSelect_Background.png", true);
        OpenScene3->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene3));

        GameObject* OpenScene4 = new UIObject("OpenScene4", "Assets/Images/Ending/EndingSelect_Background.png", true);
        OpenScene4->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene4));

        // Create dialogue manager
        UIButton* dialogueBox = new UIButton("DialogueBox", "", glm::vec3(0.0f, 3.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f), true, true, "Assets/Fonts/OverpassMono.ttf");
        dialogueManager = unique_ptr<DialogueManager>(new DialogueManager("OpenDialogue", dialogueBox, ""));
        dialogueManager->LoadDialogues("scene1", "Assets/Dialogue/Opening/Scene1.xml");
        dialogueManager->LoadDialogues("scene2", "Assets/Dialogue/Opening/Scene2.xml");
        dialogueManager->LoadDialogues("scene3", "Assets/Dialogue/Opening/Scene3.xml");
        dialogueManager->LoadDialogues("scene4", "Assets/Dialogue/Opening/Scene4.xml");

        transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
        transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));
        
        m_gameObjects.push_back(OpenScene1);
        m_gameObjects.push_back(OpenScene2);
        m_gameObjects.push_back(OpenScene3);
        m_gameObjects.push_back(OpenScene4);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(transitionObject);
    }

    void OnEnter() override {
        audioManager.PlaySound("OpenSceneBGMusic", true);
        transitionEffects->FadeIn(2.0f);
        ChangeScene(0); // Start with the first scene
    }

    void OnExit() override {
        audioManager.StopSound("OpenSceneBGMusic");
    }

    void Update(float dt, long frame) override {
        Scene::Update(dt, frame);
        transitionEffects->Update(dt);
        if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {
            if (dialogueManager->IsDialogueFinished(dialogueKeys[currentSceneIndex])) {
                currentSceneIndex++;
                if (currentSceneIndex < scenes.size()) {
                    ChangeScene(currentSceneIndex);
                }
                else {
                    transitionEffects->FadeOut(2.0f, [this]() { Application::Get().SetScene("Hallway"); });
                }
            }
            else {
                dialogueManager->PlayNextDialogue();
            }
        }

        dialogueManager->Update(dt, frame);
    }

    void Render() override {
        Scene::Render(); // Renders GameObjects
        dialogueManager->Render();
    }

private:
    void ChangeScene(int index) {
        for (auto& scene : scenes) {
            scene->setActiveStatus(false);
        }
        scenes[index]->setActiveStatus(true);
        dialogueManager->SetDialogueSet(dialogueKeys[index]);
    }
};
