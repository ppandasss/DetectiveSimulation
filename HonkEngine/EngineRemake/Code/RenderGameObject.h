#pragma once

#include "GameObject.h"
#include "../Code/CDT.h"
#include <glm/glm.hpp>

class RenderGameObject : public GameObject
{
public:
	RenderGameObject(const std::string& name, const std::string& texturePath)
		: GameObject(name)
	{
	
	
	}
	void Load() override
	{
	
		std::vector<CDTVertex> vertices;
		CDTVertex v1, v2, v3, v4;

		// Create Jack mesh/texture

		vertices.clear();
		v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
		v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 1.0f; v2.v = 0.0f;
		v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 1.0f; v3.v = 1.0f;
		v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 1.0f;

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v1);
		vertices.push_back(v3);
		vertices.push_back(v4);

		mesh = CreateMesh(vertices);
		tex = TextureLoad("waiter_test.png");

		std::cout << "RenderObject Loaded: " << m_name << std::endl;
	}
	virtual void Init() override
	{

	}
	virtual void Update(float dt)
	{
		std::cout << "RenderObject Updated: " << m_name << std::endl;

		glm::mat4 rMat = glm::mat4(1.0f);
		glm::mat4 sMat = glm::mat4(1.0f);
		glm::mat4 tMat = glm::mat4(1.0f);

		tMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
		rMat = glm::rotate(glm::mat4(1.0f), m_orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		sMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));

		model = tMat * rMat * sMat;

	}
	void Draw() override
	{
		std::cout << "Rendering GameObject: " << m_name << std::endl;
		SetRenderMode(CDT_TEXTURE, 1.0f);
		SetTexture(tex, 0.0f, 0.0f);
		std::cout << "Render::TextureID " << tex << std::endl;	
		SetTransform(model);
		DrawMesh(mesh);
		//plication::Get().DrawTexture(*textureId, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

	void Free() override
	{

	}

	void Unload() override
	{
		UnloadMesh(mesh);
		TextureUnload(tex);
	}

private:

	CDTMesh mesh;
	CDTTex tex;
	glm::mat4 model {1};

};