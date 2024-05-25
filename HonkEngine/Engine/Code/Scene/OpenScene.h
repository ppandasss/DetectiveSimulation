#pragma once

#include "Scene.h"
#include <memory>
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
    bool isTransitioning = false;
    bool isFadingOut = false;
    float transitionProgress = 0.0f;
    const float transitionDuration = 0.5f;

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
        dialogueBox->SetTextSize(0.5f);
        dialogueManager = unique_ptr<DialogueManager>(new DialogueManager("OpenDialogue", dialogueBox, ""));
        dialogueManager->LoadDialogues("scene1", "Assets/Dialogue/Opening/OpenCutscene1.xml");
        dialogueManager->LoadDialogues("scene2", "Assets/Dialogue/Opening/OpenCutscene2.xml");
        dialogueManager->LoadDialogues("scene3", "Assets/Dialogue/Opening/OpenCutscene3.xml");
        dialogueManager->LoadDialogues("scene4", "Assets/Dialogue/Opening/OpenCutscene4.xml");

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
        ResetScene(); // Reset the scene state on entry
        transitionEffects->FadeIn(2.0f);
    }

    void OnExit() override {
        audioManager.StopSound("OpenSceneBGMusic");
    }

    void Update(float dt, long frame) override {
        Scene::Update(dt, frame);
        transitionEffects->Update(dt);

        if (isTransitioning) {
            transitionProgress += dt / transitionDuration;
            if (transitionProgress >= 1.0f) {
                transitionProgress = 1.0f;
                isTransitioning = false;
                scenes[currentSceneIndex]->setActiveStatus(true);
                dialogueManager->SetDialogueSet(dialogueKeys[currentSceneIndex]);
            }

            float prevY = glm::mix(0.0f, -10.8f, transitionProgress);
            float nextY = glm::mix(10.8f, 0.0f, transitionProgress);

            if (currentSceneIndex > 0) {
                scenes[currentSceneIndex - 1]->SetPosition(glm::vec3(0.0f, prevY, 0.0f));
            }
            scenes[currentSceneIndex]->SetPosition(glm::vec3(0.0f, nextY, 0.0f));
        }
        else if (!isFadingOut) { // Prevent actions during fade-out
            if (input.Get().GetKeyDown(GLFW_KEY_SPACE) || input.Get().GetMouseButtonDown(0)) {
                if (dialogueManager->IsDialogueFinished(dialogueKeys[currentSceneIndex])) {
                    if (currentSceneIndex + 1 < scenes.size()) {
                        StartSceneTransition(currentSceneIndex + 1);
                    }
                    else {
                        isFadingOut = true; // Set flag to true during fade-out
                        transitionEffects->FadeOut(2.0f, [this]() { Application::Get().SetScene("Hallway"); });
                    }
                }
                else {
                    dialogueManager->PlayNextDialogue();
                }
            }
        }

        dialogueManager->Update(dt, frame);
    }

    void Render() override {
        Scene::Render(); // Renders GameObjects
        dialogueManager->Render();
    }

    void ResetScene() {
        currentSceneIndex = 0;
        isTransitioning = false;
        isFadingOut = false;
        transitionProgress = 0.0f;
        ChangeScene(0);

        // Reset transition object
        transitionObject->setActiveStatus(true);
        transitionObject->SetAlpha(1.0f);  // Ensure it's initially opaque for fade-in

        // Reset dialogue manager state
        dialogueManager->Reset();  // Ensure this method resets the state of the dialogue manager
    }

private:
    void ChangeScene(int index) {
        for (auto& scene : scenes) {
            scene->setActiveStatus(false);
        }
        scenes[index]->setActiveStatus(true);
        dialogueManager->SetDialogueSet(dialogueKeys[index]);
    }

    void StartSceneTransition(int nextSceneIndex) {
        isTransitioning = true;
        transitionProgress = 0.0f;
        scenes[nextSceneIndex]->setActiveStatus(true);
        currentSceneIndex = nextSceneIndex;
    }
};
