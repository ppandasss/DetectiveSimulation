#pragma once

#include "../Text/Text.h"

enum Location { TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT, LOCATION_EMPTY };

//used for clues and character data

enum Cabin {CABIN1, CABIN21, CABIN22, CABIN3, CABIN4, CABIN_EMPTY };

enum Ending {END1, END2, END3, END4, END5, END6};


struct ClueData {

	bool showText;
	Text* clueText = nullptr;
	bool isEvidence = false;

};

struct DeferredRenderObject {

	bool showObject;
	GameObject* gameObj;
};


struct MainPageData {

	Cabin player_Spy;
	Location player_BombLocation;  
	std::string player_Evidence;

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

		void SetPlayerSpyChoice(Cabin spyChoice) {
			main_page.player_Spy = spyChoice;
		}

		void SetPlayerBombLocation(Location bombLocation) {
			main_page.player_BombLocation = bombLocation;
		}

		//EVIDENCE BUTTON FUNCTIONS

		void incrementEvidence() {
			// Increment index and wrap around if needed
			//main_page.player_Evidence = (main_page.player_Evidence + 1) % 2;
		}

		std::string getEvidenceText() {
			return main_page.player_Evidence;
		}

		

		//------------------CABIN PAGE FUNCTIONS--------------------------
	

		// Function to activate a clue for a specific page
		void ActivateClue(Cabin cabin, int index) {

			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {

				ClueData* activatedClue = allCabinData[cabin].textClues[index];
				activatedClue->showText = true;

				if (activatedClue->isEvidence) {
					allCabinEvidenceChoices[cabin].push_back(activatedClue->clueText->GetContent());
				}

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

			if (newClue->showText && newClue->isEvidence) {
				allCabinEvidenceChoices[cabin].push_back(newClue->clueText->GetContent());
			}

		}
	

		//GET PAGE INFO FUNCTIONS

		MainPageData& GetMainPageData() {return main_page;}

		CabinPageData& GetCabinPageData(Cabin cabin) {
			return allCabinData[cabin];
		}

		//CHECK FINAL ENTRY

		Ending checkMainPageEntry() {

			Cabin spy_choice = main_page.player_Spy;
			Location location_choice = main_page.player_BombLocation;
			std::string evidence_choice = main_page.player_Evidence;

			//----------CHECK IF CHOICES ARE CORRECT HERE AND SET BOOL BELOW----------------

			bool spyCorrect = false;
			bool locationCorrect = false;
			bool evidenceCorrect = false;

			if (spy_choice == CABIN21) spyCorrect = true;
			if (location_choice == TOWNSQUARE) locationCorrect = true;
			if (evidence_choice == "After visiting National Day Event with his sister") evidenceCorrect = true;

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

			main_page.player_Spy = CABIN_EMPTY;
			main_page.player_BombLocation = Location::LOCATION_EMPTY;
			main_page.player_Evidence = "";

		}

		MainPageData main_page;

		std::map<Cabin, CabinPageData> allCabinData;

		std::map<Cabin,std::vector<std::string>> allCabinEvidenceChoices;

		std::string mainPageEvidence[2] = { "Evidence 1","Evidence 2" };



};


JournalData* JournalData::instance = nullptr;

