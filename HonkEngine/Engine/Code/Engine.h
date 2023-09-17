#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include<iostream>
#include<string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include "Application.h"


struct Vertex {
    float x, y, z;  // Position
    float r, g, b;  // Color
    float u, v;     // Texture coordinates
};

struct Mesh {
    std::vector<Vertex> vertices;
    unsigned int vertexBuffer;
    unsigned int vaoHandle;

};
typedef GLuint Tex;

#define CDT_COLOR 0
#define CDT_TEXTURE 1
#define BUFFER_OFFSET(i) ((char *)NULL + (i))


    void Initialize(int width, int height);
    Tex LoadTexture(std::string path);
    Mesh CreateMesh(std::vector<Vertex> in_vertices);
    void UnloadMesh(Mesh& mesh);

     void SetRenderMode(int mode, float alpha);
     void SetTexture(Tex tex, float offsetX, float offsetY);
     void SetTransform(const glm::mat4& modelMat);
     void DrawMesh(const Mesh& mesh);
     void DrawTexture(unsigned int textureId, const glm::mat4& transform);
    

  
  


