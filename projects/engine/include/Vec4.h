#pragma once
#include "Vec3.h"
namespace math
{
	class Vec4
	{
	public:
		float x, y, z, w;

		Vec4();
		Vec4(const float& x, const float& y, const float& z, const float& w = 1.0f);
		Vec4(const Vec3& vec3);
		Vec4(const Vec4& vec4);
		~Vec4();
		friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
	};
}

