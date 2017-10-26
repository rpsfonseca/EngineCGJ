#include "Vec4.h"

namespace math
{


	Vec4::Vec4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vec4::Vec4(const float& x, const float& y, const float& z, const float& w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Vec4::Vec4(const Vec3 & vec3)
		: x(vec3.x), y(vec3.y), z(vec3.z), w(1.0f)
	{

	}

	Vec4::Vec4(const Vec4 & vec4)
		: x(vec4.x), y(vec4.y), z(vec4.z), w(vec4.w)
	{

	}

	Vec4::~Vec4()
	{
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
	{
		stream << "Vec4(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}
}