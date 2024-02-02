#pragma once

#include "../GameObjects/GameObject.h"

#include <glm/glm.hpp>
#include "../Application.h"
#include "../Engine.h"

class UIObject : public GameObject
{
public:
	UIObject(const std::string& name, const std::string& texturePath, const glm::vec3& position,bool isOnScreen)
		: GameObject(name)
	{
		this->isOnScreen = isOnScreen;
		SetPosition(position);

		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;

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

		texture_Id = TextureLoad(texturePath);
		meshVert = CreateMesh(vertices);

		//std::cout << "RenderObject Created: " << m_name << std::endl;

	}

	UIObject(const std::string& name, const std::string& texturePath, bool isOnScreen)
		: GameObject(name)
	{
		this->isOnScreen = isOnScreen;
		std::vector<Vertex> vertices;
		Vertex v1, v2, v3, v4;

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

		texture_Id = TextureLoad(texturePath);
		meshVert = CreateMesh(vertices);

		//std::cout << "RenderObject Created: " << m_name << std::endl;

	}

	virtual void Update(float dt, long frame) override
	{

		glm::mat4 rMat = glm::mat4(1.0f);
		glm::mat4 sMat = glm::mat4(1.0f);
		glm::mat4 tMat = glm::mat4(1.0f);

		glm::vec3 camPos = glm::vec3(camera.GetPosX(), camera.GetPosY(), 0.0f);
		glm::vec3 targetPos = camPos + m_position;
		if (isOnScreen)
		{
			tMat = glm::translate(glm::mat4(1.0f), glm::vec3(targetPos.x, targetPos.y, 0.0f));
		}
		else
		{
			tMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
		}
		
		rMat = glm::rotate(glm::mat4(1.0f), m_orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		sMat = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));

		model = tMat * rMat * sMat;

	}

	virtual void Render() override
	{
		//std::cout << "RenderObjectRender: " << m_name << std::endl;


		//std::cout << "Rendering GameObject: " << m_name << std::endl;
		renderer.SetRenderMode(CDT_TEXTURE, 1.0f);
		renderer.SetTexture(texture_Id, 0.0f, 0.0f);
		//std::cout << "Render::TextureID " << texture_Id << std::endl;	
		renderer.SetTransform(model);
		renderer.DrawMesh(meshVert);

	}

	virtual void Clear()
	{
		renderer.UnloadMesh(meshVert);
		renderer.TextureUnload(texture_Id);
	}


private:

	bool isOnScreen;
	Renderer& renderer = Application::GetRenderer();
	Camera& camera = Application::GetCamera();
	Tex texture_Id;
	Mesh meshVert;
	glm::mat4 model{ 1 };

};