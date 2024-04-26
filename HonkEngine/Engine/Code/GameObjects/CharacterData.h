#pragma once

#include "../Scene/KitchenData.h"
#include "JournalData.h"

#include <map>

struct characterFoodScores {

	std::map<Sandwhich, int> SandwhichScores;
	std::map<Tea, int> TeaScores;
	std::map<Dessert, int> DessertScores;
	std::map<Tea, int> TeaMilkScores;

};

class CharacterData {

public:

	static CharacterData* GetInstance() {

		if (instance == nullptr) {
			instance = new CharacterData();
		}
		return instance;
	}

	//get score based on food choices



	
	
private:

	CharacterData() {

		//--------------------CABIN 1 FOOD SCORES--------------------

		characterFoodScores* cabin1Scores = new characterFoodScores;

		cabin1Scores->SandwhichScores[Sandwhich::SALMON] = 1;
		cabin1Scores->SandwhichScores[Sandwhich::EGG] = 3;
		cabin1Scores->SandwhichScores[Sandwhich::CUCUMBER] = 1;
		cabin1Scores->SandwhichScores[Sandwhich::BEEF] = 1;

		cabin1Scores->TeaScores[Tea::EARLGREYTEA] = 2;
		cabin1Scores->TeaScores[Tea::CHAMOMILETEA] = 4;
		cabin1Scores->TeaScores[Tea::ASSAMTEA] = 0;
		cabin1Scores->TeaScores[Tea::GREENTEA] = 2;

		cabin1Scores->DessertScores[Dessert::ECLAIR] = 1;
		cabin1Scores->DessertScores[Dessert::MACARON] = 1;
		cabin1Scores->DessertScores[Dessert::TART] = 1;
		cabin1Scores->DessertScores[Dessert::SCONE] = 3;

		cabin1Scores->TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin1Scores->TeaMilkScores[Tea::CHAMOMILETEA] = 4;
		cabin1Scores->TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin1Scores->TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 2-1 FOOD SCORES--------------------

		characterFoodScores* cabin21Scores = new characterFoodScores;

		cabin21Scores->SandwhichScores[Sandwhich::SALMON] = 1;
		cabin21Scores->SandwhichScores[Sandwhich::EGG] = 3;
		cabin21Scores->SandwhichScores[Sandwhich::CUCUMBER] = 1;
		cabin21Scores->SandwhichScores[Sandwhich::BEEF] = 1;

		cabin21Scores->TeaScores[Tea::EARLGREYTEA] = 2;
		cabin21Scores->TeaScores[Tea::CHAMOMILETEA] = 4;
		cabin21Scores->TeaScores[Tea::ASSAMTEA] = 0;
		cabin21Scores->TeaScores[Tea::GREENTEA] = 2;

		cabin21Scores->DessertScores[Dessert::ECLAIR] = 1;
		cabin21Scores->DessertScores[Dessert::MACARON] = 1;
		cabin21Scores->DessertScores[Dessert::TART] = 1;
		cabin21Scores->DessertScores[Dessert::SCONE] = 3;

		cabin21Scores->TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin21Scores->TeaMilkScores[Tea::CHAMOMILETEA] = 4;
		cabin21Scores->TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin21Scores->TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 2-2 FOOD SCORES--------------------

		characterFoodScores* cabin22Scores = new characterFoodScores;

		cabin22Scores->SandwhichScores[Sandwhich::SALMON] = 1;
		cabin22Scores->SandwhichScores[Sandwhich::EGG] = 3;
		cabin22Scores->SandwhichScores[Sandwhich::CUCUMBER] = 1;
		cabin22Scores->SandwhichScores[Sandwhich::BEEF] = 1;

		cabin22Scores->TeaScores[Tea::EARLGREYTEA] = 2;
		cabin22Scores->TeaScores[Tea::CHAMOMILETEA] = 4;
		cabin22Scores->TeaScores[Tea::ASSAMTEA] = 0;
		cabin22Scores->TeaScores[Tea::GREENTEA] = 2;

		cabin22Scores->DessertScores[Dessert::ECLAIR] = 1;
		cabin22Scores->DessertScores[Dessert::MACARON] = 1;
		cabin22Scores->DessertScores[Dessert::TART] = 1;
		cabin22Scores->DessertScores[Dessert::SCONE] = 3;

		cabin22Scores->TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin22Scores->TeaMilkScores[Tea::CHAMOMILETEA] = 4;
		cabin22Scores->TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin22Scores->TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 3  FOOD SCORES--------------------

		characterFoodScores* cabin3Scores = new characterFoodScores;

		cabin3Scores->SandwhichScores[Sandwhich::SALMON] = 1;
		cabin3Scores->SandwhichScores[Sandwhich::EGG] = 3;
		cabin3Scores->SandwhichScores[Sandwhich::CUCUMBER] = 1;
		cabin3Scores->SandwhichScores[Sandwhich::BEEF] = 1;

		cabin3Scores->TeaScores[Tea::EARLGREYTEA] = 2;
		cabin3Scores->TeaScores[Tea::CHAMOMILETEA] = 4;
		cabin3Scores->TeaScores[Tea::ASSAMTEA] = 0;
		cabin3Scores->TeaScores[Tea::GREENTEA] = 2;

		cabin3Scores->DessertScores[Dessert::ECLAIR] = 1;
		cabin3Scores->DessertScores[Dessert::MACARON] = 1;
		cabin3Scores->DessertScores[Dessert::TART] = 1;
		cabin3Scores->DessertScores[Dessert::SCONE] = 3;

		cabin3Scores->TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin3Scores->TeaMilkScores[Tea::CHAMOMILETEA] = 4;
		cabin3Scores->TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin3Scores->TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 4 FOOD SCORES--------------------

		characterFoodScores* cabin4Scores = new characterFoodScores;

		cabin4Scores->SandwhichScores[Sandwhich::SALMON] = 1;
		cabin4Scores->SandwhichScores[Sandwhich::EGG] = 3;
		cabin4Scores->SandwhichScores[Sandwhich::CUCUMBER] = 1;
		cabin4Scores->SandwhichScores[Sandwhich::BEEF] = 1;

		cabin4Scores->TeaScores[Tea::EARLGREYTEA] = 2;
		cabin4Scores->TeaScores[Tea::CHAMOMILETEA] = 4;
		cabin4Scores->TeaScores[Tea::ASSAMTEA] = 0;
		cabin4Scores->TeaScores[Tea::GREENTEA] = 2;

		cabin4Scores->DessertScores[Dessert::ECLAIR] = 1;
		cabin4Scores->DessertScores[Dessert::MACARON] = 1;
		cabin4Scores->DessertScores[Dessert::TART] = 1;
		cabin4Scores->DessertScores[Dessert::SCONE] = 3;

		cabin4Scores->TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin4Scores->TeaMilkScores[Tea::CHAMOMILETEA] = 4;
		cabin4Scores->TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin4Scores->TeaMilkScores[Tea::GREENTEA] = 2;


		allCharacterData[CABIN1] = cabin1Scores;
		allCharacterData[CABIN21] = cabin21Scores;
		allCharacterData[CABIN22] = cabin22Scores;
		allCharacterData[CABIN3] = cabin3Scores;
		allCharacterData[CABIN4] = cabin4Scores;

	}

	static CharacterData* instance;

	std::map<Cabin, characterFoodScores*> allCharacterData;

	
};


CharacterData* CharacterData::instance = nullptr;