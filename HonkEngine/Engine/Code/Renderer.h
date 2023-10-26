#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include "Camera.h"

class Mesh;


typedef GLuint Tex;

class Renderer
{
public:
	void Initialize(int width, int height);
	void SetRenderMode(int mode, float alpha);
	void SetTransform(const glm::mat4& modelMat);
	void SetTexture(Tex tex, float offsetX, float offsetY);

	void DrawMesh(const Mesh& mesh);
	void UnloadMesh(Mesh& mesh);
	void TextureUnload(Tex& tex);
	void SetTexturerColor(const glm::vec4& color);

private:
	glm::mat4	cdt_ViewMatrix;
	glm::mat4	cdt_ProjectionMatrix;
	glm::mat4	cdt_MVP;

	int m_windowWidth, m_windowHeight;
	Shader m_shader;
	Camera m_camera;
};