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


	Page() : GameObject("page") {}


	virtual void Render() override
	{

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		for (auto& object : textClues) {

			if (object->showText) { //CHECK ACTIVE STATUS

				object->clueText->Render();

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

			object->clueText->Update(dt, frame);

		}

		for (auto& object : deffered_m_gameObjects) {

			object->gameObj->Update(dt, frame);

		}

	}

	virtual void setActiveStatus(bool status) {

		for (auto& object : m_gameObjects) {

			object->setActiveStatus(status);

		}


		for (auto& object : textClues) {

			if (object->clueText) { //checks for nullptr

				if (object->showText) {
					object->clueText->setActiveStatus(status); //sets status accordingly if clue is active
				}
				else {
					object->clueText->setActiveStatus(false); //if inactive always set as false
				}

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


protected:

	std::vector<GameObject*> m_gameObjects;

	std::vector<ClueData*> textClues;

	std::vector<DeferredRenderObject*> deffered_m_gameObjects;

	JournalData* m_journalData = JournalData::GetInstance();

};