#pragma once

#include "tinyxml2.h"
#include "../GameObjects/GameObject.h"
#include "../UI/UIButton.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../GameObjects/OrderData.h"

using namespace std;

struct DialogueChoice {
    string text;
    string nextDialogueId;
};

struct Dialogue {
    string id;
    string speakerName;
    vector<string> text;
    vector<DialogueChoice> choices;
    string next;
    tinyxml2::XMLElement* orderElement = nullptr;
};


class DialogueManager  {
public:
    DialogueManager(const string& name, UIButton* dialogueBox, const string& filePath, const string& defaultSprite)
        : currentDialogueIndex(0), currentLineIndex(0), currentDialogueButton(dialogueBox), choiceMade(false), defaultSpriteName(defaultSprite) {
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
                dialogue.id = element->Attribute("id");

                tinyxml2::XMLElement* speakerElement = element->FirstChildElement("Speaker");
                if (speakerElement) {
                    dialogue.speakerName = speakerElement->Attribute("name");
                    for (tinyxml2::XMLElement* lineElement = speakerElement->FirstChildElement(); lineElement != nullptr; lineElement = lineElement->NextSiblingElement()) {
                        dialogue.text.push_back(lineElement->GetText());
                    }
                }

                // Read choices
                tinyxml2::XMLElement* choicesElement = element->FirstChildElement("Choices");
                if (choicesElement) {
                    for (tinyxml2::XMLElement* choiceElement = choicesElement->FirstChildElement(); choiceElement != nullptr; choiceElement = choiceElement->NextSiblingElement()) {
                        DialogueChoice choice;
                        choice.text = choiceElement->GetText();
                        choice.nextDialogueId = choiceElement->Attribute("next");
                        dialogue.choices.push_back(choice);
                    }
                }

                // Read next attribute
                const char* nextAttr = element->Attribute("next");
                if (nextAttr) {
                    dialogue.next = nextAttr;
                }

                // Read order data
                tinyxml2::XMLElement* orderElement = element->FirstChildElement("Order");
                if (orderElement) {
                    dialogue.orderElement = orderElement;
                }

                dialogues.push_back(dialogue);
            }
        }
    }



    void AddSpeakerIcon(const string& speakerCode, UIElement* icon) {
        speakerIcons[speakerCode] = icon;
    }

    void AddSpeakerSprite(const string& speakerCode, UIElement* sprite) {
        speakerSprites[speakerCode] = sprite;
        // Activate the sprite if its name matches the default sprite name
        if (speakerCode == defaultSpriteName) {
            speakerSprites[speakerCode]->setActiveStatus(true);
        }
        else {
            speakerSprites[speakerCode]->setActiveStatus(false);
        }
    }

    void HandleChoice(int choiceIndex) {
        if (choiceIndex >= 0 && choiceIndex < dialogues[currentDialogueIndex].choices.size()) {
            const auto& choice = dialogues[currentDialogueIndex].choices[choiceIndex];
            std::cout << "Player has chosen: " << choice.text << std::endl; // Add this line to print the chosen choice
            // Find the dialogue with the corresponding nextDialogueId
            auto it = std::find_if(dialogues.begin(), dialogues.end(), [&](const Dialogue& d) {
                return d.id == choice.nextDialogueId;
                });
            if (it != dialogues.end()) {
                currentDialogueIndex = std::distance(dialogues.begin(), it);
                currentLineIndex = 0; // Start from the first line of the next dialogue
                // Update the dialogue button text
                currentDialogueButton->SetButtonText(dialogues[currentDialogueIndex].text[currentLineIndex]);
                HideChoices(); // Hide choices for the next dialogue
                choiceMade = true;
            }
        }
    }

    void AddChoiceButton(UIButton* choiceButton) {
        int choiceIndex = choiceButtons.size(); // Get the index for the new choice button
        choiceButtons.push_back(choiceButton);
        choiceButton->SetOnClickAction([this, choiceIndex]() {
            HandleChoice(choiceIndex); // Set the OnClick action to handle the choice
            });
        HideChoices(); // Hide the choices initially
    }

    bool IsCurrentDialogueQuestion() {
        return !dialogues[currentDialogueIndex].id.empty() && dialogues[currentDialogueIndex].id[2] == 'Q';
    }


   string GetSpeakerCodeFromId(const string& id) {
        if (id.size() >= 2) {
            return id.substr(1, 1); // Assuming the speaker code is the second character in the ID
        }
        return ""; // Return empty string if the ID is too short
    }

   void DisplayChoices() {
       choiceMade = false;
       std::cout << "Displaying choices for dialogue " << dialogues[currentDialogueIndex].id << std::endl;

       if (IsCurrentDialogueQuestion()) {
           std::cout << "It's a question dialogue." << std::endl;
           for (size_t i = 0; i < choiceButtons.size() && i < dialogues[currentDialogueIndex].choices.size(); ++i) {
               std::cout << "Choice " << i << ": " << dialogues[currentDialogueIndex].choices[i].text << std::endl;
               choiceButtons[i]->SetButtonText(dialogues[currentDialogueIndex].choices[i].text);
               choiceButtons[i]->setActiveStatus(true); // Set the button to active
               std::cout << "Setting choice button " << i << " to active." << std::endl;
           }
       }
       else {
           std::cout << "It's not a question dialogue." << std::endl;
       }
   }

   void HideChoices() {
       //std::cout << "Hiding choices for dialogue " << dialogues[currentDialogueIndex].id << std::endl;
       for (size_t i = 0; i < choiceButtons.size(); ++i) {
           choiceButtons[i]->setActiveStatus(false); // Set the button to inactive
          //std::cout << "Setting choice button " << i << " to inactive." << std::endl;
       }
   }

    void Update(float dt, long frame) {
        UpdateSpeakerSprite();
	}

    void Render() {
        if (currentDialogueButton) {
            currentDialogueButton->Render();
        } 

        // Get the speaker code for the current dialogue
        string speakerCode = GetSpeakerCodeFromId(dialogues[currentDialogueIndex].id);

        // Render speaker icons
        if (speakerIcons.find(speakerCode) != speakerIcons.end()) {
            speakerIcons[speakerCode]->Render();
        }
    }


    bool IsConsequenceDialogue(size_t index) {
        // A dialogue is considered a consequence if it's the 'next' dialogue of any choice in the previous dialogues
        for (size_t i = 0; i < index; i++) {
            for (const auto& choice : dialogues[i].choices) {
                if (choice.nextDialogueId == dialogues[index].id) {
                    return true;
                }
            }
        }
        return false;
    }

    void PlayNextDialogue() {
        // Check if the current dialogue is a question and if a choice has been made
        if (IsCurrentDialogueQuestion() && !choiceMade) {
            std::cout << "Please make a choice before continuing." << std::endl;
            return; // Do not advance to the next dialogue
        }

        // Advance to the next line or dialogue
        if (currentLineIndex + 1 < dialogues[currentDialogueIndex].text.size()) {
            currentLineIndex++;
        }
        else {
            // Find the next dialogue based on the 'next' attribute or skip to the next non-consequence dialogue
            size_t nextDialogueIndex = currentDialogueIndex + 1;
            if (!dialogues[currentDialogueIndex].next.empty()) {
                auto it = std::find_if(dialogues.begin(), dialogues.end(), [&](const Dialogue& d) {
                    return d.id == dialogues[currentDialogueIndex].next;
                    });
                if (it != dialogues.end()) {
                    nextDialogueIndex = std::distance(dialogues.begin(), it);
                }
            }
            else {
                while (nextDialogueIndex < dialogues.size() && IsConsequenceDialogue(nextDialogueIndex)) {
                    nextDialogueIndex++;
                }
            }

            if (nextDialogueIndex < dialogues.size()) {
                currentDialogueIndex = nextDialogueIndex;
                currentLineIndex = 0;
                choiceMade = false;
            }
            else {
                std::cout << "No more dialogues available." << std::endl;
                SetOrderDataForCurrentDialogue();
                return;
            }
        }

        // Update the dialogue button text
        if (currentDialogueIndex < dialogues.size() && currentLineIndex < dialogues[currentDialogueIndex].text.size()) {
            std::cout << "Playing dialogue: " << dialogues[currentDialogueIndex].id << std::endl;
            currentDialogueButton->SetButtonText(dialogues[currentDialogueIndex].text[currentLineIndex]);

            // Display choices if the current dialogue is a question
            if (IsCurrentDialogueQuestion()) {
                DisplayChoices();
            }
        }
        else {
            std::cerr << "Error: Invalid dialogue or line index!" << std::endl;
        }
    }

    bool IsDialogueFinished() const {
        return currentDialogueIndex + 1 >= dialogues.size();
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

    void SetDialogueScale(float scale) {
        if (currentDialogueButton) {
            currentDialogueButton->SetTextSize(scale);
        }
    }

    void SetChoicePosition(float x, float y) {
        for (auto& choiceButton : choiceButtons) {
            if (choiceButton) {
                choiceButton->SetTextPosition(glm::vec3(x, y, 0.0f));
            }
        }
    }

    void SetChoiceScale(float scale) {
        for (auto& choiceButton : choiceButtons) {
            if (choiceButton) {
                choiceButton->SetTextSize(scale);
            }
        }
    }

    void SetOrderDataForCurrentDialogue() {
        const Dialogue& currentDialogue = dialogues[currentDialogueIndex];
        tinyxml2::XMLElement* orderElement = currentDialogue.orderElement;
        if (orderElement) {
            OrderData& orderData = OrderData::GetInstance();
            tinyxml2::XMLElement* roomNumberElement = orderElement->FirstChildElement("RoomNumber");
            tinyxml2::XMLElement* teaElement = orderElement->FirstChildElement("Tea");
            tinyxml2::XMLElement* sandwichElement = orderElement->FirstChildElement("Sandwich");
            tinyxml2::XMLElement* pastryElement = orderElement->FirstChildElement("Pastry");
            if (roomNumberElement) {
                std::string roomNumber = roomNumberElement->GetText();
                orderData.SetRoomNumber(roomNumber);
                std::cout << "Room Number: " << roomNumber << std::endl;
            }
            if (teaElement) {
                std::string teaOrder = teaElement->GetText();
                orderData.SetTeaOrder(teaOrder);
                std::cout << "Tea Order: " << teaOrder << std::endl;
            }
            if (sandwichElement) {
                std::string sandwichOrder = sandwichElement->GetText();
                orderData.SetSandwichOrder(sandwichOrder);
                std::cout << "Sandwich Order: " << sandwichOrder << std::endl;
            }
            if (pastryElement) {
                std::string pastryOrder = pastryElement->GetText();
                orderData.SetPastryOrder(pastryOrder);
                std::cout << "Pastry Order: " << pastryOrder << std::endl;
            }
        }
    }




   private:
   

       void UpdateSpeakerSprite() {
           string speakerName = dialogues[currentDialogueIndex].speakerName;
           string speakerCode = GetSpeakerCodeFromId(dialogues[currentDialogueIndex].id);

           // If the speaker code is "W", keep the previous sprite active
           if (speakerCode == "W") {
               return;
           }

           // Deactivate all sprites
           for (auto& pair : speakerSprites) {
               pair.second->setActiveStatus(false);
           }

           // Activate the sprite for the current speaker
           if (speakerSprites.find(speakerName) != speakerSprites.end()) {
               speakerSprites[speakerName]->setActiveStatus(true);
           }
       }

       string defaultSpriteName;
       vector<Dialogue> dialogues;
       UIButton* currentDialogueButton;
       map<string, UIElement*> speakerIcons;
       map<string, UIElement*> speakerSprites;
       vector<UIButton*> choiceButtons;
       bool choiceMade;
       size_t currentDialogueIndex;
       size_t currentLineIndex;
       string fontPath;

};
