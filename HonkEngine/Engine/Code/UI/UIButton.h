#pragma once

#include "../UI/UIElement.h"

#include "../Scene/Hallway.h"


class UIButton : public UIElement {

	public:

      

        UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen)
            : UIElement(name, texturePath, position, scale, isOnScreen) {

            //Additional properties specific to buttons

            isClickable = true;
            //category = UIcategory;

        }

        // Method to set the click action
        void SetOnClickAction(const std::function<void()>& action) {
            onClickAction = action;
        }


        void OnClick(){

            if (onClickAction) {
                onClickAction();
            }

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

        bool isClickable;
        glm::vec2 mousePos;
        std::function<void()> onClickAction;


};