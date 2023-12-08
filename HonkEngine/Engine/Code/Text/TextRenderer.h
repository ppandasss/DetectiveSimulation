#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "../Renderer/Shader.h"
#include"../Renderer/Renderer.h"
#include <map>

class Mesh;


typedef GLuint Tex;

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void Initialize(const std::string& fontPath);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, int numChars = -1);

private:

    Shader m_shader;
    FT_Library m_ft;
    FT_Face m_face;
    GLuint m_VAO;
    GLuint m_VBO;

    int m_windowWidth, m_windowHeight;
};