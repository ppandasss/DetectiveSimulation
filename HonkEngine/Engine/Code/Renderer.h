#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class Mesh;

class Renderer
{
public:
	void Initialize(int width, int height);
	void SetRenderMode(int mode, float alpha);
	void SetTransform(const glm::mat4& modelMat);
	void SetTexture(GLuint tex, float offsetX, float offsetY);

	void DrawMesh(const Mesh& mesh);


private:
	glm::mat4	cdt_ViewMatrix;
	glm::mat4	cdt_ProjectionMatrix;
	glm::mat4	cdt_MVP;

	int m_windowWidth, m_windowHeight;
	Shader m_shader;
};