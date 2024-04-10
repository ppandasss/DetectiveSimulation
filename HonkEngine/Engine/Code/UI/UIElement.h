#pragma once

#include "UIObject.h"
#include "../Input/Input.h"
#include "../Engine.h"
#include <glm/glm.hpp>
#include <iostream>

class UIElement : public UIObject {

public:


    UIElement(const std::string& name, const std::string& texturePath, glm::vec3 position, glm::vec3 scale,bool isOnScreen) : UIObject(name, texturePath, position,isOnScreen) {

        m_scale = scale;
        button_name = name;
        isClickable = true;
        offset = position;

    }



    virtual void Update(float dt, long frame) override {

        if (getActiveStatus()) {
            UIObject::Update(dt, frame);
        }

    }

    virtual void Render() override {

		UIObject::Render();

	}

    virtual void OnClick() = 0;

    bool IsClickable() {

        if (this->getActiveStatus()) {
            return isClickable;
        }
        else {
            return false;
        }

        
    }

    void SetClickable(bool clickable) {
        isClickable = clickable;
    }

    std::string getButtonName() {

        return button_name;

    }

    //Implement cleanup logic for UI elements
    //virtual void Clear() override {}

private:
    std::string button_name;
    bool isClickable;
    glm::vec3 offset;
    bool isOnScreen;
    //UICategory category;
    //Camera& camera = Application::GetCamera();
};

