#pragma once



#include <stdio.h>
#include <stdlib.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h>



//define in main.cpp
extern GLFWwindow* window;

// "Initialize GLFW, GLEW, Input, Create window
int SystemInit(int width, int height, const char* title);

void SystemShutdown();

// Get frame duration between each frame
void FrameInit();
double FrameStart();
void FrameEnd();



