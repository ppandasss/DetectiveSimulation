#include "Input.h"

Input* Input::s_instance = nullptr;

bool Input::mouseButtonStates[GLFW_MOUSE_BUTTON_LAST] = { false };

bool Input::GetKeyDown(int keyCode)
{

    if (keyCode == GLFW_MOUSE_BUTTON_1)
    {
        // Check if the left mouse button is pressed in the current frame but was not pressed in the previous frame
        if (glfwGetMouseButton(m_window, keyCode) == GLFW_PRESS && !mouseButtonStates[keyCode])
        {
            mouseButtonStates[keyCode] = true; // Update the mouse button state   
            return true; //Left mouse button was clicked in the current frame

        }

    }

    return false; //HERE
}

bool Input::GetKey(int keyCode)
{
    return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool Input::GetKeyUp(int keyCode)
{

    mouseButtonStates[keyCode] = (glfwGetMouseButton(m_window, keyCode) == GLFW_PRESS);
    return glfwGetKey(m_window, keyCode) == GLFW_RELEASE;

}