// Player.cpp
#include "Player.h"
#include <GLFW/glfw3.h>


extern GLFWwindow* window;

Player::Player(Properties* props, GLFWwindow* mainWindow) : GameObject(props) {
    window = mainWindow;
}

void Player::Draw() {

 
    SetRenderMode(CDT_TEXTURE, 1.0f);
    // Set the player's texture
    SetTexture(m_tex, 0.0f, 0.0f);
    // Set the transformation matrix for rendering
    SetTransform(m_modelMatrix);
    // Draw the player's mesh
    DrawMesh(m_mesh);
}

void Player::Update(float dt) {
    // Implement update logic for the player
    // Check for input and update the player's position accordingly
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        m_pos.x -= playerSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        m_pos.x += playerSpeed * dt;
    }
    
    // Set the transformation matrix to position and scale the player
    glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), m_orient, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 sMat = glm::scale(glm::mat4(1.0f), m_scale);
    glm::mat4 tMat = glm::translate(glm::mat4(1.0f), m_pos);
    m_modelMatrix = tMat * sMat;

}

void Player::Clean() {
    // Implement cleanup logic for the player
}

