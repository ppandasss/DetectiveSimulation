#pragma once

#include "IObject.h"
#include<CDT.h>
#include <glm/glm.hpp>


struct Properties
{
	public:
	Properties(CDTMesh* mesh, CDTTex* tex, glm::vec3 position, glm::vec3 scale)
	{
		this->pos = position;
		this->mesh = *mesh;
		this->tex = *tex;
		this->scale = scale;
	}

	public:
		CDTMesh mesh;
		CDTTex tex;
		glm::vec3 pos;
		glm::vec3 scale;

};
class GameObject : public IObject
{
	public:
		GameObject(Properties* props):m_mesh(props->mesh),m_tex(props->tex),m_position(props->pos),m_scale(props->scale){}

		virtual	void Draw() = 0;
		virtual void Update(float dt) = 0;
		virtual void Clean() = 0;

	protected:
		CDTMesh m_mesh;
		CDTTex m_tex;
		glm::vec3 m_position;
		glm::vec3 m_scale;

	private:



};

