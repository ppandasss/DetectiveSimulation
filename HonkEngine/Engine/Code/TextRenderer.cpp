#include "TextRenderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

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
    // Initialize FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // Load font as face
    if (FT_New_Face(ft, fontPath.c_str(), 0, &m_face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const char* SHADER_VERTEX_PATH = "Assets/Shaders/text.vs";
    const char* SHADER_FRAGMENT_PATH = "Assets/Shaders/text.fs";
    m_shader.Initialize(SHADER_VERTEX_PATH, SHADER_FRAGMENT_PATH);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL error during Initialize: " << err << std::endl;
    }

    std::cout << "Initialize() called with fontPath: " << fontPath << std::endl;
}

void TextRenderer::RenderText(const std::string& text, const glm::mat4& model)
{
    std::cout << "RenderText() called with text: " << text << std::endl;

    m_shader.use();
    m_shader.SetMatrix4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        std::cout << "Processing character: " << *c << std::endl;

        // Load character glyph 
        FT_Error error = FT_Load_Char(m_face, *c, FT_LOAD_RENDER);
        if (error)
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph. Error Code: " << error << std::endl;
            continue;
        }


        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // ... (rest of your code for rendering the text)

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "OpenGL error after glDrawArrays: " << err << std::endl;
        }

        glDeleteTextures(1, &texture);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::SetTextColor(const glm::vec4& color)
{
    m_shader.use();
    m_shader.SetVector4f("textColor", color);
}


