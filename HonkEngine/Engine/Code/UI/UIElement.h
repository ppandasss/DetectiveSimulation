#pragma once

#include "../GameObjects/RenderGameObject.h"
#include "Application.h"
#include "../Scene/Scene.h"
#include "../Input/Input.h"
#include "Engine.h"

class UIElement : public RenderGameObject {

	public:

		enum UICategory {
			BOOK_PAGE1,
			BOOK_PAGE2,
			IN_GAME, //journal access button etc.
			PAUSED,
			//Add more stages as needed
		};

		UIElement(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, UICategory UIcategory) : RenderGameObject(name, texturePath) {
			
			SetPosition(glm::vec3(position.x, position.y, 0.0f));
			SetScale(glm::vec3(scale.x, scale.y, 0.0f));
			button_name = name;
			isClickable = true;
			category = UIcategory;

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

		bool IsPointInside(float x, float y) const {

			float xpos = x - 800.0f / 2.0f;
			float ypos = 600.0f / 2.0f - y;

			float minX = m_position.x - (m_scale.x / 2.0f);
			float maxX = m_position.x + (m_scale.x / 2.0f);
			float minY = m_position.y - (m_scale.y / 2.0f);
			float maxY = m_position.y + (m_scale.y / 2.0f);

			//std::cout << "winX: " << GetWindowWidth() << " winy: " << GetWindowHeight() << std::endl;

			std::cout << "maxX: " << maxX << " minX: " << minX << std::endl;
			std::cout << "maxY: " << maxY << " minY: " << minY << std::endl;
			std::cout << "x: " << x << " y: " << y << std::endl;
			std::cout << "new xpos: " << xpos << " new ypos: " << ypos << std::endl;

			return (xpos >= minX && xpos <= maxX && ypos >= minY && ypos <= maxY);

		}


		//Implement cleanup logic for UI elements
		//virtual void Clear() override {}
		
	
	private:
		std::string button_name;
		bool isClickable;
		UICategory category;


};