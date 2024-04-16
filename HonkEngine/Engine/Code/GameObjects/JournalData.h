#pragma once

#include "../Text/Text.h"

enum Location { LOCATION_EMPTY, TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT };

enum Spy { SPY_EMPTY, SPY1, SPY21, SPY22, SPY3, SPY4 };

enum Cabin {CLUE_CABIN1, CLUE_CABIN21, CLUE_CABIN22, CLUE_CABIN3, CLUE_CABIN4 };


struct ClueData {

	bool showText;
	Text* clueText = nullptr;

};


struct MainPageData {

	Spy player_Spy;
	Location player_BombLocation;  
	int player_Evidence;

};

struct CabinPageData {

	std::vector<ClueData*> textClues;
	bool ShowLastActivity = false;

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

		//SER PLAYER CHOICES

		void SetPlayerSpyChoice(Spy spyChoice) {
			main_page.player_Spy = spyChoice;
		}

		void SetPlayerBombLocation(Location bombLocation) {
			main_page.player_BombLocation = bombLocation;
		}

		//EVIDENCE BUTTON FUNCTIONS

		void incrementEvidence() {
			// Increment index and wrap around if needed
			main_page.player_Evidence = (main_page.player_Evidence + 1) % 4;
		}

		std::string getEvidenceText() {
			return mainPageEvidence[main_page.player_Evidence];
		}

		//------------------CABIN PAGE FUNCTIONS--------------------------
	

		// Function to activate a clue for a specific page
		void ActivateClue(Cabin cabin, int index) {

			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {

				allCabinData[cabin].textClues[index]->showText = true;

			}

		}

		// Function to deactivate a clue for a specific page
		void DeactivateClue(Cabin cabin, int index) {

			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {

				allCabinData[cabin].textClues[index]->showText = false;

			}

		}

		void activateLastActivity(Cabin cabin) {

			allCabinData[cabin].ShowLastActivity = true;

		}

		void addClueToJournalData(Cabin cabin, ClueData *newClue){

			allCabinData[cabin].textClues.push_back(newClue);

		}
	

		//GET PAGE INFO FUNCTIONS

		MainPageData& GetMainPageData() {return main_page;}

		CabinPageData& GetCabinPageData(Cabin cabin) {
			return allCabinData[cabin];
		}

	


	private:

		static JournalData* instance;


		JournalData() {

			main_page.player_Spy = Spy::SPY_EMPTY;
			main_page.player_BombLocation = Location::LOCATION_EMPTY;
			main_page.player_Evidence = 0;

		}

		MainPageData main_page;

		std::map<Cabin, CabinPageData> allCabinData;

		std::string mainPageEvidence[4] = { "Evidence 1","Evidence 2", "Evidence 3", "Evidence 4" };

		

};

JournalData* JournalData::instance = nullptr;

