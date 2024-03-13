#pragma once

#include "UIButton.h"

class UIButtonEmpty: public UIButton {

	public:

        UIButtonEmpty(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, bool containText)
            : UIButton(name, texturePath, position, scale, isOnScreen, containText) {


        }

           
        //Comment render out to draw texture to test sizing
        void Render() override {

            //override to not draw texture

            RenderText();    

        }

        void Update(float dt, long frame) override {

            UIButton::Update(dt, frame);
            
        }

        void SetOnClickAction(const std::function<void()>& action) override {
            onClickAction = action;
        }

        void OnClick() override {
            if (onClickAction) {
                onClickAction();
            }
        }

    protected:
        std::function<void()> onClickAction;


};
