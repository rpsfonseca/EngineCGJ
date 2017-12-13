#pragma once

#include "GLFW\glfw3.h"

class Timer
{
public:
	Timer();
	~Timer();

	static float deltaTime;
	static float lastFPSUpdate;
	static float lastFrameTime;
	static int fps;

	static void update();
	
	/**
		Simple wrapper for glfwGetTime.
		Measures time elapsed since GLFW was initialized.
	*/
	static double getTotalElapsedTime();

private:
	static int frameCount;

};