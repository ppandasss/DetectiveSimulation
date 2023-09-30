#include "Camera.h"


void Camera::Init(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up,int width,int height) {

    m_windowWidth = width;
    m_windowHeight = height;
    m_camPos = position;
    m_camDir = direction;
    m_camUp = up;
    m_camZoom = 1.0f;
    m_camDegree = 0.0f;

    UpdateViewMatrix();
   //UpdateProjectionMatrix();
}

Camera::~Camera() {}

void Camera::UpdateProjectionMatrix() {
    m_projectionMatrix = glm::ortho(-(m_windowWidth / 2) * m_camZoom, (m_windowWidth / 2) * m_camZoom,
        -(m_windowHeight / 2) * m_camZoom, (m_windowHeight / 2) * m_camZoom,
        NEAR_PLANE, FAR_PLANE);
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
	return m_projectionMatrix * m_viewMatrix * ModelMatrix;
}

void Camera::Move(float dx, float dy) {
    m_camPos.x += dx;
    m_camPos.y += dy;
    UpdateViewMatrix();
}

void Camera::ZoomIn(float step) {
    m_camZoom += step;
    UpdateProjectionMatrix();
}

void Camera::ZoomOut(float step) {
    m_camZoom -= step;
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
