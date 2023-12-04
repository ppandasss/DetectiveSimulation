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

    virtual void Update() {





    }


};
