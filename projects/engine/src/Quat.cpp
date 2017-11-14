#include "Mat4.h"
#include "Quat.h"

#include "MathUtils.h"

#include <iostream>

namespace math
{
	Quat::Quat()
		: v{ 0.0f, 0.0f, 0.0f, 1.0f }
	{
	}

	Quat::Quat(float x, float y, float z, float w)
		: v{x, y, z, w}
	{
	}

	Quat::Quat(const Vec4 & v)
		: v(v)
	{
	}

	Quat::Quat(float angle, const Vec3& axis)
	{
		// TODO: Axis normalization

		float angleRad = MathUtils::radians(angle) / 2.0f;
		float s = std::sin(angleRad);
		
		*this = { axis.x * s, axis.y * s, axis.z * s, std::cos(angleRad) };

		clean(*this);

		*this = Normalize(*this);
	}

	Quat::~Quat()
	{
	}

	Quat operator+(const Quat& left, const Quat& right)
	{
		return Quat(left.v.x + right.v.x, left.v.y + right.v.y, left.v.z + right.v.z, left.v.w + right.v.w);
	}

	Quat operator-(const Quat& left, const Quat& right)
	{
		return Quat(left.v.x + right.v.x, left.v.y + right.v.y, left.v.z + right.v.z, left.v.w + right.v.w);
	}

	Quat operator*(const Quat& left, const Quat& right)
	{
		Quat q;

		q.v.w = left.v.w * right.v.w - left.v.x * right.v.x - left.v.y * right.v.y - left.v.z * right.v.z;
		q.v.x = left.v.w * right.v.x + left.v.x * right.v.w + left.v.y * right.v.z - left.v.z * right.v.y;
		q.v.y = left.v.w * right.v.y + left.v.y * right.v.w + left.v.z * right.v.x - left.v.x * right.v.z;
		q.v.z = left.v.w * right.v.z + left.v.z * right.v.w + left.v.x * right.v.y - left.v.y * right.v.x;

		return q;
	}

	Quat operator*(const Quat& left, const float scalar)
	{
		Quat q;

		q.v.w = left.v.w * scalar;
		q.v.x = left.v.x * scalar;
		q.v.y = left.v.y * scalar;
		q.v.z = left.v.z * scalar;

		return q;
	}

	Quat operator/(const Quat& left, const Quat& right)
	{
		return Quat(left.v.x + right.v.x, left.v.y + right.v.y, left.v.z + right.v.z, left.v.w + right.v.w);
	}

	std::ostream& operator<<(std::ostream& stream, const Quat& q)
	{
		stream << "Quat(" << q.v.w << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z << ")";
		return stream;
	}

	Mat4 Quat::getMatrix()
	{
		Mat4 matrix;
		Quat qNormalized = Quat::Normalize(*this);

		float xx = qNormalized.v.x * qNormalized.v.x;
		float xy = qNormalized.v.x * qNormalized.v.y;
		float xz = qNormalized.v.x * qNormalized.v.z;
		float xt = qNormalized.v.x * qNormalized.v.w;
		float yy = qNormalized.v.y * qNormalized.v.y;
		float yz = qNormalized.v.y * qNormalized.v.z;
		float yt = qNormalized.v.y * qNormalized.v.w;
		float zz = qNormalized.v.z * qNormalized.v.z;
		float zt = qNormalized.v.z * qNormalized.v.w;

		matrix.matrix[0] = 1.0f - 2.0f * (yy + zz);
		matrix.matrix[1] = 2.0f * (xy + zt);
		matrix.matrix[2] = 2.0f * (xz - yt);
		matrix.matrix[3] = 0.0f;

		matrix.matrix[4] = 2.0f * (xy - zt);
		matrix.matrix[5] = 1.0f - 2.0f * (xx + zz);
		matrix.matrix[6] = 2.0f * (yz + xt);
		matrix.matrix[7] = 0.0f;

		matrix.matrix[8] = 2.0f * (xz + yt);
		matrix.matrix[9] = 2.0f * (yz - xt);
		matrix.matrix[10] = 1.0f - 2.0f * (xx + yy);
		matrix.matrix[11] = 0.0f;

		matrix.matrix[12] = 0.0f;
		matrix.matrix[13] = 0.0f;
		matrix.matrix[14] = 0.0f;
		matrix.matrix[15] = 1.0f;

		return matrix;
	}

	void Quat::getMatrix(Mat4& matrix)
	{
		Quat qNormalized = Quat::Normalize(*this);

		float xx = qNormalized.v.x * qNormalized.v.x;
		float xy = qNormalized.v.x * qNormalized.v.y;
		float xz = qNormalized.v.x * qNormalized.v.z;
		float xt = qNormalized.v.x * qNormalized.v.w;
		float yy = qNormalized.v.y * qNormalized.v.y;
		float yz = qNormalized.v.y * qNormalized.v.z;
		float yt = qNormalized.v.y * qNormalized.v.w;
		float zz = qNormalized.v.z * qNormalized.v.z;
		float zt = qNormalized.v.z * qNormalized.v.w;

		matrix.matrix[0] = 1.0f - 2.0f * (yy + zz);
		matrix.matrix[1] = 2.0f * (xy + zt);
		matrix.matrix[2] = 2.0f * (xz - yt);
		matrix.matrix[3] = 0.0f;

		matrix.matrix[4] = 2.0f * (xy - zt);
		matrix.matrix[5] = 1.0f - 2.0f * (xx + zz);
		matrix.matrix[6] = 2.0f * (yz + xt);
		matrix.matrix[7] = 0.0f;

		matrix.matrix[8] = 2.0f * (xz + yt);
		matrix.matrix[9] = 2.0f * (yz - xt);
		matrix.matrix[10] = 1.0f - 2.0f * (xx + yy);
		matrix.matrix[11] = 0.0f;

		matrix.matrix[12] = 0.0f;
		matrix.matrix[13] = 0.0f;
		matrix.matrix[14] = 0.0f;
		matrix.matrix[15] = 1.0f;
	}

	void Quat::getRotate(float & angle, Vec3 & axis)
	{
		Quat qNorm = Normalize(*this);

		angle = MathUtils::degrees(2.0f * std::acos(qNorm.v.w));

		float s = sqrt(1.0f - qNorm.v.w*qNorm.v.w);
		if (s < Q_THRESHOLD)
		{
			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
		}
		else
		{
			axis.x = qNorm.v.x / s;
			axis.y = qNorm.v.y / s;
			axis.z = qNorm.v.z / s;
		}
	}

	Quat Quat::Conjugate(const Quat& q)
	{
		Quat conj = Quat(-q.v.x, -q.v.y, -q.v.z, q.v.w);
		return conj;
	}

	Quat Quat::Inverse(const Quat& q)
	{
		return Conjugate(q) * (1.0f / Quadrance(q));
	}

	Quat Quat::Normalize(const Quat & q)
	{
		return q * (1.0f / std::sqrt(Quadrance(q)));
	}

	Quat Quat::Lerp(const Quat& qA, const Quat& qB, float alpha)
	{
		float cos_angle = (qA.v.x * qB.v.x) + (qA.v.y * qB.v.y) + (qA.v.z * qB.v.z) + (qA.v.w * qB.v.w);
		float alpha0 = 1.0f - alpha;
		float alpha1 = cos_angle > 0.0f ? alpha : -alpha;

		Quat q = (qA * alpha0) + (qB * alpha1);
		return Normalize(q);
	}

	Quat Quat::Slerp(const Quat& qA, const Quat& qB, float alpha)
	{
		float angle = std::acos((qA.v.x * qB.v.x) + (qA.v.y * qB.v.y) + (qA.v.z * qB.v.z) + (qA.v.w * qB.v.w));
		float alpha0 = sin((1.0f - alpha)*angle) / sin(angle);
		float alpha1 = sin(alpha*angle) / sin(angle);

		Quat q = (qA * alpha0) + (qB * alpha1);
		return Normalize(q);
	}

	float Quat::Quadrance(const Quat& q)
	{
		return q.v.w * q.v.w + q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z;
	}

	void Quat::clean(Quat& q)
	{
		if (std::fabs(q.v.w) < Q_THRESHOLD) q.v.w = 0.0f;
		if (std::fabs(q.v.x) < Q_THRESHOLD) q.v.x = 0.0f;
		if (std::fabs(q.v.y) < Q_THRESHOLD) q.v.y = 0.0f;
		if (std::fabs(q.v.z) < Q_THRESHOLD) q.v.z = 0.0f;
	}

}