#include "Engine.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int m_windowWidth;
int m_windowHeight;
int m_programID;
Shader m_shader;
Tex m_blankTex;
float m_tranparency;

glm::vec3   cdt_camPos;
glm::vec3	cdt_camdir;
glm::vec3	cdt_camup;
float		cdt_camzoom;
float		cdt_camdegree;
glm::mat4	cdt_ViewMatrix;
glm::mat4	cdt_ProjectionMatrix;
glm::mat4	cdt_MVP;

void Initialize(int width, int height) {
   
    srand(time(NULL));

    m_windowWidth = width;
    m_windowHeight= height;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader.Initialize("color_tex_transparency.vert", "color_tex_transparency.frag");
    m_blankTex = LoadTexture("awesomeface.png");
    m_tranparency = 1.0f;

    // set cam, model view proj matrix
     cdt_camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    cdt_camdir = glm::vec3(0.0f, 0.0f, -1.0f);
    cdt_camup = glm::vec3(0.0f, 1.0f, 0.0f);
    cdt_camzoom = 1.0f;
    cdt_camdegree = 0.0f;
    cdt_ProjectionMatrix = glm::ortho(-(m_windowWidth / 2) * cdt_camzoom, (m_windowWidth / 2) * cdt_camzoom, -(m_windowHeight / 2) * cdt_camzoom, (m_windowHeight / 2) * cdt_camzoom, -10.0f, 10.0f);
    cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);

}



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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

    glBindVertexArray(0);

    return mesh;
}
int LoadTexture(std::string path)
{
    // load and create a texture 
    // -------------------------
    unsigned int texture1;
  
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(path.c_str() , &width, &height, &nrChannels, 0);
    if (data)
    {
        int alpha = nrChannels == 4 ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, alpha, width, height, 0, alpha, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture1;
}

void SetRenderMode(int mode, float alpha) {
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    m_shader.use();  // Activate the shader
    m_shader.setInt("mode", mode);  // Set integer uniform
    m_shader.setFloat("alpha", alpha);  // Set float uniform

    // default setting
    SetTexture(m_blankTex, 0.0f, 0.0f);
    SetTransform(glm::mat4(1.0f));
}

void SetTexture(Tex tex, float offsetX, float offsetY) {

    m_shader.setFloat("offsetX", offsetX);  // Set float uniform
    m_shader.setFloat("offsetY", offsetY);  // Set float uniform

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    m_shader.setInt("tex1", 0); 
}

void SetTransform(const glm::mat4& modelMat) {

    cdt_MVP = cdt_ProjectionMatrix * cdt_ViewMatrix * modelMat;
    glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "MVP"), 1, GL_FALSE, &cdt_MVP[0][0]);
}

void DrawMesh(const Mesh& mesh) {

    glBindVertexArray(mesh.vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());

    glBindVertexArray(0);
}
