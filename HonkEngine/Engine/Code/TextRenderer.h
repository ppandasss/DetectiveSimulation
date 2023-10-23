#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void Initialize(const std::string& fontPath);
    void RenderText(const std::string& text, float x, float y, const glm::mat4& model);

private:
    GLuint m_program;
    GLuint m_VAO, m_VBO;
    FT_Library m_ft;
    FT_Face m_face;
};
