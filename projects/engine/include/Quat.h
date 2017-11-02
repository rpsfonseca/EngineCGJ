#pragma once

#include "Vec4.h"
#include "Mat4.h"
#include "Quat.h"

namespace math
{
#define Q_THRESHOLD (float)1.0e-5
	class Quat
	{
	public:
		Vec4 v;

	public:
		Quat();
		Quat(float x, float y, float z, float w);
		Quat(const Vec4& v);
		Quat(float angle, const Vec3& axis);
		~Quat();

		friend Quat operator+(const Quat& left, const Quat& right);
		friend Quat operator-(const Quat& left, const Quat& right);
		friend Quat operator*(const Quat& left, const Quat& right);
		friend Quat operator*(const Quat& left, const float scalar);
		friend Quat operator/(const Quat& left, const Quat& right);

		friend std::ostream& operator<<(std::ostream& stream, const Quat& q);

		Mat4 getMatrix();
		void getMatrix(Mat4& matrix);
		void getRotate(float& angle, Vec3& axis);

		static Quat Conjugate(const Quat& q);
		static Quat Inverse(const Quat& q);
		static Quat Normalize(const Quat& q);

		static Quat Lerp(const Quat& qA, const Quat& qB, float alpha);
		static Quat Slerp(const Quat& qA, const Quat& qB, float alpha);

		static float Quadrance(const Quat& q);

	private:
		static void clean(Quat& q);
	};
}