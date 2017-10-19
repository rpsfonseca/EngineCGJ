#pragma once

namespace math
{
	struct Mat2
	{
		float matrix[4];

		Mat2();
		~Mat2();

		//float Determinant(const Mat2& mat);
		static float Determinant(const float a, const float b, const float c, const float d);
		static float Determinant();
	};

}