#include "Timer.h"

float Timer::deltaTime = 0.0f;
float Timer::lastTime = 0.0f;
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
	frameCount++;
	if (currentTime - lastTime >= 1.0)
	{
		fps = frameCount;
		frameCount = 0;
		lastTime += 1.0f;
	}
}

double Timer::getTotalElapsedTime()
{
	return glfwGetTime();
}

