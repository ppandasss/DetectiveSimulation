#pragma once
#include "GameObject.h"
#include "Application.h"
#include "TextRenderer.h"
#include "Engine.h"
#include <string>
#include <glm/glm.hpp>

class Text : public GameObject {
public:
    Text(const std::string& name, const std::string& content, const std::string& fontPath)
        : GameObject(name), m_content(content)
    {
        textRenderer = std::make_unique<TextRenderer>();
        textRenderer->Initialize(fontPath);
    }

    virtual void Update(float dt, long frame) override
    {
        // Update logic for Text
    }

    virtual void Render() override
    {
        float x = m_position.x;
        float y = m_position.y;
        textRenderer->RenderText(m_content, x, y, model);
    }

    // No Clear method for now, as TextRenderer doesn't have one
    virtual void Clear() override {}

    void SetContent(const std::string& content)
    {
        m_content = content;
    }

    // No SetFont for now, as TextRenderer doesn't have one

private:
    std::unique_ptr<TextRenderer> textRenderer;
    std::string m_content;
    glm::mat4 model{ 1 };
};