#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	virtual ~Scene()
	{
		for (auto& object : m_gameObjects)
		{
			object->Clear();
			delete  object;
		}
	}

	void Update(float dt,long frame)
	{
		for (auto& object : m_gameObjects) {
			object->Update(dt, frame);
			//std::cout << "Gameobject Update" << std::endl;
		}
			


		for (auto& object : m_toAddGameObjects)
			m_gameObjects.push_back(object);

		std::cout << "GAME OBJECTS: " << m_gameObjects.size() << std::endl;

		m_toAddGameObjects.clear();
	}

	void Render()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& object : m_gameObjects)
			object->Render();
	}

	void AddGameObject(GameObject* newGameObject)
	{
		m_toAddGameObjects.push_back(newGameObject);
	}

protected:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_toAddGameObjects;
};