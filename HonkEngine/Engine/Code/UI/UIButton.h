#pragma once

#include "../UI/UIElement.h"

#include "../Scene/Hallway.h"

#include <glm/gtx/string_cast.hpp>



class UIButton : public UIElement {

	public:
        
        UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, bool containText, const std::string& fontPath)
            : UIElement(name, texturePath, position, scale, isOnScreen), buttonPosition(position), buttonScale(scale) {
            isClickable = true;

            if (containText) {
                buttonTextObj = new Text("ButtonText", "Placeholder", fontPath, true);
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

        std::string matrixToString(const glm::mat4& matrix) {
            std::stringstream ss;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    ss << matrix[i][j] << " ";
                }
                ss << std::endl;
            }
            return ss.str();
        }


     
        void Update(float dt, long frame) override {
            Input& input = Application::GetInput();

            UIElement::Update(dt, frame);

            if (containsText) {
                buttonTextObj->Update(dt, frame);
            }

            mousePosWorld = Application::Get().MousetoWorld();

            if (IsClickable() && IsPointInside(mousePosWorld.x, mousePosWorld.y)) {
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

            UIElement::Render(); // Render the button texture using the transformation matrix from UIObject
            if (containsText) {
                buttonTextObj->Render(); // Render the button text
            }
        }

        void SetButtonPosition(const glm::vec3& position) {

            //std::cout << "SetButtonPosition - Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
            UIElement::SetPosition(position); // Update the position in UIObject
            
        }

        void SetButtonScale(const glm::vec3& scale) {

           // std::cout << "SetButtonScale - Scale: " << scale.x << ", " << scale.y << ", " << scale.z << std::endl;
            UIElement::SetScale(scale); // Update the scale in UIObject
            // Optionally, you can also scale the text here if needed
        }

        void SetButtonText(const std::string& buttonText) {
            buttonTextObj->SetContent(buttonText);
        }

        void SetTextSize(float scale) {
            buttonTextObj->SetScale(scale);
        }

        void SetTextPosition(glm::vec3 position) {
            buttonTextObj->SetPosition(position);
        }

        void SetTextColor(glm::vec3 colour) {
			buttonTextObj->SetColor(colour);
		}



    private:
        glm::vec3 buttonPosition;
        glm::vec3 buttonScale;
        Text* buttonTextObj;
        bool containsText = true;
        bool isClickable;     
        glm::vec2 mousePosWorld;
        std::function<void()> onClickAction;
        
};