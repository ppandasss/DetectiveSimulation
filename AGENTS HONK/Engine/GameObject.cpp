#include "GameObject.h"
#include <iostream>

// Constructor to initialize the object with a texture and position.
GameObject::GameObject(const std::string& texturePath, const glm::vec2& position) {

    this->position = position;
    this->size = glm::vec2(100.0f, 100.0f); // Set a default size for the object.

    // Load the texture using your CDT function.
    textureID = TextureLoad(texturePath.c_str());
    // Initialize other member variables as needed.
}

// Update function to handle movement logic.
void GameObject::Update(float deltaTime) {
    // Example: Move the object left and right.
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position.x -= 100.0f * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 100.0f * deltaTime;
    }

    // Add more update logic as needed.
}

// Render function to draw the object.
void GameObject::Render() {
    // Set up rendering with your CDT functions.
    SetRenderMode(CDT_TEXTURE,1.0f);
    SetTexture(textureID, /* specify texture coordinates if needed */);

    // Define the model matrix (position and size).
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.0f));

    // Set the transformation matrix for rendering.
    SetTransform(modelMatrix);

    // Render the object with your CDT functions.
    DrawMesh(/* specify the mesh you want to render */);
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
