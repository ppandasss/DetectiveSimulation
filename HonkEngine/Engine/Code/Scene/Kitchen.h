#pragma once

#include "Scene.h"

#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../UI/UIButtonEmpty.h"

#include "KitchenData.h"

class Kitchen : public Scene {

public:

	UIButtonEmpty* platePositionArea = new UIButtonEmpty("PlatePosition", glm::vec3(-5.5f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), true, true, "Assets/Fonts/ESA-m.ttf");
	

	Kitchen() :audioManager(AudioManager::GetInstance()) {
		//platePositionArea->SetButtonText("Drop Area");

		/*--------------------------------------------------------------LOAD AUDDIO------------------------------------------------------------------------------------------------------- */
		audioManager.LoadSound("kitchenAmbience", "Assets/Sounds/Ambience_Kitchen.mp3", 0.2f);
		audioManager.PlaySound("kitchenAmbience", true);

		/*--------------------------------------------------------------CREATE GAMEOBJECT------------------------------------------------------------------------------------------------------- */

		GameObject* KitchenBackground = new UIObject("KitchenBackground", "Assets/Images/Kitchen/Kitchen_Background.png",true);
		KitchenBackground->SetScale(glm::vec3(19.2f, 10.8f, 0.0f));
		KitchenBackground->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

		UIElement* orderPaper = new UINormal("OrderPaper", "Assets/Images/OrderPaper.png", glm::vec3(-7.65f, 4.0f, 0.0f), glm::vec3(3.55f, 2.54f, 0.0f), true);
		
		/*--------------------------------------------------------------CREATE GAMEOBJECT------------------------------------------------------------------------------------------------------- */

		Text* orderNoText = new Text("orderNo", "1", "Assets/Fonts/mvboli.ttf", true);
		m_gameObjects.push_back(orderNoText);

		/*--------------------------------------------------------------CREATE BUTTONS------------------------------------------------------------------------------------------------------- */

		ServeBellButton = new UIButton("ServeBellButton", "Assets/Images/Kitchen/ServeButton_servable_default.png", glm::vec3(-4.9f, -2.6f, 0.0f), glm::vec3(2.02f, 1.45f, 0.0f), true, false);
		ServeBellButton->setActiveStatus(false);
		ServeBellButton->SetOnClickAction([this]() { Serve(); });

		ServeBellGrey = new UIObject("ServeBellGrey", "Assets/Images/Kitchen/ServeButton_notServable_default.png", true);
		ServeBellGrey->SetPosition(glm::vec3(-4.9f, -2.6f, 0.0f));
		ServeBellGrey->SetScale(glm::vec3(2.02f, 1.45f, 0.0f));

		/*--------------------------------------------------------------CREATE FOOD DRAGGABLES------------------------------------------------------------------------------------------------------- */

		AssamBlackTea = new UIDraggable("AssamBlackTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Assam.png", glm::vec3(1.0f, 0.02f, 0.0f), glm::vec3(1.2f, 1.6f, 0.0f), true);
		EarlGreyTea = new UIDraggable("EarlGreyTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Earl.png", glm::vec3(2.3f, 0.02f, 0.0f), glm::vec3(1.2f, 1.6f, 0.0f), true);
		GreenTea = new UIDraggable("GreenTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Green.png", glm::vec3(3.6f, 0.0f, -0.1f), glm::vec3(1.3f, 1.5f, 0.0f), true);
		ChamomileTea = new UIDraggable("ChamomileTea", "Assets/Images/Kitchen/Food/Tea/TeaBox_Chamomile.png", glm::vec3(4.8f, 0.1f, 0.0f), glm::vec3(1.1f, 1.75f, 0.0f), true);

		SalmonSandwhich = new UIDraggable("SalmonSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Icon_Salmon.png", glm::vec3(1.38f, -2.24f, 0.0f), glm::vec3(2.08f, 1.15f, 0.0f), true);
		EggSandwhich = new UIDraggable("EggSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Icon_Egg.png", glm::vec3(3.7f, -2.35f, 0.0f), glm::vec3(2.23f, 0.92f, 0.0f), true);
		CucumberSandwhich = new UIDraggable("CucumberSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Icon_Cucumber.png", glm::vec3(5.4f, -2.28f, 0.0f), glm::vec3(1.86f, 1.03f, 0.0f), true);
		BeefSandwhich = new UIDraggable("BeefSandwhich", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Icon_Beef.png", glm::vec3(7.55f, -2.35f, 0.0f), glm::vec3(2.0f, 0.9f, 0.0f), true);

		Eclair = new UIDraggable("Eclair", "Assets/Images/Kitchen/Food/Dessert/Dessert_Icon_Eclair.png", glm::vec3(1.5f, -4.42f, 0.0f), glm::vec3(2.0f, 0.7f, 0.0f), true);
		LemonTart = new UIDraggable("LemonTart", "Assets/Images/Kitchen/Food/Dessert/Dessert_Icon_LemonTart.png", glm::vec3(3.5f, -4.37f, 0.0f), glm::vec3(1.45f, 0.83f, 0.0f), true);
		Scone = new UIDraggable("Scone", "Assets/Images/Kitchen/Food/Dessert/Dessert_Icon_Scone.png", glm::vec3(5.2f, -4.4f, 0.0f), glm::vec3(1.46f, 0.7f, 0.0f), true);
		Macaron = new UIDraggable("Macaron", "Assets/Images/Kitchen/Food/Dessert/Dessert_Icon_Macaron.png", glm::vec3(7.3f, -4.38f, 0.0f), glm::vec3(2.0f, 0.77f, 0.0f), true);

		/*--------------------------------------------------------------SET DRAGGABLE FOOD FUNCTIONS------------------------------------------------------------------------------------------------------- */

		AssamBlackTea->SetOnReleaseAction([this]() { releaseAssam(); });
		EarlGreyTea->SetOnReleaseAction([this]() { releaseEarlGrey(); });
		GreenTea->SetOnReleaseAction([this]() { releaseGreenTea(); });
		ChamomileTea->SetOnReleaseAction([this]() { releaseChamomileTea(); });

		SalmonSandwhich->SetOnReleaseAction([this]() { releaseSalmonSandwhich(); });
		EggSandwhich->SetOnReleaseAction([this]() { releaseEggSandwhich(); });
		CucumberSandwhich->SetOnReleaseAction([this]() { releaseCucumberSandwhich(); });
		BeefSandwhich->SetOnReleaseAction([this]() { releaseBeefSandwhich(); });

		Eclair->SetOnReleaseAction([this]() { releaseEclair(); });
		LemonTart->SetOnReleaseAction([this]() { releaseLemonTart(); });
		Scone->SetOnReleaseAction([this]() { releaseScone(); });
		Macaron->SetOnReleaseAction([this]() { releaseMacaron(); });

		/*-------------------------------------------------------------- CREATE PLATED FOOD ------------------------------------------------------------------------------------------------------- */

		GameObject* AssamBlack_dish = new UIObject("AssamBlackDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Assam.png", true);
		AssamBlack_dish->SetPosition(TeaDishPosition);
		AssamBlack_dish->SetScale(glm::vec3(1.2f, 1.6f, 0.0f));

		GameObject* EarlGreyTea_dish = new UIObject("EarlGreyDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Earl.png", true);
		EarlGreyTea_dish->SetPosition(TeaDishPosition);
		EarlGreyTea_dish->SetScale(glm::vec3(1.2f, 1.6f, 0.0f));

		GameObject* GreenTea_dish = new UIObject("GreenTeaDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Green.png", true);
		GreenTea_dish->SetPosition(TeaDishPosition);
		GreenTea_dish->SetScale(glm::vec3(1.3f, 1.5f, 0.0f));

		GameObject* ChamomileTea_dish = new UIObject("ChamomileTeaDish", "Assets/Images/Kitchen/Food/Tea/TeaBox_Chamomile.png", true);
		ChamomileTea_dish->SetPosition(TeaDishPosition);
		ChamomileTea_dish->SetScale(glm::vec3(1.1f, 1.75f, 0.0f));

		GameObject* SalmonDish = new UIObject("SalmonDish", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Salmon.png", true);
		SalmonDish->SetPosition(SandwhichDishPosition);
		SalmonDish->SetScale(glm::vec3(2.35f, 1.28f, 0.0f));

		GameObject* EggDish = new UIObject("EggDish", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Egg.png", true);
		EggDish->SetPosition(SandwhichDishPosition);
		EggDish->SetScale(glm::vec3(2.61f, 1.14f, 0.0f));

		GameObject* CucumberDish = new UIObject("CucumberDish", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Cucumber.png", true);
		CucumberDish->SetPosition(SandwhichDishPosition);
		CucumberDish->SetScale(glm::vec3(2.23f, 1.25f, 0.0f));

		GameObject* BeefDish = new UIObject("BeefDish", "Assets/Images/Kitchen/Food/Sandwhich/Sandwich_Beef.png", true);
		BeefDish->SetPosition(SandwhichDishPosition);
		BeefDish->SetScale(glm::vec3(2.21f, 1.02f, 0.0f));

		GameObject* EclairDish = new UIObject("EclairDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_Eclair.png", true);
		EclairDish->SetPosition(DessertDishPosition);
		EclairDish->SetScale(glm::vec3(2.6f, 0.8f, 0.0f));

		GameObject* LemonTartDish = new UIObject("LemonTartDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_LemonTart.png", true);
		LemonTartDish->SetPosition(DessertDishPosition);
		LemonTartDish->SetScale(glm::vec3(2.08f, 0.97f, 0.0f));

		GameObject* SconeDish = new UIObject("SconeDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_Scone.png", true);
		SconeDish->SetPosition(DessertDishPosition);
		SconeDish->SetScale(glm::vec3(1.7f, 0.75f, 0.0f));

		GameObject* MacaronDish = new UIObject("MacaronDish", "Assets/Images/Kitchen/Food/Dessert/Dessert_Macaron.png", true);
		MacaronDish->SetPosition(DessertDishPosition);
		MacaronDish->SetScale(glm::vec3(2.6f, 0.8f, 0.0f));

		/*--------------------------------------------------------------PUSH BACK------------------------------------------------------------------------------------------------------- */

		m_gameObjects.push_back(KitchenBackground);
		m_gameObjects.push_back(ServeBellButton);
		m_gameObjects.push_back(ServeBellGrey);
		m_gameObjects.push_back(orderPaper);

		//PLATED FOOD GAMEOBJECTS

		platedTea[ASSAMTEA] = AssamBlack_dish;
		platedTea[EARLGREYTEA] = EarlGreyTea_dish;
		platedTea[GREENTEA] = GreenTea_dish;
		platedTea[CHAMOMILETEA] = ChamomileTea_dish;

		platedSandwhich[SALMON] = SalmonDish;
		platedSandwhich[EGG] = EggDish;
		platedSandwhich[CUCUMBER] = CucumberDish;
		platedSandwhich[BEEF] = BeefDish;

		platedDessert[ECLAIR] = EclairDish;
		platedDessert[TART] = LemonTartDish;
		platedDessert[SCONE] = SconeDish;
		platedDessert[MACARON] = MacaronDish;

		m_gameObjects.push_back(AssamBlack_dish);
		m_gameObjects.push_back(EarlGreyTea_dish);
		m_gameObjects.push_back(GreenTea_dish);
		m_gameObjects.push_back(ChamomileTea_dish);

		m_gameObjects.push_back(SalmonDish);
		m_gameObjects.push_back(EggDish);
		m_gameObjects.push_back(CucumberDish);
		m_gameObjects.push_back(BeefDish);

		m_gameObjects.push_back(EclairDish);
		m_gameObjects.push_back(LemonTartDish);
		m_gameObjects.push_back(SconeDish);
		m_gameObjects.push_back(MacaronDish);


		//DRAGGABLE FOOD	
		m_gameObjects.push_back(AssamBlackTea);
		m_gameObjects.push_back(EarlGreyTea);
		m_gameObjects.push_back(GreenTea);
		m_gameObjects.push_back(ChamomileTea);

		m_gameObjects.push_back(SalmonSandwhich);
		m_gameObjects.push_back(EggSandwhich);
		m_gameObjects.push_back(CucumberSandwhich);
		m_gameObjects.push_back(BeefSandwhich);

		m_gameObjects.push_back(Eclair);
		m_gameObjects.push_back(LemonTart);
		m_gameObjects.push_back(Scone);
		m_gameObjects.push_back(Macaron);

		m_gameObjects.push_back(platePositionArea);


		//set all plate gameobjects as inactive
		clearPlate();

	}

	void Update(float dt, long frame) override {

		Scene::Update(dt, frame);

		if (input.Get().GetKeyDown(GLFW_KEY_E)) {
			Application::Get().SetScene("Hallway");
		}

		if (input.Get().GetKeyDown(GLFW_KEY_R)) { //RESET KITCHEN
			clearPlate();
		}

		updateServeButton();

	}


	void clearPlate() {

		//set all as inactive

		for (int i = 0; i < 4; i++) {
			platedTea[i]->setActiveStatus(false);
		}
		for (int i = 0; i < 4; i++) {
			platedSandwhich[i]->setActiveStatus(false);
		}
		for (int i = 0; i < 4; i++) {
			platedDessert[i]->setActiveStatus(false);
		}

		KitchenData::GetInstance()->clearPlate();

	}

	void updateSandwhichStatus() {

		for (int i = 0; i < 4; i++) {
			if (i == KitchenData::GetInstance()->getSandwhich()) {
				platedSandwhich[i]->setActiveStatus(true);
			}
			else {
				platedSandwhich[i]->setActiveStatus(false);
			}
		}

	}

	void updateDessertStatus() {


		for (int i = 0; i < 4; i++) {
			if (i == KitchenData::GetInstance()->getDessert()) {
				platedDessert[i]->setActiveStatus(true);
			}
			else {
				platedDessert[i]->setActiveStatus(false);
			}
		}

	}

	void updateTeaStatus() {


		for (int i = 0; i < 4; i++) {
			if (i == KitchenData::GetInstance()->getTea()) {
				platedTea[i]->setActiveStatus(true);
			}
			else {
				platedTea[i]->setActiveStatus(false);
			}
		}

	}

	//ON RELEASE FUNCTIONS

	void releaseAssam() {

		std::cout << platePositionArea->GetPosition().x  << platePositionArea->GetPosition().y << std::endl;
		if (AssamBlackTea->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setTea(ASSAMTEA);
			updateTeaStatus();
		}
	}

	void releaseEarlGrey() {

		//std::cout << "EARL GREY RELEASED" << std::endl;
		if (EarlGreyTea->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setTea(EARLGREYTEA);
			updateTeaStatus();
		}
	}

	void releaseGreenTea() {

		//std::cout << "GREEN TEA RELEASED" << std::endl;
		if (GreenTea->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setTea(GREENTEA);
			updateTeaStatus();
		}
	}

	void releaseChamomileTea() {

		//std::cout << "CHAMOMILE TEA RELEASED" << std::endl;
		if (ChamomileTea->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setTea(CHAMOMILETEA);
			updateTeaStatus();
		}
	}

	void releaseSalmonSandwhich() {

		//std::cout << "SALMON SANDWHICH RELEASED" << std::endl;
		if (SalmonSandwhich->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(SALMON);
			updateSandwhichStatus();
		}
	}

	void releaseEggSandwhich() {

		//std::cout << "EGG SANDWHICH RELEASED" << std::endl;
		if (EggSandwhich->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(EGG);
			updateSandwhichStatus();
		}
	}

	void releaseCucumberSandwhich() {

		//std::cout << "CUCUMBER SANDWHICH RELEASED" << std::endl;
		if (CucumberSandwhich->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(CUCUMBER);
			updateSandwhichStatus();
		}
	}

	void releaseBeefSandwhich() {

		//std::cout << "BEEF SANDWHICH RELEASED" << std::endl;
		if (BeefSandwhich->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setSandwhich(BEEF);
			updateSandwhichStatus();
		}
	}

	void releaseEclair() {

		//std::cout << "ECLAIR RELEASED" << std::endl;
		if (Eclair->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setDessert(ECLAIR);
			updateDessertStatus();
		}
	}

	void releaseLemonTart() {

		//std::cout << "LEMON TART RELEASED" << std::endl;
		if (LemonTart->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setDessert(TART);
			updateDessertStatus();
		}
	}

	void releaseScone() {

		//std::cout << "SCONE RELEASED" << std::endl;
		if (Scone->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
			KitchenData::GetInstance()->setDessert(SCONE);
			updateDessertStatus();
		}
	}

	void releaseMacaron() {

		//std::cout << "MACARON RELEASED" << std::endl;
		if (Macaron->withinRage(platePositionArea->GetOnscreenPosition(), snapThreshold)) {
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

	UIDraggable* AssamBlackTea;
	UIDraggable* EarlGreyTea;
	UIDraggable* GreenTea;
	UIDraggable* ChamomileTea;
	UIDraggable* SalmonSandwhich;
	UIDraggable* EggSandwhich;
	UIDraggable* CucumberSandwhich;
	UIDraggable* BeefSandwhich;
	UIDraggable* Eclair;
	UIDraggable* LemonTart;
	UIDraggable* Scone;
	UIDraggable* Macaron;

	UIButton* ServeBellButton;
	GameObject* ServeBellGrey;


	//Array of plated game objects
	GameObject* platedSandwhich[4];
	GameObject* platedDessert[4];
	GameObject* platedTea[4];

	const glm::vec3 TeaDishPosition = glm::vec3(-7.5f, -0.4f, 0.0f);
	const glm::vec3 SandwhichDishPosition = glm::vec3(-5.1f, -0.5f, 0.0f);
	const glm::vec3 DessertDishPosition = glm::vec3(-2.4f, -0.6f, 0.0f);

	//within range

	glm::vec3 platePosition = glm::vec3(-5.5f, 0.0f, 0.0f);



	const float snapThreshold = 4.0f;


};
