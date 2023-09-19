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
    Tex TextureLoad(std::string path);
    void TextureUnload(Tex& tex);

    Mesh CreateMesh(std::vector<Vertex> in_vertices);
    void UnloadMesh(Mesh& mesh);

    int  GetWindowWidth();
    int  GetWindowHeight();
    int GetCamPosX();
    int GetCamPosY();

     void SetRenderMode(int mode, float alpha);
     void SetTexture(Tex tex, float offsetX, float offsetY);
     void SetTransform(const glm::mat4& modelMat);
     void DrawMesh(const Mesh& mesh);
     
    
     void MoveCam(float dx, float dy);
     void ZoomIn(float step);
     void ZoomOut(float step);
     void RotateCam(float degree);
     void SetCamPosition(float xpos, float ypos);
     void SetCamZoom(float zoom);
     void SetCamRotation(float degree);
     void ResetCam();
     void SetCamPos(float x, float y);
  
  


