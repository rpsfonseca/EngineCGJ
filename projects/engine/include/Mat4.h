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
		Mat4(const float& _m0, const float& _m1, const float& _m2, const float& _m3,
			const float& _m4, const float& _m5, const float& _m6, const float& _m7,
			const float& _m8, const float& _m9, const float& _m10, const float& _m11,
			const float& _m12, const float& _m13, const float& _m14, const float& _m15);
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

		static Mat4 orthographic(const float& right, const float& left, const float& top, const float& bottom, const float& near, const float& far);
		static Mat4 perspective(const float& fov, const float& aspectRatio, const float& near, const float& far);
	};
}