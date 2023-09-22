#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

class Input
{
public:
	Input()
	{
		std::cout << "INput Constructor\n";
		s_instance = this;
	}

	void Initialize(GLFWwindow* window)
	{
		m_window = window;
		std::cout << "Window: " << m_window << "\n";
	}

	static Input& Get() { return *s_instance; }

	bool GetKeyDown(int keyCode);
	bool GetKey(int keyCode);
	bool GetKeyUp(int keyCode);

private:
	static Input* s_instance;
	GLFWwindow* m_window = nullptr;
	static bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST]; // Added for mouse button tracking
};

