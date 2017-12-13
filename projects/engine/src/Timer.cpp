#include "Timer.h"

float Timer::deltaTime = 0.0f;

Timer::Timer()
{
}

Timer::~Timer()
{
}

double Timer::getTotalElapsedTime()
{
	return glfwGetTime();
}

