#pragma once

#include "../GameObjects/GameObject.h"
#include "../Engine.h"
#include "../Input/Input.h"
#include <iostream>
#include "../Application.h"

#include "../GameObjects/JournalData.h"

class PopUp: public GameObject {	

public:

	PopUp() : GameObject("PopUp") {}


	virtual void Render() override
	{
		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

		for (auto& object : deffered_m_gameObjects) {

			if (object->showObject) {

				object->gameObj->Render();

			}

		}
	}

	virtual void Update(float dt, long frame) override {

		//Update from last object to first (top layer to bottom)

		for (auto it = m_gameObjects.rbegin(); it != m_gameObjects.rend(); ++it) {
			GameObject* object = *it;
			if (object->getActiveStatus()) { // CHECK ACTIVE STATUS
				object->Update(dt, frame);
			}
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
	std::vector<DeferredRenderObject*> deffered_m_gameObjects;

};
