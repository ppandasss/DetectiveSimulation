#include "Camera.h"
#include <iostream> 



void Camera::Init(int width, int height) {
    std::cout << "Initializing camera..." << std::endl;

    m_windowWidth = width;
    m_windowHeight = height;
    m_camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camDir = glm::vec3(0.0f, 0.0f, -1.0f);
    m_camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camZoom = 1.0f;
    m_camDegree = 0.0f;

   // std::cout << "Initial Camera Position: (" << m_camPos.x << ", " << m_camPos.y << ", " << m_camPos.z << ")" << std::endl;
    //std::cout << "Initial Camera Direction: (" << m_camDir.x << ", " << m_camDir.y << ", " << m_camDir.z << ")" << std::endl;

    UpdateViewMatrix();
    UpdateProjectionMatrix();


}

Camera::~Camera() {}

void Camera::UpdateProjectionMatrix() {

    float Scale = 200.0f;
    m_projectionMatrix = glm::ortho(-(m_windowWidth / Scale) * m_camZoom, (m_windowWidth / Scale) * m_camZoom,
        -(m_windowHeight / Scale) * m_camZoom, (m_windowHeight / Scale) * m_camZoom,
        NEAR_PLANE, FAR_PLANE);

    //m_projectionMatrix = glm::ortho(-80.0f, 80.0f, -60.0f, 60.0f, -1.0f, 100.0f);

    //std::cout << "Window Width: " << m_windowWidth << ", Window Height: " << m_windowHeight << std::endl;
    //std::cout << "Zoom Level: " << m_camZoom << std::endl;
    //std::cout << "Near Plane: " << NEAR_PLANE << ", Far Plane: " << FAR_PLANE << std::endl;
    // Manually print the projection matrix
    //for (int i = 0; i < 4; ++i) {
    //    for (int j = 0; j < 4; ++j) {
    //        std::cout << m_projectionMatrix[i][j] << ' ';
    //    }
    //    std::cout << std::endl;
    //}
}

void Camera::UpdateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_camPos, m_camPos + m_camDir, m_camUp);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return m_projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() const {
    return m_viewMatrix;
}

glm::mat4 Camera::GetMVP(glm::mat4 ModelMatrix) const {
    return ModelMatrix * m_viewMatrix * m_projectionMatrix;
}

void Camera::Move(float dx, float dy) {
    m_camPos.x += dx;
    m_camPos.y += dy;
    UpdateViewMatrix();
}

void Camera::ZoomIn(float step) {
    m_camZoom -= step;
    if (m_camZoom > MAX_ZOOM) m_camZoom = MAX_ZOOM;
    //std::cout << "zoom: " << m_camZoom << std::endl;
    UpdateProjectionMatrix();
}

void Camera::ZoomOut(float step) {
    m_camZoom += step;
    if (m_camZoom < MIN_ZOOM) m_camZoom = MIN_ZOOM;
    UpdateProjectionMatrix();
}

void Camera::Rotate(float degree) {
    m_camDegree += degree;
    // Update the camera direction based on the new degree
    // This is a simplified example; you may need more complex rotation logic
    m_camDir = glm::vec3(cos(glm::radians(m_camDegree)), sin(glm::radians(m_camDegree)), m_camDir.z);
    UpdateViewMatrix();
}

void Camera::Reset() {
    m_camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camDir = glm::vec3(0.0f, 0.0f, -1.0f);
    m_camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camZoom = 1.0f;
    m_camDegree = 0.0f;
    UpdateProjectionMatrix();
    UpdateViewMatrix();
}

void Camera::SetPosition(float xpos, float ypos) {
    m_camPos.x = xpos;
    m_camPos.y = ypos;
    UpdateViewMatrix();
    //std::cout << "Camera Position after Move - X: " << m_camPos.x << ", Y: " << m_camPos.y << std::endl;
}

void Camera::SetZoom(float zoom) {
    m_camZoom = zoom;
    UpdateProjectionMatrix();
}

float Camera::GetZoom() const
{
    return m_camZoom;
}

void Camera::SetRotation(float degree) {
    m_camDegree = degree;
    // Update the camera direction based on the new degree
    // This is a simplified example; you may need more complex rotation logic
    m_camDir = glm::vec3(cos(glm::radians(m_camDegree)), sin(glm::radians(m_camDegree)), m_camDir.z);
    UpdateViewMatrix();
}

float Camera::GetPosX() const {
    return m_camPos.x;
}

float Camera::GetPosY() const {
    return m_camPos.y;
}
