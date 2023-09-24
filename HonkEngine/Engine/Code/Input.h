#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
    Input()
    {
        s_instance = this;
    }

    void Initialize(GLFWwindow* window)
    {
        m_window = window;
    }

    static Input& Get() { return *s_instance; }

    bool GetKeyDown(int keyCode);
    bool GetKey(int keyCode);
    bool GetKeyUp(int keyCode);

    bool GetMouseButtonDown(int button);
    bool GetMouseButton(int button);
    bool GetMouseButtonUp(int button);

private:
    static Input* s_instance;
    GLFWwindow* m_window = nullptr;

    static bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST];
    static bool keyStates[GLFW_KEY_LAST];
};
