#pragma once

#include "../Text/Text.h"

enum Location { LOCATION_EMPTY, TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT };

enum Spy { SPY_EMPTY, SPY1, SPY21, SPY22, SPY3, SPY4 };

enum Cabin {ClUE_CABIN1, ClUE_CABIN21, ClUE_CABIN22, ClUE_CABIN3, ClUE_CABIN4 };

//FOR TEXT CLUES THAT GET UNBLURRED THROUGHOUT THE GAME

struct EvidenceClue {

	bool showText;
	Text* evidenceText = nullptr;

};


struct MainPageData {

	Spy player_Spy;
	Location player_BombLocation;  
	int player_Evidence;

};

struct CabinPageData {

	std::vector<EvidenceClue> textClues;
	Location lastVisit;

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
		
		//Set last visit
		void SetLastVisit(Cabin cabin, Location location) {
			allCabinData[cabin].lastVisit = location;
		}

		// Function to activate a clue for a specific page
		void ActivateClue(Cabin cabin, int index) {
			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {
				allCabinData[cabin].textClues[index].showText = true;
			}
		}

		// Function to deactivate a clue for a specific page
		void DeactivateClue(Cabin cabin, int index) {
			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {
				allCabinData[cabin].textClues[index].showText = false;
			}
		}

		// Function to check if the showText status of a clue is true or false
		bool isClueActive(Cabin cabin, int index) {

			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {
				return allCabinData[cabin].textClues[index].showText;
			}

			return false; // Return false if the provided cabin or index is invalid

		}

		// Function to get the Text object of a clue
		Text* getClueText(Cabin cabin, int index) {

			if (index >= 0 && index < allCabinData[cabin].textClues.size()) {
				return allCabinData[cabin].textClues[index].evidenceText;
			}

			return nullptr; // Return nullptr if the provided cabin or index is invalid

		}
		

		//GET PAGE INFO FUNCTIONS

		MainPageData& GetMainPageData() {return main_page;}

		CabinPageData& GetCabinPageData(Cabin cabin) {
			return allCabinData[cabin];
		}

		void InstantiateClues() {

			//----------------CABIN 1-------------------

			Text* M_C1 = new Text("M_C1", "Family resides at Eastside", "Assets/Fonts/ESA-m.ttf");
			M_C1->SetPosition(glm::vec3(1.0f, 2.7f, 0.0f));
			M_C1->SetColor(glm::vec3(0, 0, 0));
			M_C1->SetScale(0.58f);

			EvidenceClue cabin1_clue1;
			cabin1_clue1.evidenceText = M_C1;
			cabin1_clue1.showText = false;

			Text* M_C2 = new Text("M_C2", "Injury at right leg", "Assets/Fonts/ESA-smb.ttf");
			M_C2->SetPosition(glm::vec3(0.9f, 2.1f, 0.0f));
			M_C2->SetColor(glm::vec3(0, 0, 0));
			M_C2->SetScale(0.6f);

			EvidenceClue cabin1_clue2;
			cabin1_clue1.evidenceText = M_C2;
			cabin1_clue1.showText = false;

			Text* M_C3 = new Text("M_C3", "Pen-pal friend?", "Assets/Fonts/ESA-smb.ttf");
			M_C3->SetPosition(glm::vec3(1.05f, 1.45f, 0.0f));
			M_C3->SetColor(glm::vec3(0, 0, 0));
			M_C3->SetScale(0.65f);

			EvidenceClue cabin1_clue3;
			cabin1_clue1.evidenceText = M_C3;
			cabin1_clue1.showText = false;

			Text* M_C4 = new Text("M_C4", "Severe domestic violence accident", "Assets/Fonts/ESA-m.ttf");
			M_C4->SetPosition(glm::vec3(3.65f, 1.9f, 0.0f));
			M_C4->SetColor(glm::vec3(0, 0, 0));
			M_C4->SetScale(0.6f);

			EvidenceClue cabin1_clue4;
			cabin1_clue1.evidenceText = M_C4;
			cabin1_clue1.showText = false;

			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_clue1);
			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_clue2);
			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_clue3);
			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_clue4);

			// LAST ACTIVITY 1
			Text* M_LA = new Text("M_LA1", "Received a letter from Westside", "Assets/Fonts/ESA-smb.ttf");
			M_LA->SetPosition(glm::vec3(0.85f, -0.2f, 0.0f));
			M_LA->SetColor(glm::vec3(0, 0, 0));
			M_LA->SetScale(0.6f);

			EvidenceClue cabin1_lastActivity1;
			cabin1_lastActivity1.evidenceText = M_LA;
			cabin1_lastActivity1.showText = false;

			Text* M_LA2 = new Text("M_LA2", "Hire someone to send a letter instead of using post service", "Assets/Fonts/ESA-m.ttf");
			M_LA2->SetPosition(glm::vec3(3.1f, -0.22f, 0.0f));
			M_LA2->SetColor(glm::vec3(0, 0, 0));
			M_LA2->SetScale(0.5f);

			EvidenceClue cabin1_lastActivity2;
			cabin1_lastActivity1.evidenceText = M_LA2;
			cabin1_lastActivity1.showText = false;

			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_lastActivity1);
			allCabinData[Cabin::ClUE_CABIN1].textClues.push_back(cabin1_lastActivity2);

			//----------------CABIN 21-------------------



		}
		


	private:

		static JournalData* instance;


		JournalData() {

			main_page.player_Spy = Spy::SPY_EMPTY;
			main_page.player_BombLocation = Location::LOCATION_EMPTY;
			main_page.player_Evidence = 0;

			InstantiateClues();

		}

		MainPageData main_page;

		std::map<Cabin, CabinPageData> allCabinData;

		std::string mainPageEvidence[4] = { "Evidence 1","Evidence 2", "Evidence 3", "Evidence 4" };

		

};

JournalData* JournalData::instance = nullptr;

