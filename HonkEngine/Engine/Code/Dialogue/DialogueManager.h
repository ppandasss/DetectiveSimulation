#pragma once

#include "tinyxml2.h"
#include "../GameObjects/GameObject.h"
#include "../Text/Text.h" 
#include <string>
#include <vector>
#include <memory>
#include <iostream>

struct Dialogue {
    std::string id;
    std::string speakerName;
    std::string text;
};

class DialogueManager  {
public:
    DialogueManager(const std::string& name, const std::string& fontPath, const std::string& filePath)
    {
        LoadDialogues(filePath);
        if (!dialogues.empty()) {
            // Initialize the Text object with the first dialogue
            currentText = std::make_shared<Text>("DialogueText", dialogues[currentDialogueIndex].text, fontPath);
        }
    }

    ~DialogueManager() {
		if (currentText) {
			currentText->Clear();
		}
	}


    void LoadDialogues(const std::string& filePath) {
        tinyxml2::XMLDocument doc;
        if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_SUCCESS) {
            tinyxml2::XMLElement* root = doc.FirstChildElement("Dialogues");
            for (tinyxml2::XMLElement* element = root->FirstChildElement("Dialogue"); element != nullptr; element = element->NextSiblingElement("Dialogue")) {
                Dialogue dialogue;
                dialogue.id = element->Attribute("id"); // Assuming ID is a string

                // Assuming there is only one speaker per dialogue for simplicity
                tinyxml2::XMLElement* speakerElement = element->FirstChildElement("Speaker");
                if (speakerElement) {
                    dialogue.speakerName = speakerElement->Attribute("name");

                    // Assuming you want to concatenate all lines into a single text for the dialogue
                    std::string fullText;
                    for (tinyxml2::XMLElement* lineElement = speakerElement->FirstChildElement(); lineElement != nullptr; lineElement = lineElement->NextSiblingElement()) {
                        if (fullText.length() > 0) fullText += " "; // Add space between lines
                        fullText += lineElement->GetText();
                    }
                    dialogue.text = fullText;
                }

                dialogues.push_back(dialogue);

                // Debug print ID and Speaker Name
                std::cout << "Loaded Dialogue: ID = " << dialogue.id << ", Speaker = " << dialogue.speakerName << std::endl;
            }
        }
        std::cout << "Loaded " << dialogues.size() << " dialogues." << std::endl;
    }

    void SetDialoguePosition(float x, float y) {
        if (currentText) {
            currentText->SetPosition(glm::vec3(x, y, 0.0f));
        }
    }

    void SetDialogueColor(const glm::vec3& color) {
        if (currentText) {
            currentText->SetColor(color);
        }
    }

    void SetDialogueScale(float scale) {
        if (currentText) {
            currentText->SetScale(scale);
        }
    }

    void Update(float dt, long frame) {
		
	}
    // Override Render method from GameObject
    void Render(){
        if (currentText) {
            currentText->Render();
        }
    }

    void PlayNextDialogue() {
        std::cout << "Loaded " << dialogues.size() << " dialogues." << std::endl;
        if (currentDialogueIndex >= 0 && currentDialogueIndex < dialogues.size()) {
            // Move to the next dialogue
            currentDialogueIndex++;

            // Loop back to the first dialogue if we've reached the end
            if (currentDialogueIndex >= dialogues.size()) {
                currentDialogueIndex = 0;
            }

            // Update the content of the current Text object
            currentText->SetContent(dialogues[currentDialogueIndex].text);
            std::cout << "Dialogue ID: " << dialogues[currentDialogueIndex].id << " - Text: " << dialogues[currentDialogueIndex].text << std::endl;
        }
    }

    std::shared_ptr<Text> GetCurrentText() {
        return currentText;
    }



private:
    std::vector<Dialogue> dialogues;
    std::shared_ptr<Text> currentText; // Single Text object for display
    size_t currentDialogueIndex = 0;
    std::string fontPath; // Path to the font used for dialogues
};
