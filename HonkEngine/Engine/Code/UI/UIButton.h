#pragma once

#include "../UI/UIElement.h"

#include "../Scene/Hallway.h"


class UIButton : public UIElement {

	public:
        
        UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, bool containText)
            : UIElement(name, texturePath, position, scale, isOnScreen) {

            isClickable = true;

            // Initialize the text object with an empty content
            if (containText) {
                buttonTextObj->SetPosition(position);
            }

            containsText = containText;
           
        }

        //Method to set the click action
        virtual void SetOnClickAction(const std::function<void()>& action) {
            onClickAction = action;
        }


        void OnClick() override {

            if (onClickAction) {
                onClickAction();
            }

        }

     
        void Update(float dt, long frame) override {

            Input& input = Application::GetInput();
            UIElement::Update(dt, frame);

            if (containsText) {
                buttonTextObj->Update(dt, frame);
            }

                mousePosWorld = Application::Get().MousetoWorld();


                if (IsClickable() && IsPointInside(mousePosWorld.x, mousePosWorld.y)) {

                    //std::cout << " BUTTON UPDATE" << std::endl;

                    if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                        OnClick();

                    }
                }  
        }

        void RenderText() {

            if (containsText) {
                buttonTextObj->Render(); // Render the button text
            }

        }

        void Render() override {
            UIElement::Render(); // Render the button texture     

        }

        void setButtonText(const std::string& buttonText) {
            buttonTextObj->SetContent(buttonText);
        }
       


    private:
        Text* buttonTextObj = new Text("ButtonText", "hiiii", "Assets/Fonts/ESA-m.ttf", true);
        bool containsText = true;
        bool isClickable;
        glm::vec2 mousePos;
        glm::vec2 mousePosWorld;
        std::function<void()> onClickAction;
        
};