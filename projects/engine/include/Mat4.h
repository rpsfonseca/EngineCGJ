#pragma once
#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"

#include <ostream>

namespace math
{
	enum Axis
	{
		AxisX = 0,
		AxisY = 1,
		AxisZ = 2
	};

	struct Mat4
	{
		static const Mat4 Identity;

		float matrix[16];

		Mat4();
		Mat4(const float& _matrix);
		~Mat4();

		Mat4 operator-();

		friend Mat4 operator+(const Mat4& left, const Mat4& right);
		friend Mat4 operator-(const Mat4& left, const Mat4& right);
		friend Mat4 operator*(const Mat4& left, const Mat4& right);
		friend Mat4 operator/(const Mat4& left, const Mat4& right);
		friend Vec3 operator*(const Mat4& left, const Vec3& right);
		friend Vec4 operator*(const Mat4& left, const Vec4& right);
		friend Vec3 operator/(const Mat4& left, const Vec3& right);
		friend Mat4 operator*(const Mat4& left, const float& scalar);
		friend Mat4 operator/(const Mat4& left, const float& scalar);
		friend std::ostream& operator<<(std::ostream& stream, const Mat4& vector);

		Mat4& operator=(const Mat4& other);

		bool operator==(const Mat4& other);
		bool operator!=(const Mat4& other);

		Mat4& operator+=(const Mat4& other);
		Mat4& operator-=(const Mat4& other);
		Mat4& operator*=(const Mat4& other);
		Mat4& operator*=(const float& scalar);
		Mat4& operator/=(const Mat4& other);
		Mat4& operator/=(const float& scalar);

		Mat3 Upper3x3Matrix();
		static Mat4 RotationMatrixFromAxisAngle(const Vec3& axis, const float angle);
		static Mat4 RotationMatrixAboutAxis(const Axis axis, const float angle);
		static Mat4 ScaleMatrix(const Vec3& scaleVector);
		static Mat4 ScaleMatrix(const float& x, const float& y, const float& z);
		static Mat4 TranslationMatrix(const Vec3& translationVector);
		static Mat4 TranslationMatrix(const float& x, const float& y, const float& z);

	};
}