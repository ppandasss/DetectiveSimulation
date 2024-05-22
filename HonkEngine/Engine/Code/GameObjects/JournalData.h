#pragma once

#include "../Text/Text.h"

#include "../UI/UIButtonEmpty.h"

using namespace std;

enum Location { TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT, LOCATION_EMPTY };

//used for clues and character data

enum Cabin { CABIN1, CABIN21, CABIN22, CABIN3, CABIN4, CABIN_EMPTY };

enum Ending { END1, END2, END3, END4, END5, END6 };


struct ClueData {

	bool showClue;
	GameObject* clueObject = nullptr;
	bool isEvidence = false;

};

struct DeferredRenderObject {

	bool showObject;
	GameObject* gameObj;
};


struct MainPageData {

	Cabin player_Spy = CABIN_EMPTY;
	Location player_BombLocation = LOCATION_EMPTY;
	int player_Evidence = 0;

};

struct CabinPageData {

	std::vector<ClueData*> textClues;
	std::vector<std::string> activeEvidence;
};

//SINGLETON CLASS

class JournalData {

public:

	static JournalData* GetInstance() {

		if (instance == nullptr) {
			instance = new JournalData();
		}
		return instance;
	}

	//------------------MAIN PAGE FUNCTIONS--------------------------


	void incrementEvidence() {
		//Increment index and wrap around if needed

		//std::cout << "INCREMENT CALLED" << std::endl;
		no_of_Evidence = allCabinData[main_page.player_Spy].activeEvidence.size();

		if (no_of_Evidence == 2) {
			//std::cout << "INDEX INCREMENTED" << std::endl;
			main_page.player_Evidence = (main_page.player_Evidence + 1) % 2;
			//std::cout << main_page.player_Evidence << std::endl;

		}

	}

	void setCurrentEvidencetext(UIButtonEmpty* evidenceButton) {

		if (no_of_Evidence == 0) {
			evidenceButton->SetButtonText("EMPTY");
			return;
		}

		if (no_of_Evidence == 1) {
			evidenceButton->SetButtonText(mainPageEvidence[0]);
		}

		else {
			evidenceButton->SetButtonText(mainPageEvidence[main_page.player_Evidence]);
		}

	}

	//SER PLAYER CHOICES

	void SetPlayerSpyChoice(Cabin spyChoice) {

		main_page.player_Spy = spyChoice;

	}

	void resetCurrentEvidenceOptions(DeferredRenderObject* buttonObj) {

		Cabin spy_choice = main_page.player_Spy;
		no_of_Evidence = allCabinData[spy_choice].activeEvidence.size();

		if (no_of_Evidence == 0) {

			buttonObj->showObject = false;
			buttonObj->gameObj->setActiveStatus(false);

			mainPageEvidence[0] = " - ";
			mainPageEvidence[1] = " - ";

		}
		else if (no_of_Evidence == 1) {

			buttonObj->showObject = true;
			buttonObj->gameObj->setActiveStatus(true);

			mainPageEvidence[0] = allCabinData[spy_choice].activeEvidence.at(0);
			mainPageEvidence[1] = " - ";
		}
		else {

			buttonObj->showObject = true;
			buttonObj->gameObj->setActiveStatus(true);

			mainPageEvidence[0] = allCabinData[spy_choice].activeEvidence.at(0);
			mainPageEvidence[1] = allCabinData[spy_choice].activeEvidence.at(1);

		}

	}

	void SetPlayerBombLocation(Location bombLocation) {
		main_page.player_BombLocation = bombLocation;
	}


	//------------------CABIN PAGE FUNCTIONS--------------------------


	// Function to activate a clue for a specific page
	void ActivateClue(Cabin cabin, int index) {

		if (index >= 0 && index < allCabinData[cabin].textClues.size()) {

			ClueData* activatedClue = allCabinData[cabin].textClues[index];
			activatedClue->showClue = true;

			if (activatedClue->isEvidence) {

				Text* textObject = dynamic_cast<Text*>(activatedClue->clueObject);
				std::string evidencetext = textObject->GetContent();
				allCabinData[cabin].activeEvidence.push_back(evidencetext);

			}

		}
		else {
			if (cabin == CABIN3 && index == 10) {
				BookClueState[0] = true;
			}

			if (cabin == CABIN4 && index == 7) {
				BookClueState[1] = true;
			}
		}

	}

	// Function to deactivate a clue for a specific page
	void DeactivateClue(Cabin cabin, int index) {

		if (index >= 0 && index < allCabinData[cabin].textClues.size()) {

			allCabinData[cabin].textClues[index]->showClue = false;

		}

	}

	void addClueToJournalData(Cabin cabin, ClueData* newClue) {

		allCabinData[cabin].textClues.push_back(newClue);

	}


	//GET PAGE INFO FUNCTIONS

	MainPageData& GetMainPageData() { return main_page; }

	CabinPageData& GetCabinPageData(Cabin cabin) {
		return allCabinData[cabin];
	}

	//CHECK FINAL ENTRY

	int checkMainPageEntry() {

		Cabin spy_choice = main_page.player_Spy;
		Location location_choice = main_page.player_BombLocation;
		int evidence_choice = main_page.player_Evidence;

		//----------CHECK IF CHOICES ARE CORRECT HERE AND SET BOOL BELOW----------------

		bool spyCorrect = false;
		bool locationCorrect = false;
		bool evidenceCorrect = false;

		if (spy_choice == CABIN21) spyCorrect = true;
		if (location_choice == TOWNSQUARE) locationCorrect = true;
		if (mainPageEvidence[evidence_choice] == "After visiting National Day Event with his sister") evidenceCorrect = true;

		if (spyCorrect) {

			if (evidenceCorrect && locationCorrect)
				return END1;

			if (evidenceCorrect && !locationCorrect)
				return END2;

			if (!evidenceCorrect && locationCorrect)
				return END3;

			if (!evidenceCorrect && !locationCorrect)
				return END4;

		}
		else {

			if (locationCorrect) {
				return END5;
			}
			else {
				return END6;
			}

		}

	}

	bool getBookClueState(int index) {
		return BookClueState[index];
	}

	//Use for ending scene to prevent closing book
	bool GetBookState() {
		return LockBook;
	}
	
	void SetBookState(bool status) {
		LockBook = status;
	}

private:

	static JournalData* instance;

	JournalData() {

		main_page.player_Spy = CABIN_EMPTY;
		main_page.player_BombLocation = Location::LOCATION_EMPTY;
		main_page.player_Evidence = 0;

	}

	//PAGE DATA
	MainPageData main_page;
	std::map<Cabin, CabinPageData> allCabinData;

	//MAIN PAGE EVIDENCE STORE
	std::map<Cabin, std::vector<std::string>> allCabinEvidenceChoices;
	std::string mainPageEvidence[2] = { " - ", " - " };
	int no_of_Evidence = 0;

	//BOOK CLUE (NOT THE SAME AS PAGE CLUEs
	//STATE OF 2 DRAGGABLE OBJECTS IN BOOK
	bool BookClueState[2] = { false, false };

	bool LockBook = false; //Set as true so player can't close journal

};


JournalData* JournalData::instance = nullptr;
