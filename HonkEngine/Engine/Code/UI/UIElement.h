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
        //category = UIcategory;

    }



    virtual void Update(float dt, long frame) override {

        if (IsActive()) {
            UIObject::Update(dt, frame);
        }

    }

    virtual void Render() override {

		UIObject::Render();

	}

    virtual void OnClick() = 0;

    bool IsClickable() {
        return isClickable;
    }

    void SetClickable(bool clickable) {
        isClickable = clickable;
    }

    void SetActive(bool active) {
        this->active = active;
    }

    bool IsActive() const {
        return active;
    }

    std::string getButtonName() {

        return button_name;

    }

    //Implement cleanup logic for UI elements
    //virtual void Clear() override {}

private:
    bool active = true;
    std::string button_name;
    bool isClickable;
    glm::vec3 offset;
    bool isOnScreen;
    //UICategory category;
    //Camera& camera = Application::GetCamera();
};
// Assuming GetCamera is a static method in your Application class
