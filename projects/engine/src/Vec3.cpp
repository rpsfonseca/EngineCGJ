#include "Vec3.h"

namespace math
{
	const Vec3 Vec3::Zero = Vec3::Vec3(0.0f, 0.0f, 0.0f);
	const Vec3 Vec3::UnitX = Vec3(1.0f, 0.0f, 0.0f);
	const Vec3 Vec3::UnitY = Vec3(0.0f, 1.0f, 0.0f);
	const Vec3 Vec3::UnitZ = Vec3(0.0f, 0.0f, 1.0f);

	Vec3::Vec3() {}

	Vec3::Vec3(const float& scalar)
		: x(scalar), y(scalar), z(scalar)
	{
	}

	Vec3::Vec3(const float& x, const float& y, const float& z)
		: x(x), y(y), z(z)
	{
	}

	Vec3::Vec3(const Vec3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	Vec3::~Vec3()
	{
	}

	Vec3 Vec3::operator-()
	{
		return Vec3(-x, -y, -z);
	}

	Vec3 operator+(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	Vec3 operator-(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	Vec3 operator*(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	Vec3 operator/(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x / right.x, left.y / right.y, left.z / right.z);
	}

	Vec3 operator*(const Vec3& left, const float& scalar)
	{
		return Vec3(left.x * scalar, left.y * scalar, left.z * scalar);
	}

	Vec3 operator/(const Vec3& left, const float& scalar)
	{
		float invScalar = 1.0f / scalar;
		return Vec3(left.x * invScalar, left.y * invScalar, left.z * invScalar);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
	{
		stream << "Vec3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

	Vec3& Vec3::operator=(const Vec3& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	Vec3& Vec3::operator=(const float& scalar)
	{
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;
		return *this;
	}

	bool Vec3::operator==(const Vec3 & other)
	{
		return x == other.x && y == other.y;
	}

	bool Vec3::operator!=(const Vec3 & other)
	{
		return !(*this == other);
	}

	Vec3& Vec3::operator+=(const Vec3& other)
	{
		return Add(other);
	}

	Vec3& Vec3::operator-=(const Vec3& other)
	{
		return Subtract(other);
	}

	Vec3& Vec3::operator*=(const Vec3& other)
	{
		return Multiply(other);
	}

	Vec3& Vec3::operator*=(const float& scalar)
	{
		return Multiply(scalar);
	}

	Vec3& Vec3::operator/=(const Vec3& other)
	{
		return Divide(other);
	}

	Vec3& Vec3::operator/=(const float& scalar)
	{
		float invScalar = 1.0f / scalar;
		return Multiply(invScalar);
	}

	Vec3 Vec3::CrossProduct(const Vec3& left, const Vec3& right)
	{
		Vec3 aux;
		aux.x = -left.z * right.y + left.y * right.z;
		aux.y = left.z * right.x - left.x * right.z;
		aux.z = -left.y * right.x + left.x * right.y;
		return aux;
	}

	float Vec3::DotProduct(const Vec3& left, const Vec3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	Vec3 Vec3::Normalize()
	{
		float vecLength = this->Magnitude();
		Vec3 aux = Vec3(0.0f, 0.0f, 0.0f);
		if (vecLength > 0.0f)
		{
			vecLength = 1.0f / vecLength;

			aux.x = x * vecLength;
			aux.y = y * vecLength;
			aux.z = z * vecLength;
		}
		return aux;
	}

	float Vec3::Magnitude()
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	float Vec3::SquaredMagnitude()
	{
		return x * x + y * y + z * z;
	}

	Vec3& Vec3::Add(const Vec3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vec3& Vec3::Subtract(const Vec3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vec3& Vec3::Multiply(const Vec3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vec3& Vec3::Multiply(const float& other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
		return *this;
	}

	Vec3& Vec3::Divide(const Vec3& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}
}