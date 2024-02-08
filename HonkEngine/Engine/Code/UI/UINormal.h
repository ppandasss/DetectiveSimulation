#pragma once

#include "../UI/UIElement.h"

class UINormal : public UIElement {
public:
    UINormal(const std::string& name, const std::string& texturePath, glm::vec3 position, glm::vec3 scale,bool isOnScreen)
        : UIElement(name, texturePath, position, scale,isOnScreen) {}

    void OnClick() override {
        // Implement any specific behavior for normal UI
        std::cout << "UINormal Clicked!" << std::endl;
    }

    // You can add more functions or behavior specific to UINormal if needed
};