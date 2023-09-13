#pragma once

#include "IObject.h"
#include<CDT.h>
#include <glm/glm.hpp>


struct Properties
{
	public:
	Properties(CDTMesh* mesh, CDTTex* tex, glm::vec3 position, glm::vec3 scale,float orientation)
	{
		this->mesh = *mesh;
		this->tex = *tex;
		this->position = position;
		this->scale = scale;
		this->orientation = orientation;
		modelMatrix = glm::mat4(1.0f);
	}

	public:
		CDTMesh mesh;
		CDTTex tex;
		glm::vec3 position;
		glm::vec3 scale;
		float orientation;
		glm::mat4 modelMatrix;

};
class GameObject : public IObject
{
	public:
		GameObject(Properties* props):m_mesh(props->mesh),m_tex(props->tex),m_pos(props->position),m_scale(props->scale),
			m_orient(props->orientation),m_modelMatrix(props->modelMatrix){}

		virtual	void Draw() = 0;
		virtual void Update(float dt) = 0;
		virtual void Clean() = 0;

	protected:
		CDTMesh m_mesh;
		CDTTex m_tex;
		glm::vec3 m_pos;
		glm::vec3 m_scale;
		float m_orient;
		glm::mat4 m_modelMatrix;

	private:



};

