#pragma once

#include "../Text/Text.h"

enum Location { LOCATION_EMPTY, TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT };

enum Spy { SPY_EMPTY, SPY1, SPY21, SPY22, SPY3, SPY4 };

//used for clues and character data

enum Cabin {CABIN1, CABIN21, CABIN22, CABIN3, CABIN4 };

enum Ending {END1, END2, END3, END4, END5, END6};


struct ClueData {

	bool showText;
	Text* clueText = nullptr;

};

struct DeferredRenderObject {

	bool showObject;
	GameObject* gameObj;
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

		//CHECK FINAL ENTRY

		Ending checkMainPageEntry() {

			Spy spy_choice = main_page.player_Spy;
			Location location_choice = main_page.player_BombLocation;
			int evidence_choice = main_page.player_Evidence;

			//----------CHECK IF CHOICES ARE CORRECT HERE AND SET BOOL BELOW----------------

			bool spyCorrect = true;
			bool locationCorrect = true;
			bool evidenceCorrect = true;


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

		
	


	private:

		static JournalData* instance;


		JournalData() {

			main_page.player_Spy = Spy::SPY_EMPTY;
			main_page.player_BombLocation = Location::LOCATION_EMPTY;
			main_page.player_Evidence = 0;

		}

		MainPageData main_page;

		std::map<Cabin, CabinPageData> allCabinData;

		std::vector<std::string> mainPageEvidenceVec;

		std::string mainPageEvidence[4] = { "Evidence 1","Evidence 2", "Evidence 3", "Evidence 4" };

};


JournalData* JournalData::instance = nullptr;

