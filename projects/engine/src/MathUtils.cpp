#include "../include/MathUtils.h"



MathUtils::MathUtils()
{
}


MathUtils::~MathUtils()
{
}

float MathUtils::degrees(const float& angle)
{
	return angle * DEGREES;
}

float MathUtils::radians(const float& angle)
{
	return angle * RADIAN;
}