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
    for (const auto& pair : Characters) {
        std::cout << "Character: " << pair.first << ", Texture ID: " << pair.second.TextureID << std::endl;
    }
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color, int numChars)
{

    // activate corresponding render state	
    m_shader.use();
    m_shader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);


    scale *= 0.01f;
    // iterate through all characters
    int charCount = 0;
    for (auto c = text.begin(); c != text.end() && (numChars == -1 || charCount < numChars); c++)
    {
        Character ch = Characters[*c];

        /* std::cout << "Character :" << *c << std::endl;
         std::cout << "Character Size :" << ch.Size.x << " "<< ch.Size.y << std::endl;*/




        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };


        // render glyph texture over quad
        //std::cout << "Binding texture ID for rendering: " << ch.TextureID << " for char: " << *c << std::endl;
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        //std::cout << "Binding texture ID for rendering: " << ch.TextureID << std::endl;
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glPointSize(100.0f);
        glDrawArrays(GL_POINT, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        charCount++;
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


