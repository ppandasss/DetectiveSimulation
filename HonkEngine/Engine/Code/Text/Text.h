#pragma once
#include "../GameObjects/GameObject.h"
#include "../Application.h"
#include "TextRenderer.h"
#include "../Engine.h"
#include <string>
#include <glm/glm.hpp>

class Text : public GameObject {
public:
    Text(const std::string& name, const std::string& content, const std::string& fontPath,bool isCenterPivot = false)
        : GameObject(name), m_content(content),m_isCenterPivot(isCenterPivot)
    {
        textRenderer = std::make_unique<TextRenderer>();
        textRenderer->Initialize(fontPath);
    }

    virtual void Update(float dt, long frame) override
    {

    }

    virtual void Render() override
    {
        float x = m_position.x;
        float y = m_position.y;
        textRenderer->RenderText(m_content, x, y, m_scale, m_color, m_isCenterPivot);
    }

    // No Clear method for now, as TextRenderer doesn't have one
    virtual void Clear() override {}

    void SetContent(const std::string& content)
    {
       // std::cout << "Setting content: " << content << std::endl;
        m_content = content;
    }


    void SetColor(const glm::vec3& color)
    {
        m_color = color;
    }
    void SetScale(float scale)
    {
        m_scale = scale;
    }

    // No SetFont for now, as TextRenderer doesn't have one
    std::string GetContent() const
	{
		return m_content;
	}


private:
    std::unique_ptr<TextRenderer> textRenderer;
    std::string m_content;
    glm::mat4 model{ 1 };
    glm::vec3 m_color = glm::vec3(0.0f, 0.0f, 0.0f);
    float m_scale = 1.0f;
    bool m_isCenterPivot;
};