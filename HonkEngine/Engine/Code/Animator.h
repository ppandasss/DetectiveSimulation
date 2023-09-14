#pragma once

#include <GLFW/glfw3.h>

class Animator
{
public:
	Animator()
	{
		s_instance = this;
	}
	~Animator();

private:
	static Animator* s_instance;

};

Animator::Animator()
{
}

Animator::~Animator()
{
}