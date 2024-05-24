#pragma once

#include "GameObject.h"
#include "../Engine.h"
#include "../Input/Input.h"
#include <iostream>
#include "../Application.h"

#include "../Text/Text.h"
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../UI/UIButtonEmpty.h"

#include "JournalData.h"


class Page : public GameObject {

public:


	Page(Cabin cabinType) : GameObject("page"), cabinType(cabinType) {}


	virtual void Render() override
	{

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		for (size_t i = 0; i < textClues.size(); ++i) {

			if (m_journalData->GetClueState(cabinType, i)) {

				textClues[i]->Render();

			}
		}

		for (auto& object : deffered_m_gameObjects) {

			if (object->showObject) { //CHECK ACTIVE STATUS

				object->gameObj->Render();

			}

		}


	}

	virtual void Update(float dt, long frame) override {

		//Update from last object to first
		//top layer to bottom

		for (auto it = m_gameObjects.rbegin(); it != m_gameObjects.rend(); ++it) {

			GameObject* object = *it;
			if (object->getActiveStatus()) { // CHECK ACTIVE STATUS
				object->Update(dt, frame);
			}

		}

		for (auto& object : textClues) {

			object->Update(dt, frame);

		}

		for (auto& object : deffered_m_gameObjects) {

			if (object->showObject) {
				object->gameObj->Update(dt, frame);
			}

		}

	}

	virtual void setActiveStatus(bool status) {

		for (auto& object : m_gameObjects) {
			object->setActiveStatus(status);
		}

		for (auto& object : textClues) {

			if (object) { //checks for nullptr		

			}
		}

		for (auto& object : deffered_m_gameObjects) {

			if (object->gameObj) { //checks for nullptr

				if (object->showObject) {
					object->gameObj->setActiveStatus(status); //sets status accordingly if clue is active
				}
				else {
					object->gameObj->setActiveStatus(false); //if inactive always set as false
				}

			}
		}

		active = status;

	}

	void ResetPage() {

		for (auto& object : deffered_m_gameObjects) {
			if (object->gameObj) { //checks for nullptr
				object->showObject = false;
				object->gameObj->setActiveStatus(false);
			}
		}

	}


protected:

	Cabin cabinType;

	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> textClues;
	std::vector<DeferredRenderObject*> deffered_m_gameObjects;

	JournalData* m_journalData = JournalData::GetInstance();

};