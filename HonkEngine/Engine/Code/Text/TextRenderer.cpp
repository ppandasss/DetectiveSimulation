#include "TextRenderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include"../Application.h"



TextRenderer::TextRenderer()
{
    m_VAO = 0;
    m_VBO = 0;
}

TextRenderer::~TextRenderer()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void TextRenderer::Initialize(const std::string& fontPath)
{


    const char* SHADER_VERTEX_PATH = "Assets/Shaders/text.vs";
    const char* SHADER_FRAGMENT_PATH = "Assets/Shaders/text.fs";
    m_shader.Initialize(SHADER_VERTEX_PATH, SHADER_FRAGMENT_PATH);

    m_shader.use();
    Camera& camera = Application::GetCamera();
    glm::mat4 projection = camera.GetProjectionMatrix();
    m_shader.SetMatrix4("projection", projection);
    // glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

     // FreeType
 // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // find path to font

    if (fontPath.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            //std::cout << "Generated texture ID for character " << c << ": " << texture << std::endl;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //std::cout << "Text::Initialize() called with font path :" << fontPath << std::endl;

}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color, bool centerPivot, int numChars)
{
    // Activate corresponding render state
    m_shader.use();
    m_shader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    scale *= 0.01f;
    float lineHeight = 0.0f; // Adjust line height as needed
    float originalX = x;
    float originalY = y;

    std::vector<std::string> lines;
    std::string currentLine;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c)
    {
        if (*c == ' ' && *(c + 1) == ' ') // Detect double space as a marker for a new line
        {
            lines.push_back(currentLine);
            currentLine.clear();
            c++; // Skip the second space
            continue;
        }
        currentLine += *c;
    }
    lines.push_back(currentLine); // Add the last line

    for (const std::string& line : lines)
    {
        float totalWidth = 0.0f;
        // Calculate total width of the line
        for (char ch : line)
        {
            totalWidth += (Characters[ch].Advance >> 6) * scale; // Advance is in 1/64th pixels
        }

        if (centerPivot)
        {
            // Adjust x to center the line
            x = originalX - totalWidth / 2.0f;
        }

        // Render each character in the line
        for (char ch : line)
        {
            Character glyph = Characters[ch];

            float xpos = x + glyph.Bearing.x * scale;
            float ypos = y - (glyph.Size.y - glyph.Bearing.y) * scale;

            float w = glyph.Size.x * scale;
            float h = glyph.Size.y * scale;
            lineHeight = std::max(lineHeight, h + 10.0f * scale); // Update line height

            // Update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, glyph.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            x += (glyph.Advance >> 6) * scale; // Advance cursor to the next glyph
        }

        y -= lineHeight; // Move to the next line
        lineHeight = 0.0f; // Reset line height for the next line
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void TextRenderer::CleanupCharacters()
{
    for (auto c : Characters) {
        glDeleteTextures(1, &c.second.TextureID);
    }
    Characters.clear();
}


