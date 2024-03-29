#pragma once

#include "UIButton.h"

class UIButtonEmpty: public UIButton {

	public:
        
        UIButtonEmpty(const std::string& name, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, bool containText, const std::string& fontPath)
            : UIButton(name, "" , position, scale, isOnScreen, containText, fontPath) {
            //don't need to include texture path
            //no text -> fontpath = ""

        }

           
        //Comment render out to draw texture to test sizing
        void Render() override {

            //override Render to not draw texture
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
