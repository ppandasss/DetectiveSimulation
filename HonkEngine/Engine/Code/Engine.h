#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include<iostream>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include "Application.h"
#include"Camera.h"


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

    Tex TextureLoad(const std::string path);
 

    Mesh CreateMesh(std::vector<Vertex> in_vertices);


    int  GetWindowWidth();
    int  GetWindowHeight();


     void PrintMatrix(const glm::mat4& mat);
  
  


