#pragma once

#include "Vec3.h"

using namespace math;

class Animation
{
public:
	Animation();
	Animation(Vec3 init, Vec3 target);
	~Animation();

	Vec3 initPos;
	Vec3 currentPos;
	Vec3 targetPos;

	float animationSpeed;

	bool hasAnimationRunning;

	void updateAnimation();
private:

};