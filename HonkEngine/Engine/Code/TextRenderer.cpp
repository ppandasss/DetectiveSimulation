#include "TextRenderer.h"
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include <fstream>

TextRenderer::TextRenderer()
{
    // Initialize OpenGL objects to 0 or create them here
    m_program = 0;
    m_VAO = 0;
    m_VBO = 0;
}

TextRenderer::~TextRenderer()
{
    // Cleanup
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void TextRenderer::Initialize(const std::string& fontPath)
{
    // Initialize FreeType and load the font
   // Initialize FreeType and load the font
    std::cout << "Trying to load font from: " << fontPath << std::endl;

    std::ifstream infile(fontPath);
    if (!infile.good()) {
        std::cerr << "File does not exist or is not readable." << std::endl;
    }
    infile.close();


    FT_Error error;

    error = FT_Init_FreeType(&m_ft);
    if (error)
    {
        std::cerr << "Error initializing FreeType: Error code " << error << std::endl;
        return;
    }

    error = FT_New_Face(m_ft, fontPath.c_str(), 0, &m_face);
    if (error == FT_Err_Unknown_File_Format)
    {
        std::cerr << "Error loading font: The file format is unsupported." << std::endl;
        return;
    }
    else if (error)
    {
        std::cerr << "Error loading font: Error code " << error << std::endl;
        return;
    }


    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // Initialize shader program, VAO, VBO, etc.
    // Assuming m_program is already initialized and compiled

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::RenderText(const std::string& text, float x, float y, const glm::mat4& model)
{
    // Activate corresponding render state
    glUseProgram(m_program);

    // Set model matrix
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // Render text
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        FT_Load_Char(m_face, *c, FT_LOAD_RENDER);

        // Generate texture
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

        // Render glyph texture over quad
        float xpos = x + m_face->glyph->bitmap_left;
        float ypos = y - (m_face->glyph->bitmap.rows - m_face->glyph->bitmap_top);

        float w = m_face->glyph->bitmap.width;
        float h = m_face->glyph->bitmap.rows;

        float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, texture);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (m_face->glyph->advance.x >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)

        // Delete the glyph texture
        glDeleteTextures(1, &texture);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}





