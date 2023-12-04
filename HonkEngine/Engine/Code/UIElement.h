#pragma once

#include "RenderGameObject.h"

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
		
			// Implement UI-specific update logic here
			// For example, handling UI animations, interactions, etc

		}  

		virtual void OnClick() {};

		bool IsClickable() {
			return isClickable;
		}

		void SetClickable(bool clickable) {
			isClickable = clickable;
		}

		bool IsPointInside(float x, float y) const {

			float minX = m_position.x - (m_scale.x / 2.0f);
			float maxX = m_position.x + (m_scale.x / 2.0f);
			float minY = m_position.y - (m_scale.y / 2.0f);
			float maxY = m_position.y + (m_scale.y / 2.0f);

			return (x >= minX && x <= maxX && y >= minY && y <= maxY);

		}


		// Implement cleanup logic for UI elements
		//virtual void Clear() override {}
		
	
	private:
		std::string button_name;
		bool isClickable;
		UICategory category;

};