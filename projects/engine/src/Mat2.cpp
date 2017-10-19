#include "Mat2.h"

namespace math
{
	Mat2::Mat2()
	{
	}


	Mat2::~Mat2()
	{
	}

	float Mat2::Determinant()
	{
		return 0.0f;
	}

	float Mat2::Determinant(const float a, const float b, const float c, const float d)
	{
		return a*d - c*b;
	}
}
