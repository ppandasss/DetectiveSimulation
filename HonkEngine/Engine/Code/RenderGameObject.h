#pragma once

#include "GameObject.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include "Application.h"

class RenderGameObject : public GameObject
{
public:
	RenderGameObject(const std::string& name, const std::string& texturePath)
		: GameObject(name)
	{
		texture_id = Engine::LoadTexture(texturePath);
	}

	virtual void Render() override
	{

		glm::mat4 model {1};

		model = glm::translate(model, m_position);
		model = glm::rotate(model, m_orientation,glm::vec3(0,0,1));
		model = glm::scale(model, m_scale);
		Application::Get().DrawTexture(texture_id, model);
		//Engine::DrawTexture(texture_id, glm::mat4{1});
	}

private:
	int texture_id;

};