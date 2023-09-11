// GameObject.h
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <glm/glm.hpp>
#include<gl/GL.h>
#include "CDT.h"

class GameObject {
public:
    GameObject(const std::string& texturePath, const glm::vec2& position, CDTMesh* mesh);
    GameObject(const std::string& texturePath, const glm::vec2& position, int spriteSheetWidth, int spriteSheetHeight);
    void Render();
    void SetModelMatrix(const glm::mat4& modelMatrix);
    glm::vec2 GetPosition() const;
    void SetPosition(const glm::vec2& position);
    glm::vec2 GetSize() const;
    void SetSize(const glm::vec2& size);

private:
    glm::vec2 position;
    glm::vec2 size;
    GLuint textureID;
    CDTMesh* mesh; // Added member for the mesh.
};

#endif
