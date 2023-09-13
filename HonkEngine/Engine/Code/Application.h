#pragma once

#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Scene.h"
#include "Input.h"

class Application
{
public:
	Application();
	~Application();

	void AddScene(const std::string& name, Scene* scene)
	{
		m_sceneMap.insert({ name, scene });
	}

	void SetScene(const std::string& name)
	{
		if (m_sceneMap.find(name) != m_sceneMap.end())
			m_currentScene = m_sceneMap[name];
	}

	void Run();

	static Application& Get() { return *s_instance; }

	void DrawTexture(unsigned int textureId, const glm::mat4& transform);


	glm::vec2  CursorPos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		return { xpos,ypos };

	}


	bool IsMouseClick(int mouseButton)
	{
		return  glfwGetMouseButton(m_window,mouseButton) == GLFW_PRESS;
		
	}

	Scene* GetCurrentScene()
	{
		return m_currentScene;
	}



private:
	static Application* s_instance;

	unsigned int VBO, VAO, EBO;
	Shader m_shader;
	GLFWwindow* m_window;
	Input m_input;

	Scene* m_currentScene = nullptr;
	std::map<std::string, Scene*> m_sceneMap;

};