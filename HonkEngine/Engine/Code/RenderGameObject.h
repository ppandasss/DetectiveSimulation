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
		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;

		// Create Jack mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 1.0f; v2.v = 0.0f ;
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 1.0f ; v3.v = 1.0f;
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 1.0f;

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v1);
		vertices.push_back(v3);
		vertices.push_back(v4);

		texture_Id = TextureLoad(texturePath);

		meshVert = CreateMesh(vertices);


	}

	virtual void Update(float dt)
	{
		//std::cout << "Update::TextureID " << textureId << std::endl;

		glm::mat4 rMat = glm::mat4(1.0f);
		glm::mat4 sMat = glm::mat4(1.0f);
		glm::mat4 tMat = glm::mat4(1.0f);

		rMat = glm::translate(model, m_position);
		sMat = glm::rotate(model, m_orientation, glm::vec3(0, 0, 1));
		tMat = glm::scale(model, m_scale);

		model = tMat * sMat * rMat;
	}


	virtual void Render() override
	{
		SetTexture(texture_Id, 0.0f, 0.0f);
		SetRenderMode(CDT_TEXTURE, 1.0f);
		std::cout << "Render::TextureID " << texture_Id << std::endl;	
		SetTransform(model);
		DrawMesh(meshVert);
		//plication::Get().DrawTexture(*textureId, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

	virtual void Clear() 
	{
		UnloadMesh(meshVert);
		TextureUnload(texture_Id);
	}

private:

	Tex texture_Id;
	Mesh meshVert;
	glm::mat4 model {1};

};