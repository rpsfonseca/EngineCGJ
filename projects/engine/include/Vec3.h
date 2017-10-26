#pragma once
#include <ostream>

namespace math
{
	class Vec3
	{
	public:
		float x, y, z;
		
		static const Vec3 Zero;
		static const Vec3 UnitX;
		static const Vec3 UnitY;
		static const Vec3 UnitZ;

		Vec3();
		Vec3(const float& scalar);
		Vec3(const float& x, const float& y, const float& z);
		Vec3(const Vec3& vec);
		~Vec3();

		Vec3 operator-();

		friend Vec3 operator+(const Vec3& left, const Vec3& right);
		friend Vec3 operator-(const Vec3& left, const Vec3& right);
		friend Vec3 operator*(const Vec3& left, const Vec3& right);
		friend Vec3 operator/(const Vec3& left, const Vec3& right);
		friend Vec3 operator*(const Vec3& left, const float& scalar);
		friend Vec3 operator/(const Vec3& left, const float& scalar);
		friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);

		Vec3& operator=(const Vec3& other);
		Vec3& operator=(const float& other);

		bool operator==(const Vec3& other);
		bool operator!=(const Vec3& other);

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator*=(const float& other);
		Vec3& operator/=(const Vec3& other);
		Vec3& operator/=(const float& other);

		static Vec3 CrossProduct(const Vec3& left, const Vec3& right);
		static float DotProduct(const Vec3& left, const Vec3& right);

		Vec3 Normalize();

		float Magnitude();
		float SquaredMagnitude();

	private:
		Vec3& Add(const Vec3& other);
		Vec3& Subtract(const Vec3& other);
		Vec3& Multiply(const Vec3& other);
		Vec3& Multiply(const float& other);
		Vec3& Divide(const Vec3& other);
	};
}