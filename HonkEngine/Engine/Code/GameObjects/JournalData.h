#pragma once


enum Location { LOCATION_EMPTY, TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT };

enum Spy { SPY_EMPTY, SPY1, SPY21, SPY22, SPY3, SPY4 };

//FOR TEXT CLUES THAT GET UNBLURRED THROUGHOUT THE GAME

struct textClue {

	bool showText;
	std::string text;

};



struct MainPageData {

	Spy player_Spy;

	Location player_BombLocation;  

	int player_Evidence;


};

struct CabinPageData {

	//2 arrays for text clue

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

		//SET FUNCTIONS FOR MAIN PAGE

		void SetPlayerSpyChoice(Spy spyChoice) {
			main_page.player_Spy = spyChoice;

			//std::cout << "SET SPY " << spyChoice << std::endl;

		}

		void SetPlayerBombLocation(Location bombLocation) {
			main_page.player_BombLocation = bombLocation;
		}

		//SET FOR CABIN PAGE

		void SetLastVisit(Spy cabin, Location location) {
			allCabinData[cabin].lastVisit = location;
		}

		void incrementEvidence() {

			// Increment index and wrap around if needed
			main_page.player_Evidence = (main_page.player_Evidence + 1) % 4;  

		}

		std::string getEvidenceText() {

			return mainPageEvidence[main_page.player_Evidence];

		}


		//GET FUNCTIONS

		MainPageData& GetMainPageData() {return main_page;}

		CabinPageData& GetCabinPageData(Spy cabin) {
			return allCabinData[cabin];
		}
		


	private:

		static JournalData* instance;


		JournalData() {

			main_page.player_Spy = SPY_EMPTY;
			main_page.player_BombLocation = LOCATION_EMPTY;
			main_page.player_Evidence = 0;

		}

		MainPageData main_page;

		std::map<Spy, CabinPageData> allCabinData;

		std::string mainPageEvidence[4] = { "Evidence 1","Evidence 2", "Evidence 3", "Evidence 4" };


};

JournalData* JournalData::instance = nullptr;

