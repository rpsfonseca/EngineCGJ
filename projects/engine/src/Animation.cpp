#include "Animation.h"
#include "Timer.h"

Animation::Animation()
{
	hasAnimationRunning = false;
}

Animation::Animation(Vec3 init, Vec3 target)
{
	initPos = init;
	currentPos = initPos;
	targetPos = target;
	animationSpeed = 0.05f;
	hasAnimationRunning = true;
}

Animation::~Animation()
{
}

void Animation::updateAnimation()
{
	if (hasAnimationRunning && currentPos != targetPos)
	{
		currentPos = Vec3::Lerp(currentPos, targetPos, Timer::deltaTime * animationSpeed);
	}
	else if (currentPos == targetPos)
	{
		hasAnimationRunning = false;
	}
}

