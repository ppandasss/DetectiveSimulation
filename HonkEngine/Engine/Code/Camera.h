#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {

public:

    ~Camera();

    glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetMVP(glm::mat4 ModelMatrix) const;

    void Init(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up,int width,int height);
    void Move(float dx, float dy);
    void ZoomIn(float step);
    void ZoomOut(float step);
    void Rotate(float degree);
    void Reset();

    void SetPosition(float xpos, float ypos);
    void SetZoom(float zoom);
    void SetRotation(float degree);

    float GetPosX() const;
    float GetPosY() const;
    float GetZoom() const;


private:

    int m_windowWidth;
    int m_windowHeight;

    const float NEAR_PLANE = -1.0f;
    const float FAR_PLANE = 1.0f;
    float MAX_ZOOM = 2.0f;
    float MIN_ZOOM = 0.5f;

    glm::vec3 m_camPos;
    glm::vec3 m_camDir;
    glm::vec3 m_camUp;

    float m_camZoom;
    float m_camDegree;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;

    void UpdateProjectionMatrix();
    void UpdateViewMatrix();
};


