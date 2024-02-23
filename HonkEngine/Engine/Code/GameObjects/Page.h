#pragma once

#include "GameObject.h"
#include "../Engine.h"
#include "../Input/Input.h"
#include <iostream>
#include "../Application.h"

#include "../Text/Text.h"
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"

#include "JournalData.h"


class Page: public GameObject{

public:

	JournalData* journalDataObj;

	Page() : GameObject("page") {

		
	}



	virtual void Render() override
	{

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Render();

			}

		}

	}

	virtual void Update(float dt, long frame) override {

		for (auto& object : m_gameObjects) {

			if (object->getActiveStatus()) { //CHECK ACTIVE STATUS

				object->Update(dt, frame);

			}

		}


	}

	virtual void setActiveStatus(bool status) { 

		for (auto& object : m_gameObjects) {

			object->setActiveStatus(status);

		}

		active = status;
	
	}


protected:

	std::vector<GameObject*> m_gameObjects;

};