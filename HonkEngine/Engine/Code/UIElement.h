#pragma once

#include "RenderGameObject.h"

class UIElement : public RenderGameObject {

	public:

		UIElement(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) : RenderGameObject(name, texturePath) {
			
			SetPosition(glm::vec3(position.x, position.y, 0.0f));
			SetScale(glm::vec3(scale.x, scale.y, 0.0f));

			isClickable = true;

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



		// Implement cleanup logic for UI elements
		virtual void Clear() override {

		}
		
	
	private:
		bool isClickable;

};