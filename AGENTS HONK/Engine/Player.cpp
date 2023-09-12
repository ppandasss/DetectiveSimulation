// Player.cpp
#include "Player.h"

Player::Player(Properties* props) : GameObject(props) {
    // Initialize any player-specific properties here
}

void Player::Draw() {
    // Set the transformation matrix to position and scale the player
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, m_position);
    modelMatrix = glm::scale(modelMatrix, m_scale);

    // Set the transformation matrix for rendering
    SetTransform(modelMatrix);

    // Set the player's texture
    SetTexture(m_tex, 0.0f, 0.0f);

    // Draw the player's mesh
    DrawMesh(m_mesh);
}

void Player::Update(float dt) {
    // Implement update logic for the player
    // Check for input and update the player's position accordingly
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_position.x -= playerSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_position.x += playerSpeed * dt;
    }
}

void Player::Clean() {
    // Implement cleanup logic for the player
}

