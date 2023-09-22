#pragma once



#include <stdio.h>
#include <stdlib.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Input.h"


//define in main.cpp

class System
{
public:

	// "Initialize GLFW, GLEW, Input, Create window
	static int SystemInit(int width, int height, const char* title);

	static void SystemShutdown();

	// Get frame duration between each frame
	void FrameInit();
	double FrameStart();
	void FrameEnd();

	static GLFWwindow* window;
	static Input input;
};

