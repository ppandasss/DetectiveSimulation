#pragma once

#include "tinyxml2.h"
#include "../GameObjects/GameObject.h"
#include "../UI/UIButton.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct Dialogue {
   string id;
   string speakerName;
   vector<std::string> text;
};

class DialogueManager  {
public:
    DialogueManager(const string& name, UIButton* dialogueBox, const string& filePath)
        : currentDialogueIndex(0), currentLineIndex(0), currentDialogueButton(dialogueBox) {
        LoadDialogues(filePath);
        if (!dialogues.empty() && !dialogues[0].text.empty()) {
            currentDialogueButton->SetButtonText(dialogues[0].text[0]);
            currentDialogueButton->SetTextSize(0.55f); // Set text size if needed
        }
    }

    ~DialogueManager() {
		if (currentDialogueButton) {
            currentDialogueButton->Clear();
		}
	}


    void LoadDialogues(const string& filePath) {
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
               cout << "Loaded Dialogue: ID = " << dialogue.id << ", Speaker = " << dialogue.speakerName <<endl;
            }
        }
       cout << "Loaded " << dialogues.size() << " dialogues." <<endl;
    }

    void AddSpeakerIcon(const string& speakerCode, UIElement* icon) {
        speakerIcons[speakerCode] = icon;
    }

   string GetSpeakerCodeFromId(const string& id) {
        if (id.size() >= 2) {
            return id.substr(1, 1); // Assuming the speaker code is the second character in the ID
        }
        return ""; // Return empty string if the ID is too short
    }



    void SetDialoguePosition(float x, float y) {
        if (currentDialogueButton) {
            currentDialogueButton->SetTextPosition(glm::vec3(x, y, 0.0f));
        }
    }

   void SetDialogueBoxPosition(const glm::vec3& position) {
    if (currentDialogueButton) {
        currentDialogueButton->SetButtonPosition(position);
       
    }
}

void SetDialogueBoxScale(const glm::vec3& scale) {
    if (currentDialogueButton) {
        currentDialogueButton->SetButtonScale(scale);
       
    }
}


    void SetDialogueColor(const glm::vec3& color) {
        if (currentDialogueButton) {
            currentDialogueButton->SetTextColor(color);
        }
    }

    void SetDialogueScale(float scale) {
        if (currentDialogueButton) {
            currentDialogueButton->SetTextSize(scale);
        }
    }

    void Update(float dt, long frame) {
		
	}
    // Override Render method from GameObject
    void Render() {
        if (currentDialogueButton) {
            currentDialogueButton->Render();
        }

        string speakerCode = GetSpeakerCodeFromId(dialogues[currentDialogueIndex].id);
        if (speakerIcons.find(speakerCode) != speakerIcons.end()) {
            speakerIcons[speakerCode]->Render();
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
                currentDialogueButton->SetButtonText(dialogues[currentDialogueIndex].text[currentLineIndex]);
                string speakerCode = GetSpeakerCodeFromId(dialogues[currentDialogueIndex].id);
                std::cout << "Speaker Code: " << speakerCode << std::endl; // Print the speaker code for debugging
               cout << "Playing Dialogue ID: " << dialogues[currentDialogueIndex].id
                    << " - Text: " << dialogues[currentDialogueIndex].text[currentLineIndex] <<endl;
            }
            else {
               cerr << "Error: Invalid dialogue or line index!" <<endl;
            }
        }
        else {
           cout << "No more dialogues available." <<endl;
        }
    }

    



private:
   vector<Dialogue> dialogues;
    UIButton* currentDialogueButton;
    map<string, UIElement*> speakerIcons;
    size_t currentDialogueIndex;
    size_t currentLineIndex; // Added this line
   string fontPath;
};
