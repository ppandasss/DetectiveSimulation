#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "../Renderer/Shader.h"
#include "../Renderer/Renderer.h"
#include <map>

class Mesh;

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

typedef GLuint Tex;

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void Initialize(const std::string& fontPath);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color,bool centerPivot, int numChars = -1);
    void RenderCharacter(char ch, float& x, float y, float scale, glm::vec3 color);
    void CleanupCharacters();
private:
    Shader m_shader; // Only one declaration of m_shader
    unsigned int m_VAO, m_VBO;
    std::map<GLchar, Character> Characters;

    int m_windowWidth, m_windowHeight;
};
