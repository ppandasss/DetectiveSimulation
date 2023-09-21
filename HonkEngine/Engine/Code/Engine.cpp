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
float m_tranparency;

glm::vec3   cdt_camPos;
glm::vec3	cdt_camdir;
glm::vec3	cdt_camup;
float		cdt_camzoom;
float		cdt_camdegree;
glm::mat4	cdt_ViewMatrix;
glm::mat4	cdt_ProjectionMatrix;
glm::mat4	cdt_MVP;

const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 10.0f;

void Initialize(int width, int height) {
   
    srand(time(NULL));

    m_windowWidth = width;
    m_windowHeight= height;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader.Initialize(SHADER_VERTEX_PATH, SHADER_FRAGMENT_PATH);
    m_blankTex = TextureLoad(TEXTURE_PATH);
    m_tranparency = 1.0f;



    // set cam, model view proj matrix
    cdt_camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    cdt_camdir = glm::vec3(0.0f, 0.0f, -1.0f);
    cdt_camup = glm::vec3(0.0f, 1.0f, 0.0f);
    cdt_camzoom = 1.0f;
    cdt_camdegree = 0.0f;
    cdt_ProjectionMatrix = glm::ortho(-(m_windowWidth / 2) * cdt_camzoom, (m_windowWidth / 2) * cdt_camzoom, -(m_windowHeight / 2) * cdt_camzoom, (m_windowHeight / 2) * cdt_camzoom, NEAR_PLANE, FAR_PLANE);
    cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
    //PrintMatrix(cdt_ProjectionMatrix);
}

void PrintMatrix(const glm::mat4& mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
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

void TextureUnload(Tex& tex)
{
	glDeleteTextures(1, &tex);
	tex = GL_INVALID_INDEX;
}

void SetRenderMode(int mode, float alpha) {
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    m_shader.use();  // Activate the shader
    m_shader.setInt("mode", mode);  // Set integer uniform
    m_shader.setFloat("alpha", alpha);  // Set float uniform

    // default setting
    //SetTexture(m_blankTex, 0.0f, 0.0f);
    //SetTransform(glm::mat4(1.0f));
}

void SetTexture(Tex tex, float offsetX, float offsetY) {

    std::cout << "SetTexture::TextureID " << tex << std::endl;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	m_shader.setInt("tex1", 0);  // Set integer uniform
	m_shader.setFloat("offsetX", offsetX);  // Set float uniform
	m_shader.setFloat("offsetY", offsetY);  // Set float uniform
}

void SetTransform(const glm::mat4 &modelMat) {

    cdt_MVP = cdt_ProjectionMatrix * cdt_ViewMatrix * modelMat;
    std::cout << "Model matrix at start of SetTransform method:\n";
    PrintMatrix(modelMat);
    std::cout << "Proj matrix at start of SetTransform method:\n";
    PrintMatrix(cdt_ProjectionMatrix);
    std::cout << "View matrix at start of SetTransform method:\n";
    PrintMatrix(cdt_ViewMatrix);
    std::cout << "MVP matrix at start of SetTransform method:\n";
    PrintMatrix(cdt_MVP);
    glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "MVP"), 1, GL_FALSE, &cdt_MVP[0][0]);
   int errocode =  glGetError();

   std::cout << "Error code" << errocode << std::endl;
}

void DrawMesh(const Mesh& mesh) {
    std::cout << " DrawMesh method called:\n";

    glBindVertexArray(mesh.vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());

    glBindVertexArray(0);
}

void UnloadMesh(Mesh& mesh)
{
    glDeleteBuffers(1, &mesh.vertexBuffer);
    glDeleteVertexArrays(1, &mesh.vaoHandle);

    mesh.vertices.clear();
}




int GetWindowWidth() {
	return m_windowWidth;
}

int GetWindowHeight() {
	return m_windowHeight;
}
/*void DrawTexture(unsigned int textureId, const glm::mat4& transform)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // create transformations
    //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


    // get matrix's uniform location and set matrix
    m_shader.use();
    unsigned int transformLoc = glGetUniformLocation(m_shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // render container
    //lBindVertexArray(&mesh.vaoHandle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}*/

void MoveCam(float dx, float dy)
{
	cdt_camPos.x += dx;
	cdt_camPos.y += dy;

	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

void ZoomIn(float step)
{
	cdt_camzoom += step;

	cdt_ProjectionMatrix = glm::ortho(-(m_windowWidth / 2) * cdt_camzoom, (m_windowWidth / 2) * cdt_camzoom, -(m_windowHeight / 2) * cdt_camzoom, (m_windowHeight / 2) * cdt_camzoom, -10.0f, 10.0f);
}

void ZoomOut(float step)
{
	cdt_camzoom -= step;

	cdt_ProjectionMatrix = glm::ortho(-(m_windowWidth / 2) * cdt_camzoom, (m_windowWidth / 2) * cdt_camzoom, -(m_windowHeight / 2) * cdt_camzoom, (m_windowHeight / 2) * cdt_camzoom, -10.0f, 10.0f);
}

void RotateCam(float degree)
{
	cdt_camdegree += degree;

	glm::vec3 newUp;
	newUp.x = -1 * glm::sin(glm::radians(cdt_camdegree));
	newUp.y = glm::cos(glm::radians(cdt_camdegree));
	newUp.z = cdt_camup.z;

	cdt_camup = newUp;

	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

void ResetCam()
{
	cdt_camPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cdt_camdir = glm::vec3(0.0f, 0.0f, -1.0f);
	cdt_camup = glm::vec3(0.0f, 1.0f, 0.0f);

	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

void SetCamPosition(float xpos, float ypos)
{
	cdt_camPos.x = xpos;
	cdt_camPos.y = ypos;

	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

void SetCamZoom(float zoom)
{
	cdt_camzoom = zoom;
	if (cdt_camzoom < 0.1f) { cdt_camzoom = 0.1f; }

	cdt_ProjectionMatrix = glm::ortho(-(m_windowWidth / 2) * cdt_camzoom, (m_windowWidth / 2) * cdt_camzoom, -(m_windowHeight / 2) * cdt_camzoom, (m_windowHeight / 2) * cdt_camzoom, -10.0f, 10.0f);
	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

void SetCamRotation(float degree)
{
	cdt_camdegree = degree;

	glm::vec3 newUp;
	newUp.x = -1 * glm::sin(glm::radians(cdt_camdegree));
	newUp.y = glm::cos(glm::radians(cdt_camdegree));
	newUp.z = cdt_camup.z;

	cdt_camup = newUp;

	cdt_ViewMatrix = glm::lookAt(cdt_camPos, cdt_camPos + cdt_camdir, cdt_camup);
}

float GetCamPosX()
{
	return cdt_camPos.x;
}

float GetCamPosY()
{
	return cdt_camPos.y;
}

void SetCamPos(float x, float y)
{
	cdt_camPos.x = x;
	cdt_camPos.y = y;
}

