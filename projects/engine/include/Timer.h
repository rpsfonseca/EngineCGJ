#pragma once

#include "GLFW\glfw3.h"

class Timer
{
public:
	Timer();
	~Timer();

	static float deltaTime;
	
	/**
		Simple wrapper for glfwGetTime.
		Measures time elapsed since GLFW was initialized.
	*/
	static double getTotalElapsedTime();
private:

};