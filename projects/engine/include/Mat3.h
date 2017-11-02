#pragma once

#include "Vec3.h"
#include "Mat2.h"

#include <ostream>

namespace math
{
	struct Mat3
	{
		static const Mat3 Identity;

		float matrix[9];

		Mat3();
		Mat3(const float& _matrix);
		Mat3(
			const float& _m0, const float& _m1, const float& _m2,
			const float& _m3, const float& _m4, const float& _m5,
			const float& _m6, const float& _m7, const float& _m8);
		~Mat3();

		Mat3 operator-();

		friend Mat3 operator+(const Mat3& left, const Mat3& right);
		friend Mat3 operator-(const Mat3& left, const Mat3& right);
		friend Mat3 operator*(const Mat3& left, const Mat3& right);
		friend Mat3 operator/(const Mat3& left, const Mat3& right);
		friend Vec3 operator*(const Mat3& left, const Vec3& right);
		friend Vec3 operator/(const Mat3& left, const Vec3& right);
		friend Mat3 operator*(const Mat3& left, const float& scalar);
		friend Mat3 operator/(const Mat3& left, const float& scalar);
		friend std::ostream& operator<<(std::ostream& stream, const Mat3& vector);

		Mat3& operator=(const Mat3& other);

		bool operator==(const Mat3& other);
		bool operator!=(const Mat3& other);

		Mat3& operator+=(const Mat3& other);
		Mat3& operator-=(const Mat3& other);
		Mat3& operator*=(const Mat3& other);
		Mat3& operator*=(const float& scalar);
		Mat3& operator/=(const Mat3& other);
		Mat3& operator/=(const float& scalar);

		Mat3 Inverse(const Mat3& mat);
		Mat3 Transpose(const Mat3& mat);
		float Determinant(const Mat3& mat);
		float Determinant(const float & a, const float & d, const float & b, const float & c);

		static Mat3 RodriguezRotation(const Vec3& axis, const float angle);
	};
}