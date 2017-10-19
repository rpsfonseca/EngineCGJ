#include "Vec2.h"

namespace math
{
	const Vec2 Vec2::Zero	= Vec2(0.0f, 0.0f);
	const Vec2 Vec2::UnitX = Vec2(1.0f, 0.0f);
	const Vec2 Vec2::UnitY = Vec2(0.0f, 1.0f);

	Vec2::Vec2()
	{
	}

	Vec2::Vec2(const float& scalar)
		: x(scalar), y(scalar)
	{

	}

	Vec2::Vec2(const float& x, const float& y)
		: x(x), y(y)
	{
	}

	Vec2::~Vec2() {}

	Vec2 Vec2::operator-()
	{
		return Vec2(-x, -y);
	}

	Vec2 operator+(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x + right.x, left.y + right.y);
	}

	Vec2 operator-(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x - right.x, left.y - right.y);
	}

	Vec2 operator*(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x * right.x, left.y * right.y);
	}

	Vec2 operator/(const Vec2& left, const Vec2& right)
	{
		return Vec2(left.x / right.x, left.y / right.y);
	}

	Vec2 operator*(const Vec2& left, const float& scalar)
	{
		return Vec2(left.x * scalar, left.y * scalar);
	}

	Vec2 operator/(const Vec2& left, const float& scalar)
	{
		return Vec2(left.x / scalar, left.y / scalar);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
	{
		stream << "Vec2(" << vector.x << ", " << vector.y << ")";
		return stream;
	}

	Vec2& Vec2::operator=(const Vec2& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vec2& Vec2::operator=(const float& scalar)
	{
		this->x = scalar;
		this->y = scalar;
		return *this;
	}

	bool Vec2::operator==(const Vec2 & other)
	{
		return x == other.x && y == other.y;
	}

	bool Vec2::operator!=(const Vec2 & other)
	{
		return !(*this == other);
	}

	Vec2& Vec2::operator+=(const Vec2& other)
	{
		return Add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other)
	{
		return Subtract(other);
	}

	Vec2& Vec2::operator*=(const Vec2& other)
	{
		return Multiply(other);
	}

	Vec2& Vec2::operator*=(const float& other)
	{
		return Multiply(other);
	}

	Vec2& Vec2::operator/=(const Vec2& other)
	{
		return Divide(other);
	}

	Vec2& Vec2::operator/=(const float& scalar)
	{
		float invScalar = 1.0f / scalar;
		return Multiply(invScalar);
	}

	float Vec2::DotProduct(const Vec2& left, const Vec2& right)
	{
		return left.x * right.x + left.y * right.y;
	}

	Vec2 Vec2::Normalize()
	{
		float vecLength = this->Magnitude();
		Vec2 aux = Vec2(0.0f, 0.0f);
		if (vecLength > 0.0f)
		{
			vecLength = 1.0f / vecLength;

			aux.x = x * vecLength;
			aux.y = y * vecLength;
		}
		return aux;
	}

	float Vec2::Magnitude()
	{
		return std::sqrt(x * x + y * y);
	}

	float Vec2::SquaredMagnitude()
	{
		return x * x + y * y;
	}

	Vec2& Vec2::Add(const Vec2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2& Vec2::Subtract(const Vec2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2& Vec2::Multiply(const Vec2& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vec2& Vec2::Multiply(const float& other)
	{
		this->x *= other;
		this->y *= other;
		return *this;
	}

	Vec2& Vec2::Divide(const Vec2& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}
}