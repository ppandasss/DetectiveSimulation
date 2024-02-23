#pragma once
#include "../GameObjects/GameObject.h"
#include "../UI/UINormal.h"
#include "../Text/Text.h"
#include <memory>

class DialogueBox : public GameObject {
public:
    DialogueBox(const std::string& name, const std::string& boxTexturePath, const std::string& fontPath,
        const glm::vec3& boxPosition, const glm::vec3& boxScale, bool isOnScreen,
        const std::string& initialText, const glm::vec3& textPosition, float textScale, const glm::vec3& textColor)
        : GameObject(name) {
        // Create the background box as a UINormal object
        UIbox = std::make_unique<UINormal>(name + "_bg", boxTexturePath, boxPosition, boxScale, isOnScreen);

        // Create the text component
        text = std::make_unique<Text>("Text_" + name, initialText, fontPath);
        text->SetPosition(textPosition);
        text->SetScale(textScale);
        text->SetColor(textColor);
    }

    void Render() override {
        UIbox->Render(); // Render the dialogue box background
        text->Render();  // Render the text
    }

    void SetText(const std::string& content) {
        text->SetContent(content);
    }

    void SetTextColor(const glm::vec3& color) {
        text->SetColor(color);
    }

    void SetTextScale(float scale) {
        text->SetScale(scale);
    }

private:
    std::unique_ptr<UINormal> UIbox;
    std::unique_ptr<Text> text;
};
