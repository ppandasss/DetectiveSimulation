#pragma once

#include "GameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"
#include "Engine.h"

class RenderGameObject : public GameObject
{
public:
	RenderGameObject(const std::string& name, const std::string& texturePath)
		: GameObject(name)
	{
		*textureId = LoadTexture(texturePath);
		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;

		// Create Jack mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 1.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 1.0f; v2.v = 1.0f ;
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 1.0f ; v3.v = 1.0f;
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 1.0f;

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v1);
		vertices.push_back(v3);
		vertices.push_back(v4);
		*meshVert = CreateMesh(vertices);

	}


	virtual void Render() override
	{
		model = glm::translate(model, m_position);
		model = glm::rotate(model, m_orientation, glm::vec3(0, 0, 1));
		model = glm::scale(model, m_scale);

		Application::Get().DrawTexture(*textureId, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

private:

	Tex* textureId;
	Mesh* meshVert;
	glm::mat4 model {1};

};