#include "Mat3.h"
#include "MathUtils.h"

namespace math
{

	const Mat3 Mat3::Identity = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	Mat3::Mat3()
		: matrix {
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		}
	{
	}

	Mat3::Mat3(const float& _matrix)
		: matrix { _matrix }
	{
	}

	Mat3::Mat3(
		const float& _m0, const float& _m1, const float& _m2,
		const float& _m3, const float& _m4, const float& _m5,
		const float& _m6, const float& _m7, const float& _m8)
	{
		matrix[0] = _m0;
		matrix[1] = _m3;
		matrix[2] = _m6;
		matrix[3] = _m1;
		matrix[4] = _m4;
		matrix[5] = _m7;
		matrix[6] = _m2;
		matrix[7] = _m5;
		matrix[8] = _m8;
	}

	Mat3::~Mat3()
	{
	}

	Mat3 Mat3::operator-()
	{
		Mat3 result;

		result.matrix[0] = -this->matrix[0];
		result.matrix[1] = -this->matrix[1];
		result.matrix[2] = -this->matrix[2];
		result.matrix[3] = -this->matrix[3];
		result.matrix[4] = -this->matrix[4];
		result.matrix[5] = -this->matrix[5];
		result.matrix[6] = -this->matrix[6];
		result.matrix[7] = -this->matrix[7];
		result.matrix[8] = -this->matrix[8];

		return result;
	}

	Mat3& Mat3::operator=(const Mat3& other)
	{
		for (int i = 0; i < 9; i++)
		{
			matrix[i] = other.matrix[i];
		}
		return *this;
	}

	Mat3 operator+(const Mat3& left, const Mat3& right)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
		{
			result.matrix[i] = left.matrix[i] + right.matrix[i];
			result.matrix[i+3] = left.matrix[i + 3] + right.matrix[i + 3];
			result.matrix[i+6] = left.matrix[i + 6] + right.matrix[i + 6];
		}
		return result;
	}

	Mat3 operator-(const Mat3& left, const Mat3& right)
	{
		Mat3 result;
		for (int i = 0; i < 3; i++)
		{
			result.matrix[i] = left.matrix[i] - right.matrix[i];
			result.matrix[i + 3] = left.matrix[i + 3] - right.matrix[i + 3];
			result.matrix[i + 6] = left.matrix[i + 6] - right.matrix[i + 6];
		}
		return result;
	}

	Mat3 operator*(const Mat3& left, const Mat3& right)
	{
		Mat3 result;
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				result.matrix[col] += left.matrix[col + 3 * row] * right.matrix[row];
				result.matrix[col + 3] += left.matrix[col + 3 * row] * right.matrix[row + 3];
				result.matrix[col + 6] += left.matrix[col + 3 * row] * right.matrix[row + 6];
			}
		}
		return result;
	}

	Mat3 operator/(const Mat3& left, const Mat3& right)
	{
		Mat3 result;
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				result.matrix[col] += left.matrix[col + 3 * row] / right.matrix[row];
				result.matrix[col + 3] += left.matrix[col + 3 * row] / right.matrix[row + 3];
				result.matrix[col + 6] += left.matrix[col + 3 * row] / right.matrix[row + 6];
			}
		}
		return result;
	}

	Vec3 operator*(const Mat3 & left, const Vec3& right)
	{
		Vec3 result = Vec3(0.0f);

		result.x = left.matrix[0] * right.x + left.matrix[3] * right.y + left.matrix[6] * right.z;
		result.y = left.matrix[1] * right.x + left.matrix[4] * right.y + left.matrix[7] * right.z;
		result.z = left.matrix[2] * right.x + left.matrix[5] * right.y + left.matrix[8] * right.z;

		return result;
	}

	Vec3 operator/(const Mat3 & left, const Vec3 & right)
	{
		Vec3 result = Vec3(0.0f);
		float invX = 1.0f / right.x;
		float invY = 1.0f / right.y;
		float invZ = 1.0f / right.z;

		result.x = left.matrix[0] * invX + left.matrix[3] * invY + left.matrix[6] * invZ;
		result.y = left.matrix[1] * invX + left.matrix[4] * invY + left.matrix[7] * invZ;
		result.z = left.matrix[2] * invX + left.matrix[5] * invY + left.matrix[8] * invZ;

		return result;
	}

	Mat3 operator*(const Mat3& left, const float& scalar)
	{
		Mat3 result;

		for (int i = 0; i < 9; i++)
		{
			result.matrix[i] = left.matrix[i] * scalar;
		}

		return result;
	}

	Mat3 operator/(const Mat3& left, const float& scalar)
	{
		Mat3 result;

		float invScalar = 1.0f / scalar;
		for (int x = 0; x < 9; x++)
		{
			result.matrix[x] = left.matrix[x] * invScalar;
		}

		return result;
	}

	std::ostream& operator<<(std::ostream & stream, const Mat3& mat)
	{
		for (int i = 0; i < 3; i++)
		{
			stream << mat.matrix[i] << " " << mat.matrix[i + 3] << " " << mat.matrix[i + 6] << "\n";
		}
		return stream;
	}

	Mat3& Mat3::operator+=(const Mat3 & other)
	{
		for (int i = 0; i < 9; i++)
		{
			this->matrix[i] += other.matrix[i];
		}
		return *this;
	}

	Mat3& Mat3::operator-=(const Mat3 & other)
	{
		for (int i = 0; i < 9; i++)
		{
			this->matrix[i] -= other.matrix[i];
		}
		return *this;
	}

	Mat3 & Mat3::operator*=(const Mat3& other)
	{
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				this->matrix[col] += this->matrix[col + 3 * row] * other.matrix[row];
				this->matrix[col + 3] += this->matrix[col + 3 * row] * other.matrix[row + 3];
				this->matrix[col + 6] += this->matrix[col + 3 * row] * other.matrix[row + 6];
			}
		}
		return *this;
	}

	Mat3& Mat3::operator*=(const float & scalar)
	{
		for (int i = 0; i < 9; i++)
		{
			this->matrix[i] *= scalar;
		}
		return *this;
	}

	Mat3& Mat3::operator/=(const Mat3& other)
	{
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				this->matrix[col] += this->matrix[col + 3 * row] / other.matrix[row];
				this->matrix[col + 3] += this->matrix[col + 3 * row] / other.matrix[row + 3];
				this->matrix[col + 6] += this->matrix[col + 3 * row] / other.matrix[row + 6];
			}
		}
		return *this;
	}

	Mat3 & Mat3::operator/=(const float & scalar)
	{
		float invScalar = 1.0f / scalar;
		for (int i = 0; i < 9; i++)
		{
			this->matrix[i] *= invScalar;
		}
		return *this;
	}

	Mat3 Mat3::Inverse(const Mat3& mat)
	{
		Mat3 result;
		float invDet = 1.0f/Determinant(mat);

		result.matrix[0] =	Determinant(mat.matrix[4], mat.matrix[8], mat.matrix[7], mat.matrix[5]);
		result.matrix[1] =  -Determinant(mat.matrix[3], mat.matrix[8], mat.matrix[6], mat.matrix[5]);
		result.matrix[2] =  Determinant(mat.matrix[3], mat.matrix[7], mat.matrix[6], mat.matrix[4]);
		result.matrix[3] =  -Determinant(mat.matrix[1], mat.matrix[8], mat.matrix[7], mat.matrix[2]);
		result.matrix[4] =  Determinant(mat.matrix[0], mat.matrix[8], mat.matrix[6], mat.matrix[2]);
		result.matrix[5] =  -Determinant(mat.matrix[0], mat.matrix[5], mat.matrix[6], mat.matrix[1]);
		result.matrix[6] =	Determinant(mat.matrix[1], mat.matrix[5], mat.matrix[4], mat.matrix[2]);
		result.matrix[7] =  -Determinant(mat.matrix[0], mat.matrix[5], mat.matrix[3], mat.matrix[2]);
		result.matrix[8] =	Determinant(mat.matrix[0], mat.matrix[4], mat.matrix[3], mat.matrix[1]);

		result = Transpose(result);

		result *= invDet;
		
		/*result.matrix[0] = invDet * Determinant(mat.matrix[5], mat.matrix[7], mat.matrix[6], mat.matrix[8]);
		result.matrix[1] = invDet * Determinant(mat.matrix[7], mat.matrix[1], mat.matrix[8], mat.matrix[2]);
		result.matrix[2] = invDet * Determinant(mat.matrix[1], mat.matrix[4], mat.matrix[2], mat.matrix[5]);
		result.matrix[3] = invDet * Determinant(mat.matrix[6], mat.matrix[3], mat.matrix[8], mat.matrix[5]);
		result.matrix[4] = invDet * Determinant(mat.matrix[0], mat.matrix[6], mat.matrix[2], mat.matrix[8]);
		result.matrix[5] = invDet * Determinant(mat.matrix[3], mat.matrix[0], mat.matrix[5], mat.matrix[2]);
		result.matrix[6] = invDet * Determinant(mat.matrix[3], mat.matrix[6], mat.matrix[4], mat.matrix[7]);
		result.matrix[7] = invDet * Determinant(mat.matrix[6], mat.matrix[0], mat.matrix[7], mat.matrix[2]);
		result.matrix[8] = invDet * Determinant(mat.matrix[0], mat.matrix[3], mat.matrix[2], mat.matrix[4]);*/

		return result;
	}

	Mat3 Mat3::Transpose(const Mat3 & mat)
	{
		Mat3 result;

		result.matrix[0] = mat.matrix[0];
		result.matrix[1] = mat.matrix[3];
		result.matrix[2] = mat.matrix[6];
		result.matrix[3] = mat.matrix[1];
		result.matrix[4] = mat.matrix[4];
		result.matrix[5] = mat.matrix[7];
		result.matrix[6] = mat.matrix[2];
		result.matrix[7] = mat.matrix[5];
		result.matrix[8] = mat.matrix[8];

		return result;
	}

	float Mat3::Determinant(const Mat3& mat)
	{
		return (mat.matrix[0] * mat.matrix[4] * mat.matrix[8]) + (mat.matrix[3] * mat.matrix[7] * mat.matrix[2]) + (mat.matrix[6] * mat.matrix[1] * mat.matrix[5]) - (mat.matrix[6] * mat.matrix[4] * mat.matrix[2]) - (mat.matrix[3] * mat.matrix[1] * mat.matrix[8]) - (mat.matrix[0] * mat.matrix[7] * mat.matrix[5]);
	}

	float Mat3::Determinant(const float & a, const float & d, const float & b, const float & c)
	{
		return a*d - b*c;
	}
	Mat3 Mat3::RodriguezRotation(const Vec3& axis, const float angle)
	{
		Mat3 K = Mat3(
			0.0f, -axis.z, axis.y,
			axis.z, 0.0f, -axis.x,
			-axis.y, axis.x, 0.0f
		);

		Mat3 KSquared = K * K; /*Mat3(
			-(axis.z * axis.z) * -(axis.y * axis.y), axis.y * axis.x, axis.z * axis.x,
			axis.x * axis.y, -(axis.z * axis.z) * -(axis.x * axis.x), axis.z * axis.y,
			axis.x * axis.z, axis.y * axis.z, -(axis.y * axis.y) * -(axis.x * axis.x)
		);*/

		return Mat3::Identity + (K * std::sin(MathUtils::radians(angle))) + (KSquared * (1 - std::cos(MathUtils::radians(angle))));
	}
}