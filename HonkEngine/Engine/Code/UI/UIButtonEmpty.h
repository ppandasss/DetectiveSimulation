#pragma once

#include "UIButton.h"

class UIButtonEmpty: public UIButton {

	public:

        UIButtonEmpty(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen)
            : UIButton(name, texturePath, position, scale, isOnScreen) {

        }

           
        //Comment render out to draw texture to test sizing
        void Render() override {

        }

        void Update(float dt, long frame) override {

            UIButton::Update(dt, frame);
            
        }


};
