#pragma once
#include <ostream>

namespace math
{
	class Vec2
	{
	public:
		float x, y;

		static const Vec2 Zero;
		static const Vec2 UnitX;
		static const Vec2 UnitY;

		Vec2();
		Vec2(const float& scalar);
		Vec2(const float& x, const float& y);
		~Vec2();

		Vec2 operator-();

		friend Vec2 operator+(const Vec2& left, const Vec2& right);
		friend Vec2 operator-(const Vec2& left, const Vec2& right);
		friend Vec2 operator*(const Vec2& left, const Vec2& right);
		friend Vec2 operator/(const Vec2& left, const Vec2& right);
		friend Vec2 operator*(const Vec2& left, const float& right);
		friend Vec2 operator/(const Vec2& left, const float& right);
		friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);

		Vec2& operator=(const Vec2& other);
		Vec2& operator=(const float& other);

		bool operator==(const Vec2& other);
		bool operator!=(const Vec2& other);

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator*=(const float& other);
		Vec2& operator/=(const Vec2& other);
		Vec2& operator/=(const float& other);

		static float DotProduct(const Vec2& left, const Vec2& right);

		Vec2 Normalize();

		float Magnitude();
		float SquaredMagnitude();

	private:
		Vec2& Add(const Vec2& other);
		Vec2& Subtract(const Vec2& other);
		Vec2& Multiply(const Vec2& other);
		Vec2& Multiply(const float& other);
		Vec2& Divide(const Vec2& other);

	};
}