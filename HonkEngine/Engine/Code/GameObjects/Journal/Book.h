#pragma once

#include "../GameObjects/GameObject.h"
#include "../GameObjects/RenderGameObject.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include "../Application.h"
#include"../Scene/Scene.h"
#include "../Input/Input.h"
#include "JournalData.h"
#include <iostream>


enum currentPage {MAIN, CABIN1, CABIN21, CABIN22, CABIN3, CABIN4, GUIDE1, GUIDE2};

//FIGURE OUT A DATA STRUCTURE TO STORE PAGE DATA

//SUBCLASS - MAINPAGE
//SUBCLASS - CHARACTERPAGE
//SUBCLASS - TEAGUIDE

class Book : public RenderGameObject {

public:

	void openBook(){


	}
	void closeBook();

	//void drawMainPage();
	//void drawCharacterPage(currentPage page);
	//void drawTeaGuide();

private:

	//status of current page player is on, resets to MAIN everytime player closes book
	currentPage activePage = MAIN;

};