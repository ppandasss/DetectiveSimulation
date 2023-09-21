#pragma once

#include <string>
#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject(const std::string& name = "")
		: m_name(name){}

	virtual void Load() {}

	virtual void Init() {}

	virtual void Update(float dt){}

	virtual void Draw(){}

	virtual void Free(){}

	virtual void Unload() {}

	void SetPosition(glm::vec3 newPos){ m_position = newPos; }

	void SetScale(const glm::vec3& scale){m_scale = scale;}

	void SetOrientation(float orientation){m_orientation = orientation;}

	bool getState() { return isActive; }

protected:
	std::string m_name;
	glm::vec3 m_position {0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale {1.0f, 1.0f, 0.0f};
	float m_orientation = 0.0f;
	bool isActive = true;
};