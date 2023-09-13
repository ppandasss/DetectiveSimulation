//engine main.cpp
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Object/GameObject.h>
#include "Player.h"

GLFWwindow* window;

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(1280, 720, "HONK!", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	double lastFrameTime = glfwGetTime();
	double frameRateUpdateInterval = 1.0; // Update frame rate every 1 second
	double frameRateTimer = 0.0;
	int frameCount = 0;

	int spriteSheetWidth = 1;
	int spriteSheetHeight = 1;
	CDTMesh* playerMesh = ResourceManager::GetInstance().CreateMeshVertices(spriteSheetWidth, spriteSheetHeight);
	CDTTex* playerTexture = ResourceManager::GetInstance().SetTexture("waiter_texture.png");

	if (playerTexture == nullptr) {
		// Texture loading failed
		std::cout << "Failed to load texture: waiter_texture.png" << std::endl;
		// Add additional error handling here if needed
	}
	
	Properties playerProps(playerMesh, playerTexture, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),0.0f);
	Player player(&playerProps,window);
	while (!glfwWindowShouldClose(window))
	{
		
		double currentTime = glfwGetTime();
		double dt = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		player.Update(dt);
		glClearColor(0.324f, 0.444f, 0.59f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	
		player.Draw();
		

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (frameRateTimer >= frameRateUpdateInterval)
		{
			double frameRate = frameCount / frameRateTimer;
			std::cout << "Frame Rate: " << frameRate << " FPS" << std::endl;
			frameRateTimer = 0.0;
			frameCount = 0;
		}
	}
	player.Clean();
	glfwTerminate();

	return 0;
}