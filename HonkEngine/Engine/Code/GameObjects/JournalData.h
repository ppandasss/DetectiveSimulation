#pragma once

#include "../Text/Text.h"

#include "../UI/UIButtonEmpty.h"

using namespace std;

enum Location { TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT, LOCATION_EMPTY };

//used for clues and character data

enum Cabin { CABIN1, CABIN21, CABIN22, CABIN3, CABIN4, CABIN_EMPTY, MAINPAGE, FOODGUIDE };

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

	using JournalObserver = std::function<void()>;

	static JournalData* GetInstance() {

		if (instance == nullptr) {
			instance = new JournalData();
		}
		return instance;
	}

	void AddObserver(JournalObserver observer) {
		observers.push_back(observer);
	}

	void NotifyObservers() {
		for (auto& observer : observers) {
			observer();
		}
	}

	//------------------MAIN PAGE FUNCTIONS--------------------------


	void incrementEvidence() {
		//Increment index and wrap around if needed

		//std::cout << "INCREMENT CALLED" << std::endl;

		main_page.player_Evidence = (main_page.player_Evidence + 1) % 2;

	}

	void setCurrentEvidencetext(UIButtonEmpty* evidenceButton) {

		no_of_Evidence = allCabinData[main_page.player_Spy].activeEvidence.size();

		if (no_of_Evidence == 0) {
			evidenceButton->SetButtonText("EMPTY");

		} else if (no_of_Evidence == 1){
			evidenceButton->SetButtonText(mainPageEvidence[0]);

		}
		else {
			evidenceButton->SetButtonText(mainPageEvidence[main_page.player_Evidence]);
		}

	}


	// Add a method to set the spy choice without notifying observers
	void SetPlayerSpyChoiceInternal(Cabin spyChoice) {
		main_page.player_Spy = spyChoice;
	}

	// Modified SetPlayerSpyChoice method to notify observers
	void SetPlayerSpyChoice(Cabin spyChoice) {
		SetPlayerSpyChoiceInternal(spyChoice);
		NotifyObservers();
	}

	// Add a similar method for bomb location
	void SetPlayerBombLocationInternal(Location bombLocation) {
		main_page.player_BombLocation = bombLocation;
	}

	// Modified SetPlayerBombLocation method to notify observers
	void SetPlayerBombLocation(Location bombLocation) {
		SetPlayerBombLocationInternal(bombLocation);
		NotifyObservers();
	}

	void resetCurrentEvidenceOptions(DeferredRenderObject* buttonObj) {

		Cabin spy_choice = main_page.player_Spy;

		//std::cout << "RESET SPY - RESET EVIDENCE \n";

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

		main_page.player_Evidence = 0;

	}



	//------------------CABIN PAGE FUNCTIONS--------------------------

	bool GetClueState(Cabin cabin, int clueIndex) const {

		auto cabinIt = clueStates.find(cabin);

		if (cabinIt != clueStates.end()) {
			auto clueIt = cabinIt->second.find(clueIndex);

			if (clueIt != cabinIt->second.end()) {

				return clueIt->second;

			}
		}

		return false;
	}

	// Function to activate a clue for a specific page
	void ActivateClue(Cabin cabin, int index) {


		if (cabin == CABIN3 && index == 10) {
			BookClueState[0] = true;
			return;
		}

		if (cabin == CABIN4 && index == 7) {
			BookClueState[1] = true;
			return;
		}

		clueStates[cabin][index] = true;

		if (evidenceMap.find(cabin) != evidenceMap.end() &&
			evidenceMap[cabin].find(index) != evidenceMap[cabin].end()) {

			std::string evidenceText = evidenceMap[cabin][index];
			allCabinData[cabin].activeEvidence.push_back(evidenceText);

		}
	

	}

	// Function to add evidence to the journal data
	void addEvidenceToJournal(Cabin cabin, int index, const std::string& evidenceText) {
		evidenceMap[cabin][index] = evidenceText;
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
		

		if (spyCorrect) {

			string evidenceChoice = "";
			if (mainPageEvidence->size() > 1) {
				evidenceChoice = mainPageEvidence[evidence_choice];
			}
			else if (mainPageEvidence->size() == 1) {
				evidenceChoice = mainPageEvidence[0];
			}

			if (evidenceChoice == "After visiting National Day Event with his sister") evidenceCorrect = true;

		}

		if (location_choice == TOWNSQUARE) locationCorrect = true;

		if (spyCorrect) {
			if (evidenceCorrect && locationCorrect) return END1;
			if (evidenceCorrect && !locationCorrect) return END2;
			if (!evidenceCorrect && locationCorrect) return END3;
			return END4;
		}
		else {
			return locationCorrect ? END5 : END6;
		}

	}

	bool getBookClueState(int index) {
		return BookClueState[index];
	}

	//Use for ending scene to prevent closing book
	bool GetSceneState() {
		return LastScene;
	}

	bool GetBookState() {
		return LockBook;
	}
	
	void SetBookState(bool status) {
		LockBook = status;
	}

	void ActivateLastScene() {
		SetBookState(true);
		LastScene = true;
	}

	void ResetJournalData() {

		// Reset main page data
		main_page.player_Spy = CABIN_EMPTY;
		main_page.player_BombLocation = LOCATION_EMPTY;
		main_page.player_Evidence = 0;

		// Clear all cabin data
		allCabinData.clear();

		// Clear clue states
		clueStates.clear();

		// Clear evidence map
		evidenceMap.clear();

		// Reset main page evidence
		mainPageEvidence[0] = " - ";
		mainPageEvidence[1] = " - ";
		no_of_Evidence = 0;

		// Reset book clue states
		BookClueState[0] = false;
		BookClueState[1] = false;

		// Reset lock book state
		LockBook = false;

		NotifyObservers();

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

	std::map<Cabin, std::map<int, bool>> clueStates;


	// Map to store evidence information
	std::map<Cabin, std::map<int, std::string>> evidenceMap;

	//MAIN PAGE EVIDENCE STORE
	//std::map<Cabin, std::vector<std::string>> allCabinEvidenceChoices;
	std::string mainPageEvidence[2] = { " - ", " - " };
	int no_of_Evidence = 0;

	//BOOK CLUE (NOT THE SAME AS PAGE CLUEs
	//STATE OF 2 DRAGGABLE OBJECTS IN BOOK
	bool BookClueState[2] = { false, false };

	bool LastScene = false;
	bool LockBook = false; //Set as true so player can't close journal

	std::vector<JournalObserver> observers;

};


JournalData* JournalData::instance = nullptr;
