#pragma once

#include <string>
#include"glm/glm.hpp"

class GameObject
{
public:
	GameObject(const std::string& name = "")
		: m_name(name){}

	virtual void Update(float dt,long frame){}

	virtual void Render(){}

	virtual void Clear(){}

	virtual void SetPosition(glm::vec3 newPos){ m_position = newPos; }
	
	virtual void SetScale(const glm::vec3& scale){m_scale = scale;}

	virtual void SetOrientation(float orientation){m_orientation = orientation;}

protected:
	std::string m_name;
	glm::vec3 m_position {0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale {1.0f, 1.0f, 1.0f};
	int layer = 0;
	float m_orientation = 0.0f;
};