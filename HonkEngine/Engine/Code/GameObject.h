#pragma once

#include <string>

class GameObject
{
public:
	GameObject(const std::string& name = "")
		: m_name(name)
	{

	}

	virtual void Update(float dt)
	{
	}

	virtual void Render()
	{
	}

	void SetPosition(glm::vec3 newPos)
	{
		m_position = newPos;
	}

	void SetScale(const glm::vec3& scale)
	{
		m_scale = scale;
	}

	void SetOrientation(float orientation)
	{
		m_orientation = orientation;
	}

protected:
	std::string m_name;
	glm::vec3 m_position {0, 0, 0};
	glm::vec3 m_scale {1, 1, 0};
	float m_orientation = 0.0f;
};