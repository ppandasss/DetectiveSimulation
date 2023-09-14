#pragma once
#include<iostream>
#include<string>
#include <glm/glm.hpp>
#include"Application.h"


class Engine
{
public:
	Engine();
	static int LoadTexture(std::string path);
	static float CreateMesh(float vertices[]);
	~Engine();

private:

};

