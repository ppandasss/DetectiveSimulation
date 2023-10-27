#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "Shader.h"
#include"Renderer.h"

class Mesh;


typedef GLuint Tex;


class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void Initialize(const std::string& fontPath);
    void RenderText(const std::string& text,float x,float y ,float scale, const glm::mat4& model);
    void SetTextColor(const glm::vec4& color);

private:

    Shader m_shader;
    FT_Library m_ft;
    FT_Face m_face;
    GLuint m_VAO; 
    GLuint m_VBO;  

    int m_windowWidth, m_windowHeight;
};

