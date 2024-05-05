#pragma once

#include "tinyxml2.h"
#include "../GameObjects/GameObject.h"
#include "../UI/UIButton.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <optional>
#include "../GameObjects/JournalData.h"

using namespace std;

struct TempOrderData {
    std::string roomNumber;
    std::string teaOrder;
    std::string sandwichOrder;
    std::string pastryOrder;
};

<<<<<<< Updated upstream

struct ClueActivation {
    string clueID;
    string index;
=======
struct ClueInfo {
    Cabin clueID = CABIN_EMPTY; // Default to CABIN_EMPTY assuming it's defined in your enum
    int clueIndex = -1;
    bool isValid = false;
>>>>>>> Stashed changes
};


struct DialogueChoice {
    string text;
    string nextDialogueId;
    vector<string> clueIDs;  // Store as a vector of strings
    bool hasClue() const { return !clueIDs.empty(); }
};





struct Dialogue {
    string id;
    string speakerName;
    vector<string> text;
    vector<DialogueChoice> choices;
    string next;
    tinyxml2::XMLElement* orderElement = nullptr;
    bool hasOrderData = false;  // Add this line
    TempOrderData* tempOrderData = nullptr;
};

<<<<<<< Updated upstream
Cabin stringToCabin(const std::string& cabinString) {
    if (cabinString == "CABIN1") return CABIN1;
    else if (cabinString == "CABIN21") return CABIN21;
    else if (cabinString == "CABIN22") return CABIN22;
    else if (cabinString == "CABIN3") return CABIN3;
    else if (cabinString == "CABIN4") return CABIN4;
    else return CABIN_EMPTY; // Default or error case
}

int stringToInt(const std::string& str) {
	if(str == "0") return 0;
    if(str == "1") return 1;
    if(str == "2") return 2;
    if(str == "3") return 3;
    if(str == "4") return 4;
    if(str == "5") return 5;
    if(str == "6") return 6;
    if(str == "7") return 7;
    if(str == "8") return 8;
    if(str == "9") return 9;
    if(str == "10") return 10;
    if(str == "11") return 11;
    if(str == "12") return 12;
}

int safeStoi(const std::string& str, int defaultValue = 0) {
    try {
        return std::stoi(str);
    }
    catch (const std::exception& e) {  // Catching all standard exceptions
        std::cerr << "Exception converting string to int: " << e.what() << '\n';
        return defaultValue;
    }
}


=======
Cabin GetCabinFromString(const string& cabinStr) {
    static const map<string, Cabin> cabinMap = {
        {"CABIN1", CABIN1},
        {"CABIN21", CABIN21},
        {"CABIN22", CABIN22},
        {"CABIN3", CABIN3},
        {"CABIN4", CABIN4},
        {"CABIN_EMPTY", CABIN_EMPTY}
    };

    auto it = cabinMap.find(cabinStr);
    if (it != cabinMap.end()) {
        return it->second;
    }
    return CABIN_EMPTY;  // Default return if not found
}
>>>>>>> Stashed changes


class DialogueManager {
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
        for (auto& dialogue : dialogues) {
            delete dialogue.tempOrderData;
            dialogue.tempOrderData = nullptr; // Ensure pointer is set to nullptr after deletion
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

<<<<<<< Updated upstream
                        for(tinyxml2::XMLElement * choiceElement = choicesElement->FirstChildElement(); choiceElement != nullptr; choiceElement = choiceElement->NextSiblingElement()) {
                            DialogueChoice choice;
                            choice.text = choiceElement->GetText();
                            choice.nextDialogueId = choiceElement->Attribute("next");

                            // Parsing clue activations with safety
                            for (tinyxml2::XMLElement* clueElement = choiceElement->FirstChildElement("ClueActivation");
                                clueElement != nullptr;
                                clueElement = clueElement->NextSiblingElement("ClueActivation")) {

                                const char* clueID = clueElement->Attribute("clueID");
                                const char* indexStr = clueElement->Attribute("index");

                                if (clueID && indexStr) {  // Ensure both attributes are not null
                                    ClueActivation activation;
                                    activation.clueID = clueID;
                                    activation.index = safeStoi(indexStr);  // Convert index to integer safely
                                    choice.clueActivations.push_back(activation);
                                }
                            }
                            dialogue.choices.push_back(choice);

=======
                        const char* clueIDAttr = choiceElement->Attribute("clueID");
                        if (clueIDAttr) {
                            stringstream ss(clueIDAttr);
                            string clueID;
                            while (getline(ss, clueID, ',')) { 
                                choice.clueIDs.push_back(clueID);
                            }
>>>>>>> Stashed changes
                        }

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
                    dialogue.hasOrderData = true;

                    // Allocate memory for tempOrderData
                    dialogue.tempOrderData = new TempOrderData();

                    // Parse and store the order data
                    tinyxml2::XMLElement* roomNumberElement = orderElement->FirstChildElement("RoomNumber");
                    if (roomNumberElement) dialogue.tempOrderData->roomNumber = roomNumberElement->GetText();
                    tinyxml2::XMLElement* teaElement = orderElement->FirstChildElement("Tea");
                    if (teaElement) dialogue.tempOrderData->teaOrder = teaElement->GetText();
                    tinyxml2::XMLElement* sandwichElement = orderElement->FirstChildElement("Sandwich");
                    if (sandwichElement) dialogue.tempOrderData->sandwichOrder = sandwichElement->GetText();
                    tinyxml2::XMLElement* pastryElement = orderElement->FirstChildElement("Pastry");
                    if (pastryElement) dialogue.tempOrderData->pastryOrder = pastryElement->GetText();
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

    void HandleClue(const string& clueID) {
        size_t underscorePos = clueID.find('_');
        if (underscorePos != string::npos) {
            string cabinStr = clueID.substr(0, underscorePos);
            int clueIndex = stoi(clueID.substr(underscorePos + 1));

            Cabin cabinEnum = GetCabinFromString(cabinStr);
            if (cabinEnum != CABIN_EMPTY) {
                JournalData::GetInstance()->ActivateClue(cabinEnum, clueIndex);
                cout << "Clue activated: " << clueID << endl;
            }
            else {
                cout << "Invalid cabin ID: " << cabinStr << endl;
            }
        }
        else {
            cout << "Invalid clue ID format: " << clueID << endl;
        }
    }



    void HandleChoice(int choiceIndex) {
        if (choiceIndex >= 0 && choiceIndex < dialogues[currentDialogueIndex].choices.size()) {
            const auto& choice = dialogues[currentDialogueIndex].choices[choiceIndex];
<<<<<<< Updated upstream
            //Clue activation
            for (const auto& activation : choice.clueActivations) {
                int index = stringToInt(activation.index);
                JournalData::GetInstance()->ActivateClue(stringToCabin(activation.clueID),index);
=======
            std::cout << "Player has chosen: " << choice.text << std::endl; // Add this line to print the chosen choice
            
            if (choice.hasClue()) {
                for (const auto& clueID : choice.clueIDs) {
                    HandleClue(clueID);
                }
>>>>>>> Stashed changes
            }

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
                if (dialogues[currentDialogueIndex].hasOrderData) {
                    // Apply the order data
                    SetOrderDataForCurrentDialogue();
                }
                currentDialogueIndex = nextDialogueIndex;
                currentLineIndex = 0;
                choiceMade = false;
            }
            else {
                std::cout << "No more dialogues available." << std::endl;
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
        if (!currentDialogue.tempOrderData) {
            std::cerr << "Error: tempOrderData is null for dialogue index " << currentDialogueIndex << std::endl;
            return;
        }

        OrderData& orderData = OrderData::GetInstance();
        if (!currentDialogue.tempOrderData->roomNumber.empty()) {
            orderData.SetRoomNumber(currentDialogue.tempOrderData->roomNumber);
            std::cout << "Room Number set to: " << currentDialogue.tempOrderData->roomNumber << std::endl;
        }
        if (!currentDialogue.tempOrderData->teaOrder.empty()) {
            orderData.SetTeaOrder(currentDialogue.tempOrderData->teaOrder);
            std::cout << "Tea Order set to: " << currentDialogue.tempOrderData->teaOrder << std::endl;
        }
        if (!currentDialogue.tempOrderData->sandwichOrder.empty()) {
            orderData.SetSandwichOrder(currentDialogue.tempOrderData->sandwichOrder);
            std::cout << "Sandwich Order set to: " << currentDialogue.tempOrderData->sandwichOrder << std::endl;
        }
        if (!currentDialogue.tempOrderData->pastryOrder.empty()) {
            orderData.SetPastryOrder(currentDialogue.tempOrderData->pastryOrder);
            std::cout << "Pastry Order set to: " << currentDialogue.tempOrderData->pastryOrder << std::endl;
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