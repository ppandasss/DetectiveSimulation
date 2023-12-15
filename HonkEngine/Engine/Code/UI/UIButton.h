#pragma once
#include "UIElement.h"

class UIButton : public UIElement {

public:
    UIButton(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, UICategory UIcategory)
        : UIElement(name, texturePath, position, scale, UIcategory) {
        // Additional properties specific to buttons
    }

    virtual void OnClick() {

        std::cout << "Button Clicked" << std::endl;
    }

       void Update(float dt, long frame) override {

		Input& input = Application::GetInput();

	    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		{   

            std::cout << IsClickable() << std::endl;
            
            mousePos = Application::Get().CursorPos();

            std::cout << "x objpos: " << m_position.x << "y objpos: " << m_position.y << std::endl;

            //IsPointInside(mousePos.x, mousePos.y);
            //std::cout << "button clicked" << std::endl;


            if (IsClickable() && IsPointInside(mousePos.x, mousePos.y)) {

                //std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
                std::cout << "Button Clicked" << std::endl;

            }

            
		}


    }

    private:
        glm::vec2 mousePos;


};
