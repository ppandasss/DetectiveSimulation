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
    std::vector<std::string> dialogueKeys = { "scene1", "scene2", "scene3", "scene4", "scene5", "scene6", "scene7", "scene8", "scene9", "scene10", "scene11", "scene12", "scene13" };
    UIElement* transitionObject;
    std::unique_ptr<TransitionEffects> transitionEffects;
    Text* instructionText;
    int currentSceneIndex = 0;
    bool isTransitioning = false;
    bool isFadingOut = false;
    float transitionProgress = 0.0f;
    const float transitionDuration = 0.5f;

public:

    OpenScene() :audioManager(AudioManager::GetInstance())
    {
        audioManager.LoadSound("OpenSceneBGMusic", "Assets/Sounds/Music/BGmusic_Cutscene.mp3", Music, 1.0f);
        audioManager.LoadSound("ProjectorSFX", "Assets/Sounds/SFX_Projector.mp3", SFX, 0.6f);

        // Load scenes
        GameObject* OpenScene1 = new UIObject("OpenScene1", "Assets/Images/Opening/Opening_Cutscene_1.jpg", true);
        OpenScene1->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene1));

        GameObject* OpenScene2 = new UIObject("OpenScene2", "Assets/Images/Opening/Opening_Cutscene_2.jpg", true);
        OpenScene2->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene2));

        GameObject* OpenScene3 = new UIObject("OpenScene3", "Assets/Images/Opening/Opening_Cutscene_3.jpg", true);
        OpenScene3->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene3));

        GameObject* OpenScene4 = new UIObject("OpenScene4", "Assets/Images/Opening/Opening_Cutscene_4.jpg", true);
        OpenScene4->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene4));

        GameObject* OpenScene5 = new UIObject("OpenScene5", "Assets/Images/Opening/Opening_Cutscene_5.jpg", true);
        OpenScene5->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene5));

        GameObject* OpenScene6 = new UIObject("OpenScene6", "Assets/Images/Opening/Opening_Cutscene_6.jpg", true);
        OpenScene6->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene6));

        GameObject* OpenScene7 = new UIObject("OpenScene7", "Assets/Images/Opening/Opening_Cutscene_7.jpg", true);
        OpenScene7->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene7));

        GameObject* OpenScene8 = new UIObject("OpenScene8", "Assets/Images/Opening/Opening_Cutscene_8.jpg", true);
        OpenScene8->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene8));

        GameObject* OpenScene9 = new UIObject("OpenScene9", "Assets/Images/Opening/Opening_Cutscene_9.jpg", true);
        OpenScene9->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene9));

        GameObject* OpenScene10 = new UIObject("OpenScene10", "Assets/Images/Opening/Opening_Cutscene_10.jpg", true);
        OpenScene10->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene10));

        GameObject* OpenScene11 = new UIObject("OpenScene11", "Assets/Images/Opening/Opening_Cutscene_11.jpg", true);
        OpenScene11->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene11));

        GameObject* OpenScene12 = new UIObject("OpenScene12", "Assets/Images/Opening/Opening_Cutscene_12.jpg", true);
        OpenScene12->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene12));

        GameObject* OpenScene13 = new UIObject("OpenScene13", "Assets/Images/Opening/Opening_Cutscene_13.jpg", true);
        OpenScene13->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
        scenes.push_back(static_cast<UIObject*>(OpenScene13));

        OpenScene1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        OpenScene2->SetPosition(glm::vec3(0.0f, 10.8f, 0.0f));
        OpenScene3->SetPosition(glm::vec3(0.0f, 21.6f, 0.0f));
        OpenScene4->SetPosition(glm::vec3(0.0f, 32.4f, 0.0f));
        OpenScene5->SetPosition(glm::vec3(0.0f, 43.2f, 0.0f));
        OpenScene6->SetPosition(glm::vec3(0.0f, 54.0f, 0.0f));
        OpenScene7->SetPosition(glm::vec3(0.0f, 64.8f, 0.0f));
        OpenScene8->SetPosition(glm::vec3(0.0f, 75.6f, 0.0f));
        OpenScene9->SetPosition(glm::vec3(0.0f, 86.4f, 0.0f));
        OpenScene10->SetPosition(glm::vec3(0.0f, 97.2f, 0.0f));
        OpenScene11->SetPosition(glm::vec3(0.0f, 108.0f, 0.0f));
        OpenScene12->SetPosition(glm::vec3(0.0f, 118.8f, 0.0f));
        OpenScene13->SetPosition(glm::vec3(0.0f, 129.6f, 0.0f));
   

        // Create dialogue manager
        UIButton* dialogueBox = new UIButton("DialogueBox", "", glm::vec3(0.0f, -4.5f, 0.0f), glm::vec3(10.96f, 2.05f, 0.0f), true, true, "Assets/Fonts/OverpassMono-SemiBold.ttf");
        dialogueBox->SetTextSize(0.55f);
        dialogueBox->SetTextColor(glm::vec3(1, 1, 1));

        dialogueManager = unique_ptr<DialogueManager>(new DialogueManager("OpenDialogue", dialogueBox, ""));
        dialogueManager->LoadDialogues("scene1", "Assets/Dialogue/Opening/OpenCutscene1.xml");
        dialogueManager->LoadDialogues("scene2", "Assets/Dialogue/Opening/OpenCutscene2.xml");
        dialogueManager->LoadDialogues("scene3", "Assets/Dialogue/Opening/OpenCutscene3.xml");
        dialogueManager->LoadDialogues("scene4", "Assets/Dialogue/Opening/OpenCutscene4.xml");
        dialogueManager->LoadDialogues("scene5", "Assets/Dialogue/Opening/OpenCutscene5.xml");
        dialogueManager->LoadDialogues("scene6", "Assets/Dialogue/Opening/OpenCutscene6.xml");
        dialogueManager->LoadDialogues("scene7", "Assets/Dialogue/Opening/OpenCutscene7.xml");
        dialogueManager->LoadDialogues("scene8", "Assets/Dialogue/Opening/OpenCutscene8.xml");
        dialogueManager->LoadDialogues("scene9", "Assets/Dialogue/Opening/OpenCutscene9.xml");
        dialogueManager->LoadDialogues("scene10", "Assets/Dialogue/Opening/OpenCutscene10.xml");
        dialogueManager->LoadDialogues("scene11", "Assets/Dialogue/Opening/OpenCutscene11.xml");
        dialogueManager->LoadDialogues("scene12", "Assets/Dialogue/Opening/OpenCutscene12.xml");
        dialogueManager->LoadDialogues("scene13", "Assets/Dialogue/Opening/OpenCutscene13.xml");

        instructionText = new Text("dialogueinstruction", "Use [Left-click] or [Space] to continue", "Assets/Fonts/mvboli.ttf", true);
        instructionText->SetScale(0.4f);
        instructionText->SetPosition(glm::vec3(7.0f, -5.0f, 0.0f));
        instructionText->SetColor(glm::vec3(1, 1, 1));

        transitionObject = new UINormal("Transition", "Assets/Images/black.png", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(25.0f, 20.0f, 0.0f), true);
        transitionEffects = std::unique_ptr<TransitionEffects>(new TransitionEffects(transitionObject));

        m_gameObjects.push_back(OpenScene1);
        m_gameObjects.push_back(OpenScene2);
        m_gameObjects.push_back(OpenScene3);
        m_gameObjects.push_back(OpenScene4);
        m_gameObjects.push_back(OpenScene5);
        m_gameObjects.push_back(OpenScene6);
        m_gameObjects.push_back(OpenScene7);
        m_gameObjects.push_back(OpenScene8);
        m_gameObjects.push_back(OpenScene9);
        m_gameObjects.push_back(OpenScene10);
        m_gameObjects.push_back(OpenScene11);
        m_gameObjects.push_back(OpenScene12);
        m_gameObjects.push_back(OpenScene13);
        m_gameObjects.push_back(dialogueBox);
        m_gameObjects.push_back(instructionText);
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
                if (instructionText->getActiveStatus())
                {
                   instructionText->setActiveStatus(false);
                }
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
        audioManager.PlaySound("ProjectorSFX");
    }
};
