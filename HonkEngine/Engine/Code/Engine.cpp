#include "Engine.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* SHADER_VERTEX_PATH = "Assets/Shaders/color_tex_transparency.vert";
const char* SHADER_FRAGMENT_PATH = "Assets/Shaders/color_tex_transparency.frag";
const std::string TEXTURE_PATH = "Assets/Images/awesomeface.png";

int m_windowWidth;
int m_windowHeight; 
Shader m_shader;
Tex m_blankTex;



Mesh CreateMesh(std::vector<Vertex> in_vertices)
{
    Mesh mesh;
    mesh.vertices = in_vertices;

    glGenBuffers(1, &mesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &mesh.vaoHandle);
    glBindVertexArray(mesh.vaoHandle);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);

    // Set up vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));

    glBindVertexArray(0);

    return mesh;
}
Tex TextureLoad(const std::string path)
{
    Tex texture;

    int texWidth, texHeight, channels;
    //stbi_set_flip_vertically_on_load(false); // STB Image loads images upside-down by default ?

    unsigned char* pData = stbi_load(path.c_str(), &texWidth, &texHeight, &channels, 0);
    if (!pData)
    {
        std::cerr << "Failed to load texture. Reason: " << stbi_failure_reason() << std::endl;
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLint format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, pData);

    stbi_image_free(pData); // Free the image data after uploading it to OpenGL.

    if (texture == 0)
    {
        std::cerr << "Failed to load texture from path: " << path << std::endl;
        return 0;
    }

    std::cout << "TextureLoad::TextureID " << texture << std::endl;
    return texture;
}



int GetWindowWidth() {
	return m_windowWidth;
}

int GetWindowHeight() {
	return m_windowHeight;
}




