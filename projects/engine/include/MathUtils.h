#pragma once

#define DEGREES 57.29577951308232185913f
#define RADIAN 0.01745329251994329547f

class MathUtils
{
public:
	MathUtils();
	~MathUtils();

	static float degrees(const float& angle);
	static float radians(const float& angle);
};

