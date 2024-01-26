#pragma once

#include "../GameObjects/RenderGameObject.h"
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>


class UIElement : public RenderGameObject {


public:

	enum UICategory {
		BOOK_PAGE1,
		BOOK_PAGE2,
		IN_GAME, //journal access button etc.
		PAUSED,
		//Add more stages as needed
	};

	UIElement(const std::string& name, const std::string& texturePath, glm::vec3 position, glm::vec3 scale) : RenderGameObject(name, texturePath, position) {

		m_scale = scale;
		button_name = name;
		isClickable = true;
		//category = UIcategory;

	}


	virtual void Update(float dt, long frame) override {

		RenderGameObject::Update(dt, frame);

		// Implement UI-specific update logic here
		// For example, handling UI animations, interactions, etc

	}

	virtual void OnClick() = 0;

	bool IsClickable() {
		return isClickable;
	}

	void SetClickable(bool clickable) {
		isClickable = clickable;
	}


	glm::vec2 MousetoScreen(float x, float y) const {

		float xpos = x - (SCR_WIDTH / 2.0f);
		float ypos = y - (SCR_HEIGHT / 2.0f);

		xpos = xpos * 16.0 / SCR_WIDTH;
		ypos = ypos * 9.0 / SCR_HEIGHT * -1;

		return glm::vec2(xpos, ypos);

	}

	bool IsPointInside(float x, float y) const {

		glm::vec2 newPos = MousetoScreen(x, y);

		float minX = m_position.x - (m_scale.x / 2.0f );
		float maxX = m_position.x + (m_scale.x / 2.0f);
		float minY = m_position.y - (m_scale.y / 2.0f );
		float maxY = m_position.y + (m_scale.y / 2.0f);

		
		/*
		std::cout << "x: " << x << " y: " << y << std::endl;
		std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;

		std::cout << "new xpos: " << xpos << " new ypos: " << ypos << std::endl;
		std::cout << "obj x: " << m_position.x << "obj y: " << m_position.y << std::endl;
		std::cout << "maxX: " << maxX << " minX: " << minX << std::endl;
		std::cout << "maxY: " << maxY << " minY: " << minY << std::endl;
		*/

		return (newPos.x >= minX && newPos.x <= maxX && newPos.y >= minY && newPos.y <= maxY);

	}


	//Implement cleanup logic for UI elements
	//virtual void Clear() override {}


private:
	std::string button_name;
	bool isClickable;
	//UICategory category;

};
