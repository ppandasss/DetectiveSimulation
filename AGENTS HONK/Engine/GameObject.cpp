// GameObject.cpp
#include "GameObject.h"
#include <iostream>

// Constructor to initialize the object with a texture, position, and mesh.
GameObject::GameObject(const std::string& texturePath, const glm::vec2& position, CDTMesh* mesh) {
    this->position = position;
    this->size = glm::vec2(100.0f, 100.0f); // Set a default size for the object.

    textureID = TextureLoad(texturePath.c_str());
    this->mesh = mesh;
}

GameObject::GameObject(const std::string& texturePath, const glm::vec2& position, int spriteSheetWidth, int spriteSheetHeight) {
    this->position = position;
    this->size = glm::vec2(100.0f, 100.0f); // Set a default size for the object.

    // Create the mesh using the sprite sheet dimensions.
    *mesh = CreateMesh(spriteSheetWidth, spriteSheetHeight);

    textureID = TextureLoad(texturePath.c_str());
}

// Render function to draw the object.
void GameObject::Render() {
    // Set up rendering with your CDT functions.
    SetRenderMode(CDT_TEXTURE, 1.0f);
    SetTexture(textureID, 0.0f, 0.0f);

    // Define the model matrix (position and size).
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

    // Set the transformation matrix for rendering.
    SetTransform(modelMatrix);

    // Render the object with the provided mesh.
    DrawMesh(*mesh);
}


// Getters and setters for position, size, etc.
glm::vec2 GameObject::GetPosition() const {
    return position;
}

void GameObject::SetPosition(const glm::vec2& position) {
    this->position = position;
}

glm::vec2 GameObject::GetSize() const {
    return size;
}

void GameObject::SetSize(const glm::vec2& size) {
    this->size = size;
}
// Add more getters and setters as needed.
