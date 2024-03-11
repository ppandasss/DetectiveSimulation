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
    std::vector<std::string> text;
};

class DialogueManager  {
public:
    DialogueManager(const std::string& name, const std::string& fontPath, const std::string& filePath)
        : currentDialogueIndex(0), currentLineIndex(0)
    {
        LoadDialogues(filePath);
        if (!dialogues.empty() && !dialogues[0].text.empty()) {
            currentText = std::make_shared<Text>("DialogueText", dialogues[0].text[0], fontPath, true);
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

                    // Store each line as a separate string in the vector
                    for (tinyxml2::XMLElement* lineElement = speakerElement->FirstChildElement(); lineElement != nullptr; lineElement = lineElement->NextSiblingElement()) {
                        dialogue.text.push_back(lineElement->GetText());
                    }
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
        if (currentDialogueIndex < dialogues.size()) {
            if (currentLineIndex + 1 < dialogues[currentDialogueIndex].text.size()) {
                currentLineIndex++;
            }
            else {
                currentDialogueIndex++;
                currentLineIndex = 0;
                if (currentDialogueIndex >= dialogues.size()) {
                    currentDialogueIndex = 0; // Reset to the first dialogue
                }
            }

            if (currentDialogueIndex < dialogues.size() && currentLineIndex < dialogues[currentDialogueIndex].text.size()) {
                currentText->SetContent(dialogues[currentDialogueIndex].text[currentLineIndex]);
                std::cout << "Playing Dialogue ID: " << dialogues[currentDialogueIndex].id
                    << " - Text: " << dialogues[currentDialogueIndex].text[currentLineIndex] << std::endl;
            }
            else {
                std::cerr << "Error: Invalid dialogue or line index!" << std::endl;
            }
        }
        else {
            std::cout << "No more dialogues available." << std::endl;
        }
    }





    std::shared_ptr<Text> GetCurrentText() {
        return currentText;
    }



private:
    std::vector<Dialogue> dialogues;
    std::shared_ptr<Text> currentText;
    size_t currentDialogueIndex;
    size_t currentLineIndex;  // Added this line
    std::string fontPath;
};
