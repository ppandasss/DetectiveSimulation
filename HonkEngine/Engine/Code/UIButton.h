#pragma once
#include "UIElement.h"

class UIButton : public UIElement {

	public:
		UIButton(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale) :
			UIElement(name, texturePath, position, scale) {

			//addition properties that are specific to buttons
		}

		virtual void OnClick() {

		}


};
