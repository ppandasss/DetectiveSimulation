#pragma once

#include "../UI/UIElement.h"


class UIButton : public UIElement {

	public:
        UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale,bool isOnScreen)
            : UIElement(name, texturePath, position, scale,isOnScreen) {

            // Additional properties specific to buttons

            isClickable = true;
            //category = UIcategory;

        }

        void OnClick(){

            std::cout << "Button Clicked" << std::endl;
        }


        void Update(float dt, long frame) override {

            Input& input = Application::GetInput();
            UIElement::Update(dt, frame);
            
                
                mousePos = Application::Get().CursorPos();

                if (IsClickable() && IsPointInside(mousePos.x, mousePos.y)) {

                    //std::cout << " BUTTON UPDATE" << std::endl;

                    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                        OnClick();

                    }

                }  

        }
  

    private:

        std::string button_name;
        bool isClickable;
        //UICategory category;
        glm::vec2 mousePos;


};