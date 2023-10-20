#pragma once

#include "GameObject.h"
#include "TextRenderer.h"

class Text : public GameObject
{
public:
    Text(const std::string& name, const std::string& content, TextRenderer& textRenderer)
        : GameObject(name), m_content(content), m_textRenderer(textRenderer)
    {
        m_textRenderer.Initialize();
    }

    virtual void Render() override
    {
        m_textRenderer.RenderText(m_content, m_position.x, m_position.y);
    }

    void SetContent(const std::string& content)
    {
        m_content = content;
    }

private:
    std::string m_content;
    TextRenderer& m_textRenderer;
};
