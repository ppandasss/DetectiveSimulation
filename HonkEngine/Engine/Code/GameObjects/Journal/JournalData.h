#pragma once

class JournalData {

public:

	enum Location{TOWNSQUARE, HOLYCHURCH, COUNCIL, SUPREMECOURT};

	struct MainPage {

		int playerSpyChoice; //CABIN 1-5
		
		Location playerBombLocation;

		//STORE STRING FOR EVIDENCE


	};

	struct CabinPage {

		//STORE STRING HERE FOR CHAR INFO

		Location lastVisit;

		//STORE LAST ACTIVITY


	};

	JournalData(){



	}


};

