#include "Input.h"

Input* Input::s_instance = nullptr;

bool Input::mouseButtonStates[GLFW_MOUSE_BUTTON_LAST] = { false };
bool Input::keyStates[GLFW_KEY_LAST] = { false };

bool Input::GetKeyDown(int keyCode)
{
    if (glfwGetKey(m_window, keyCode) == GLFW_PRESS && !keyStates[keyCode])
    {
        keyStates[keyCode] = true;
        return true;
    }
    else if (glfwGetKey(m_window, keyCode) == GLFW_RELEASE)
    {
        keyStates[keyCode] = false;
    }
    return false;
}

bool Input::GetKey(int keyCode)
{
    return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool Input::GetKeyUp(int keyCode)
{
    if (glfwGetKey(m_window, keyCode) == GLFW_RELEASE)
    {
        keyStates[keyCode] = false;
        return true;
    }
    return false;
}

bool Input::GetMouseButtonDown(int button)
{
    if (glfwGetMouseButton(m_window, button) == GLFW_PRESS && !mouseButtonStates[button])
    {
        mouseButtonStates[button] = true;
        return true;
    }
    else if (glfwGetMouseButton(m_window, button) == GLFW_RELEASE)
    {
        mouseButtonStates[button] = false;
    }
    return false;
}

bool Input::GetMouseButton(int button)
{
    return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

bool Input::GetMouseButtonUp(int button)
{
    if (glfwGetMouseButton(m_window, button) == GLFW_RELEASE)
    {
        mouseButtonStates[button] = false;
        return true;
    }
    return false;
}
