#include "Timer.h"

float Timer::deltaTime = 0.0f;
float Timer::lastFPSUpdate = 0.0f;
float Timer::lastFrameTime = 0.0f;
int Timer::frameCount = 0;
int Timer::fps = 0;

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::update()
{
	double currentTime = getTotalElapsedTime();
	Timer::deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;

	frameCount++;

	if (currentTime - lastFPSUpdate >= 1.0)
	{
		fps = frameCount;
		frameCount = 0;
		lastFPSUpdate += 1.0f;
	}
}

double Timer::getTotalElapsedTime()
{
	return glfwGetTime();
}

