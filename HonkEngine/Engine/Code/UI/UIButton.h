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

        //Method to set the click action
        void SetOnClickAction(const std::function<void()>& action) {
            onClickAction = action;
        }


        void OnClick(){

            if (onClickAction) {
                onClickAction();
            }

        }

       /* void(*clickfunc)();

        void BindOnClick(void(*newfunc)())
        {
            clickfunc = newfunc;
        }

        void OnClick() {
            clickfunc();
        }*/

     
        void Update(float dt, long frame) override {

            Input& input = Application::GetInput();
            UIElement::Update(dt, frame);
            
                mousePosWorld = Application::Get().MousetoWorld();


                if (IsClickable() && IsPointInside(mousePosWorld.x, mousePosWorld.y)) {

                    //std::cout << " BUTTON UPDATE" << std::endl;

                    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                        OnClick();

                    }
                }  
        }
 
    private:

        bool isClickable;
        glm::vec2 mousePos;
        glm::vec2 mousePosWorld;
        std::function<void()> onClickAction;


};