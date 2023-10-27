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
        glm::mat4 rMat = glm::mat4(1.0f);
        glm::mat4 sMat = glm::mat4(1.0f);
        glm::mat4 tMat = glm::mat4(1.0f);

        tMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
        rMat = glm::rotate(glm::mat4(1.0f), m_orientation, glm::vec3(0.0f, 0.0f, 1.0f));
        sMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));

        model = tMat * rMat * sMat;
        
    }

    virtual void Render() override
    {
        float x = m_position.x;
        float y = m_position.y;
        textRenderer->RenderText(m_content,x,y,1.0f, model);
    }

    // No Clear method for now, as TextRenderer doesn't have one
    virtual void Clear() override {}

    void SetContent(const std::string& content)
    {
        m_content = content;
    }

    void SetColor(const glm::vec4& color)
    {
        textRenderer->SetTextColor(color);
    }

    // No SetFont for now, as TextRenderer doesn't have one

private:
    std::unique_ptr<TextRenderer> textRenderer;
    std::string m_content;
    glm::mat4 model{ 1 };
};