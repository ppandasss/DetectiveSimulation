#include "Input.h"

Input* Input::s_instance = nullptr;

bool Input::GetKeyDown(int keyCode)
{
	return false;
}

bool Input::GetKey(int keyCode)
{  
	return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool Input::GetKeyUp(int keyCode)
{
	return glfwGetKey(m_window, keyCode) == GLFW_RELEASE;
}