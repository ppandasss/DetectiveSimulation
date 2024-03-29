#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "KitchenData.h"

class Kitchen : public Scene {

public:

	Kitchen() :audioManager(AudioManager::GetInstance()) {


		/*--------------------------------------------------------------LOAD AUDDIO------------------------------------------------------------------------------------------------------- */
		/*audioManager.LoadSound("kitchenAmbience", "Assets/Sounds/Ambience_Kitchen.mp3", 0.2f);
		audioManager.PlaySound("kitchenAmbience", true);*/

		/*--------------------------------------------------------------CREATE GAMEOBJECT------------------------------------------------------------------------------------------------------- */

		GameObject* KitchenBackground = new RenderGameObject("KitchenBackground", "Assets/Images/Kitchen/Kitchen_Background.png");
		KitchenBackground->SetScale(glm::vec3(19.5f, 10.8f, 0.0f));
		KitchenBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));


		/*--------------------------------------------------------------CREATE BUTTONS------------------------------------------------------------------------------------------------------- */

		ServeBellButton = new UIButton("ServeBellButton", "Assets/Images/Kitchen/ServeButton_servable_default.png", glm::vec3(-4.3f, -2.1f, 0.0f), glm::vec3(2.2f, 1.5f, 0.0f), true, false);
		ServeBellButton->setActiveStatus(false);
		ServeBellButton->SetOnClickAction([this]() { Serve(); });
		
		ServeBellGrey = new RenderGameObject("ServeBellGrey", "Assets/Images/Kitchen/ServeButton_notServable_default.png");
		ServeBellGrey->SetPosition(glm::vec3(-4.3f, -2.1f, 0.0f));
		ServeBellGrey->SetScale(glm::vec3(2.2f, 1.5f, 0.0f));

		/*--------------------------------------------------------------CREATE FOOD DRAGGABLES------------------------------------------------------------------------------------------------------- */

		EarlGreyTea = new UIDraggable("EarlGreyTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Earl.png", glm::vec3(1.8f, 0.0f, 0.0f), glm::vec3(1.3f, 1.6f, 0.0f), true);
		AssamBlackTea = new UIDraggable("AssamBlackTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Assam.png", glm::vec3(3.5f, 0.0f, 0.0f), glm::vec3(1.3f, 1.6f, 0.0f), true);

		SalmonSandwhich = new UIDraggable("SalmonSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Salmon.png", glm::vec3(2.3f, -2.1f, 0.0f), glm::vec3(2.6f, 1.3f, 0.0f), true);
		EggSandwhich = new UIDraggable("EggSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Egg.png", glm::vec3(5.3f, -2.1f, 0.0f), glm::vec3(2.6f, 1.3f, 0.0f), true);

		Eclair = new UIDraggable("Eclair", "Assets/Images/Kitchen/Food/Dessert/Dessert_Eclair.png", glm::vec3(2.3f, -4.3f, 0.0f), glm::vec3(2.2f, 0.8f, 0.0f), true);
		Macaron = new UIDraggable("Macaron", "Assets/Images/Kitchen/Food/Dessert/Dessert_Macaron.png", glm::vec3(5.3f, -4.3f, 0.0f), glm::vec3(2.2f, 0.8f, 0.0f), true);

		/*--------------------------------------------------------------SET DRAGGABLE FOOD FUNCTIONS------------------------------------------------------------------------------------------------------- */

		EarlGreyTea->SetOnReleaseAction([this]() { releaseEarlGrey(); });
		AssamBlackTea->SetOnReleaseAction([this]() { releaseAssam(); });

		SalmonSandwhich->SetOnReleaseAction([this]() { releaseSalmonSandwhich(); });
		EggSandwhich->SetOnReleaseAction([this]() { releaseEggSandwhich(); });

		Eclair->SetOnReleaseAction([this]() { releaseEclair(); });
		Macaron->SetOnReleaseAction([this]() { releaseMacaron(); });

		/*-------------------------------------------------------------- CREATE PLATED FOOD ------------------------------------------------------------------------------------------------------- */

		GameObject* EarlGreyTea_dish = new RenderGameObject("EarlGreyDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Earl.png");
		EarlGreyTea_dish->SetPosition(TeaDishPosition);
		EarlGreyTea_dish->SetScale(glm::vec3(1.3f, 1.6f, 0.0f));

		GameObject* AssamBlack_dish = new RenderGameObject("AssamBlackDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Assam.png");
		AssamBlack_dish->SetPosition(TeaDishPosition);
		AssamBlack_dish->SetScale(glm::vec3(1.3f, 1.6f, 0.0f));

		GameObject* SalmonDish = new RenderGameObject("SalmonDish", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Salmon_Dish.png");
		SalmonDish->SetPosition(SandwhichDishPosition);
		SalmonDish->SetScale(glm::vec3(2.6f, 1.3f, 0.0f));

		GameObject* EggDish = new RenderGameObject("EggDish", "Assets/Images/Kitchen/Food/Sandwhich/Meal_Egg_dish.png");
		EggDish->SetPosition(SandwhichDishPosition);
		EggDish->SetScale(glm::vec3(2.6f, 1.3f, 0.0f));

		GameObject* EclairDish = new RenderGameObject("EclairDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_Eclair_dish.png");
		EclairDish->SetPosition(DessertDishPosition);
		EclairDish->SetScale(glm::vec3(2.6f, 0.8f, 0.0f));

		GameObject* MacaronDish = new RenderGameObject("MacaronDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_Macaron_dish.png");
		MacaronDish->SetPosition(DessertDishPosition);
		MacaronDish->SetScale(glm::vec3(2.6f, 0.8f, 0.0f));

		/*--------------------------------------------------------------PUSH BACK------------------------------------------------------------------------------------------------------- */

		m_gameObjects.push_back(KitchenBackground);
		m_gameObjects.push_back(ServeBellButton);
		m_gameObjects.push_back(ServeBellGrey);

		//PLATED FOOD GAMEOBJECTS

		platedTea[EARLGREYTEA] = EarlGreyTea_dish;
		platedTea[ASSAMTEA] = AssamBlack_dish;

		platedSandwhich[SALMON] = SalmonDish;
		platedSandwhich[EGG] = EggDish;

		platedDessert[ECLAIR] = EclairDish;
		platedDessert[MACARON] = MacaronDish;

		m_gameObjects.push_back(EarlGreyTea_dish);
		m_gameObjects.push_back(AssamBlack_dish);

		m_gameObjects.push_back(SalmonDish);
		m_gameObjects.push_back(EggDish);

		m_gameObjects.push_back(EclairDish);
		m_gameObjects.push_back(MacaronDish);


		//DRAGGABLE FOOD	
		m_gameObjects.push_back(EarlGreyTea);
		m_gameObjects.push_back(AssamBlackTea);

		m_gameObjects.push_back(SalmonSandwhich);
		m_gameObjects.push_back(EggSandwhich);

		m_gameObjects.push_back(Eclair);
		m_gameObjects.push_back(Macaron);


		//set all plate gameobjects as inactive
		clearPlate();

	}

	void Update(float dt, long frame) override {

		Scene::Update(dt, frame);

		if (input.Get().GetKeyDown(GLFW_KEY_K)) {
			Application::Get().SetScene("Hallway");
		}

		if (input.Get().GetKeyDown(GLFW_KEY_R)) { //RESET KITCHEN
			clearPlate();
		}

		updateServeButton();

	}


	void clearPlate() {

		//set all as inactive

		for (int i = 0; i < 2; i++) {
			platedTea[i]->setActiveStatus(false);
		}
		for (int i = 0; i < 2; i++) {
			platedSandwhich[i]->setActiveStatus(false);
		}
		for (int i = 0; i < 2; i++) {
			platedDessert[i]->setActiveStatus(false);
		}

		KitchenData::GetInstance()->clearPlate();

	}

	void updateSandwhichStatus() {

		for (int i = 0; i < 2; i++) {
			if (i == KitchenData::GetInstance()->getSandwhich()) {
				platedSandwhich[i]->setActiveStatus(true);
			}
			else {
				platedSandwhich[i]->setActiveStatus(false);
			}
		}

	}

	void updateDessertStatus() {


		for (int i = 0; i < 2; i++) {
			if (i == KitchenData::GetInstance()->getDessert()) {
				platedDessert[i]->setActiveStatus(true);
			}
			else {
				platedDessert[i]->setActiveStatus(false);
			}
		}

	}

	void updateTeaStatus() {


		for (int i = 0; i < 2; i++) {
			if (i == KitchenData::GetInstance()->getTea()) {
				platedTea[i]->setActiveStatus(true);
			}
			else {
				platedTea[i]->setActiveStatus(false);
			}
		}

	}

	//ON RELEASE FUNCTIONS

	void releaseEarlGrey() {

		//std::cout << "EARL GREY RELEASED" << std::endl;
		if (EarlGreyTea->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setTea(EARLGREYTEA);
			updateTeaStatus();
		}

	}

	void releaseAssam() {

		//std::cout << "ASSAM RELEASED" << std::endl;
		if (AssamBlackTea->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setTea(ASSAMTEA);
			updateTeaStatus();
		}

	}

	void releaseSalmonSandwhich() {

		//std::cout << "Salmon RELEASED" << std::endl;
		if (SalmonSandwhich->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(SALMON);
			updateSandwhichStatus();
		}

	}

	void releaseEggSandwhich() {

		//std::cout << "Egg sandwhich RELEASED" << std::endl;
		if (EggSandwhich->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(EGG);
			updateSandwhichStatus();
		}
	}

	void releaseEclair() {

		//std::cout << "ECLAIR RELEASED" << std::endl;
		if (Eclair->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setDessert(ECLAIR);
			updateDessertStatus();
		}

	}

	void releaseMacaron() {

		//std::cout << "MACARON RELEASED" << std::endl;
		if (Macaron->withinRage(platePosition, snapThreshold)) {
			KitchenData::GetInstance()->setDessert(MACARON);
			updateDessertStatus();
		}

	}

	void Serve() {
		std::cout << "SERVE FOOD" << std::endl;
	}

	void updateServeButton() {

		if (KitchenData::GetInstance()->checkCompletePlate()) {
			ServeBellButton->setActiveStatus(true);
			ServeBellGrey->setActiveStatus(false);
		}
		else {
			ServeBellButton->setActiveStatus(false);
			ServeBellGrey->setActiveStatus(true);
		}

	}


private:

	AudioManager& audioManager;
	Input& input = Application::GetInput();

	const glm::vec3 tea_platePos;
	const glm::vec3 sandwhich_platePos;
	const glm::vec3 dessert_platePos;

	UIDraggable* EarlGreyTea;
	UIDraggable* AssamBlackTea;
	UIDraggable* SalmonSandwhich;
	UIDraggable* EggSandwhich;
	UIDraggable* Eclair;
	UIDraggable* Macaron;

	UIButton* ServeBellButton;
	GameObject* ServeBellGrey;


	//Array of plated game objects
	GameObject* platedSandwhich[2];
	GameObject* platedDessert[2];
	GameObject* platedTea[2];

	const glm::vec3 TeaDishPosition = glm::vec3(-7.5f, 0.0f, 0.0f);
	const glm::vec3 SandwhichDishPosition = glm::vec3(-5.5f, -0.3f, 0.0f);
	const glm::vec3 DessertDishPosition = glm::vec3(-2.8f, -0.35f, 0.0f);

	//within range

	const glm::vec3 platePosition = glm::vec3(-5.5f, 0.0f, 0.0f);
	const float snapThreshold = 4.0f;


};
