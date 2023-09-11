// GameObject.h
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "CDT.h"

class GameObject {
public:
    // Constructor to initialize the object with a texture and position.
    GameObject(const std::string& texturePath, const glm::vec2& position);

    // Update function to handle movement logic.
    void Update(float deltaTime);

    // Render function to draw the object.
    void Render();

    // Getters and setters for position, size, etc.
    glm::vec2 GetPosition() const;
    void SetPosition(const glm::vec2& position);
    glm::vec2 GetSize() const;
    void SetSize(const glm::vec2& size);
    // Add more getters and setters as needed.

private:
    // Member variables for position, size, texture, etc.
    glm::vec2 position;
    glm::vec2 size; 
    GLuint textureID; // Assuming you load textures with OpenGL.
    // Add more member variables as needed.
};

#endif
