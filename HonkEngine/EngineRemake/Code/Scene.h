#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include"CDT.h"

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

class Scene
{
public:

	void AddGameObject(GameObject* newGameObject)
	{
		m_toAddGameObjects.push_back(newGameObject);
	}
	void Load() //set vertices for game objects
	{

		for (auto& object : m_gameObjects)
			object->Load();

		printf("Level: Load\n");
	}
	void Init() //set initial gameobject data
	{
		for (auto & object : m_gameObjects)
			object->Init();

		printf("Level: Init\n");
	}
	void Update(float dt) //update gameobject data
	{
		for (auto& object : m_gameObjects)
			object->Update(dt);

		for (auto& object : m_toAddGameObjects)
			m_gameObjects.push_back(object);

		std::cout << "GAME OBJECTS: " << m_gameObjects.size() << std::endl;

		m_toAddGameObjects.clear();
	}

	void Draw() //render gameobjects
	{
		// Clear the screen
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& object : m_gameObjects)
			object->Draw();

		glfwSwapBuffers(window);
	}

	void Free()//delete inactive gameobjects
	{
		for (auto& object : m_gameObjects)
		{
			object->Free();
			if (!object->getState())
			{
				delete object;
			}
		}	

		ResetCam();
		printf("Level: Free\n");
	}

	void Unload()//unload mesh and texture
	{
		for (auto& object : m_gameObjects)
		{
			object->Unload();
		}
	}

protected:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_toAddGameObjects;
};