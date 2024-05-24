#pragma once

#include "../UI/UIElement.h"
#include "../Text/Text.h"
#include "../Application.h"
#include <functional>
#include <sstream>

class UIButton : public UIElement {

public:

    UIButton(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, bool containText, const std::string& fontPath = "")
        : UIElement(name, texturePath, position, scale, isOnScreen), buttonPosition(position), buttonScale(scale) {
        isClickable = true;

        if (containText) {
            buttonTextObj = new Text("ButtonText", "Placeholder", fontPath, true);
            buttonTextObj->SetPosition(position);
        }

        containsText = containText;
        hasTexture = !texturePath.empty();
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

        if (getActiveStatus()) {

            if (containsText) {
                buttonTextObj->Update(dt, frame);
            }

            mousePosWorld = Application::Get().MousetoWorld();

            if (IsClickable() && IsPointInside(mousePosWorld.x, mousePosWorld.y)) {
                if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
                    OnClick();
                }

                //HOVER STATE
                isHover = true;
            }
            else {
                isHover = false;
            }
        }
    }

    void RenderText() {
        if (containsText) {
            buttonTextObj->Render(); // Render the button text
        }
    }

    void Render() override {
        if (hasTexture) {
            if (textureHoverID != -1) {
                if (isHover) {
                    SetTextureID(textureHoverID);
                }
                else {
                    SetTextureID(textureNormalID);
                }
            }
            UIElement::Render(); // Render the button texture using the transformation matrix from UIObject
        }

        if (containsText) {
            buttonTextObj->Render(); // Render the button text
        }
    }

    void SetButtonPosition(const glm::vec3& position) {
        UIElement::SetPosition(position); // Update the position in UIObject
    }

    void SetButtonScale(const glm::vec3& scale) {
        UIElement::SetScale(scale); // Update the scale in UIObject
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

    void SetHoverTexture(const std::string& texturePath) {
        textureHoverID = TextureLoad(texturePath);
        textureNormalID = GetTextureID();
    }

private:
    glm::vec3 buttonPosition;
    glm::vec3 buttonScale;
    Text* buttonTextObj;
    bool containsText = true;
    bool isClickable;
    bool isHover = false;
    glm::vec2 mousePosWorld;
    std::function<void()> onClickAction;

    Tex textureHoverID = -1;
    Tex textureNormalID = -1;
    bool hasTexture = true;
};
