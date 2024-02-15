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

	std::string evidence;


};

struct CabinPageData {

	//2 arrays for text clue

	Location lastVisit;


};

class JournalData {

	public:

		JournalData(){
		
			main_page.player_Spy = SPY_EMPTY;
			main_page.player_BombLocation = LOCATION_EMPTY;
		
		}

		//GET FUNCTIONS

		MainPageData& GetMainPageData() {return main_page;}

		CabinPageData& GetCabinPageData(Spy cabin) {
			return allCabinData[cabin];
		}

		//SET FUNCTIONS FOR MAIN PAGE

		void SetPlayerSpyChoice(Spy spyChoice) {
			main_page.player_Spy = spyChoice;
		}

		void SetPlayerBombLocation(Location bombLocation) {
			main_page.player_BombLocation = bombLocation;
		}

		//SET FOR CABIN PAGE

		void SetLastVisit(Spy cabin, Location location) {
			allCabinData[cabin].lastVisit = location;
		}



	private:

		MainPageData main_page;

		std::map<Spy, CabinPageData> allCabinData;


};

