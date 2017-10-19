#include "Mat4.h"
namespace math
{
	const Mat4 Identity[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Mat4::Mat4()
		: matrix{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	}
	{
	}

	Mat4::Mat4(const float& _matrix)
		: matrix{ _matrix }
	{
	}


	Mat4::~Mat4()
	{
	}

	Mat4 Mat4::operator-()
	{
		Mat4 result;

		result.matrix[0] = -this->matrix[0];
		result.matrix[1] = -this->matrix[1];
		result.matrix[2] = -this->matrix[2];
		result.matrix[3] = -this->matrix[3];
		result.matrix[4] = -this->matrix[4];
		result.matrix[5] = -this->matrix[5];
		result.matrix[6] = -this->matrix[6];
		result.matrix[7] = -this->matrix[7];
		result.matrix[8] = -this->matrix[8];
		result.matrix[9] = -this->matrix[9];
		result.matrix[10] = -this->matrix[10];
		result.matrix[11] = -this->matrix[11];
		result.matrix[12] = -this->matrix[12];
		result.matrix[13] = -this->matrix[13];
		result.matrix[14] = -this->matrix[14];
		result.matrix[15] = -this->matrix[15];

		return result;
	}

	Mat4& Mat4::operator=(const Mat4& other)
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] = other.matrix[i];
		}
		return *this;
	}

	Mat4 operator+(const Mat4& left, const Mat4& right)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			result.matrix[i] = left.matrix[i] + right.matrix[i];
			result.matrix[i + 4] = left.matrix[i + 4] + right.matrix[i + 4];
			result.matrix[i + 8] = left.matrix[i + 8] + right.matrix[i + 8];
			result.matrix[i + 12] = left.matrix[i + 12] + right.matrix[i + 12];
		}
		return result;
	}

	Mat4 operator-(const Mat4& left, const Mat4& right)
	{
		Mat4 result;
		for (int i = 0; i < 4; i++)
		{
			result.matrix[i] = left.matrix[i] - right.matrix[i];
			result.matrix[i + 4] = left.matrix[i + 4] - right.matrix[i + 4];
			result.matrix[i + 8] = left.matrix[i + 8] - right.matrix[i + 8];
			result.matrix[i + 12] = left.matrix[i + 12] - right.matrix[i + 12];
		}
		return result;
	}

	Mat4 operator*(const Mat4& left, const Mat4& right)
	{
		Mat4 result;
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				result.matrix[col] += left.matrix[col + 4 * row] * right.matrix[row];
				result.matrix[col + 4] += left.matrix[col + 4 * row] * right.matrix[row + 4];
				result.matrix[col + 8] += left.matrix[col + 4 * row] * right.matrix[row + 8];
				result.matrix[col + 12] += left.matrix[col + 4 * row] * right.matrix[row + 12];
			}
		}
		return result;
	}

	Mat4 operator/(const Mat4& left, const Mat4& right)
	{
		Mat4 result;
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				result.matrix[col] += left.matrix[col + 4 * row] / right.matrix[row];
				result.matrix[col + 4] += left.matrix[col + 4 * row] / right.matrix[row + 4];
				result.matrix[col + 8] += left.matrix[col + 4 * row] / right.matrix[row + 8];
				result.matrix[col + 12] += left.matrix[col + 4 * row] / right.matrix[row + 12];
			}
		}
		return result;
	}

	Vec3 operator*(const Mat4 & left, const Vec3& right)
	{
		Vec3 result = Vec3(0.0f, 0.0f, 0.0f);
		float invW = 1.0f / (left.matrix[3] * right.x + left.matrix[7] * right.y + left.matrix[11] * right.z + left.matrix[15]);
		result.x = (left.matrix[0] * right.x + left.matrix[4] * right.y + left.matrix[8] * right.z + left.matrix[12]) * invW;
		result.y = (left.matrix[1] * right.x + left.matrix[5] * right.y + left.matrix[9] * right.z + left.matrix[13]) * invW;
		result.z = (left.matrix[2] * right.x + left.matrix[6] * right.y + left.matrix[10] * right.z + left.matrix[14]) * invW;
		return result;
	}

	Vec4 operator*(const Mat4 & left, const Vec4& right)
	{
		Vec4 result = Vec4();
		result.x = left.matrix[0] * right.x + left.matrix[4] * right.y + left.matrix[8] * right.z + left.matrix[12] * right.w;
		result.y = left.matrix[1] * right.x + left.matrix[5] * right.y + left.matrix[9] * right.z + left.matrix[13] * right.w;
		result.z = left.matrix[2] * right.x + left.matrix[6] * right.y + left.matrix[10] * right.z + left.matrix[14] * right.w;
		result.w = left.matrix[3] * right.x + left.matrix[7] * right.y + left.matrix[11] * right.z + left.matrix[15] * right.w;
		return result;
	}

	Vec3 operator/(const Mat4 & left, const Vec3 & right)
	{
		Vec3 result = Vec3(0.0f, 0.0f, 0.0f);
		for (int row = 0; row < 3; row++)
		{
			result.x += left.matrix[row] / right.x;
			result.y += left.matrix[row + 3] / right.y;
			result.z += left.matrix[row + 6] / right.z;
		}
		return result;
	}

	Mat4 operator*(const Mat4& left, const float& scalar)
	{
		Mat4 result;
		for (int i = 0; i < 16; i++)
		{
			result.matrix[i] = left.matrix[i] * scalar;
		}
		return result;
	}

	Mat4 operator/(const Mat4& left, const float& scalar)
	{
		Mat4 result;
		float invScalar = 1.0f / scalar;
		for (int x = 0; x < 16; x++)
		{
			result.matrix[x] = left.matrix[x] * invScalar;
		}
		return result;
	}

	std::ostream& operator<<(std::ostream & stream, const Mat4& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			stream << mat.matrix[i] << " " << mat.matrix[i + 4] << " " << mat.matrix[i + 8] << " " << mat.matrix[i + 12] << "\n";
		}
		return stream;
	}

	Mat4& Mat4::operator+=(const Mat4 & other)
	{
		for (int i = 0; i < 4; i++)
		{
			this->matrix[i] += other.matrix[i];
			this->matrix[i + 4] += other.matrix[i + 4];
			this->matrix[i + 8] += other.matrix[i + 8];
			this->matrix[i + 12] += other.matrix[i + 12];
		}
		return *this;
	}

	Mat4& Mat4::operator-=(const Mat4 & other)
	{
		for (int i = 0; i < 4; i++)
		{
			this->matrix[i] -= other.matrix[i];
			this->matrix[i + 4] -= other.matrix[i + 4];
			this->matrix[i + 8] -= other.matrix[i + 8];
			this->matrix[i + 12] -= other.matrix[i + 12];
		}
		return *this;
	}

	Mat4 & Mat4::operator*=(const Mat4& other)
	{
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				this->matrix[col] += this->matrix[col + 4 * row] * other.matrix[row];
				this->matrix[col + 4] += this->matrix[col + 4 * row] * other.matrix[row + 4];
				this->matrix[col + 8] += this->matrix[col + 4 * row] * other.matrix[row + 8];
				this->matrix[col + 12] += this->matrix[col + 4 * row] * other.matrix[row + 12];
			}
		}
		return *this;
	}

	Mat4& Mat4::operator*=(const float & scalar)
	{
		for (int i = 0; i < 16; i++)
		{
			this->matrix[i] *= scalar;
		}
		return *this;
	}

	Mat4& Mat4::operator/=(const Mat4& other)
	{
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				this->matrix[col] += this->matrix[col + 4 * row] / other.matrix[row];
				this->matrix[col + 4] += this->matrix[col + 4 * row] / other.matrix[row + 4];
				this->matrix[col + 8] += this->matrix[col + 4 * row] / other.matrix[row + 8];
				this->matrix[col + 12] += this->matrix[col + 4 * row] / other.matrix[row + 12];
			}
		}
		return *this;
	}

	Mat4 & Mat4::operator/=(const float & scalar)
	{
		float invScalar = 1.0f / scalar;
		for (int i = 0; i < 16; i++)
		{
			this->matrix[i] *= invScalar;
		}
		return *this;
	}

	Mat3 Mat4::Upper3x3Matrix()
	{
		Mat3 result;
		result.matrix[0] = matrix[0];
		result.matrix[1] = matrix[1];
		result.matrix[2] = matrix[2];
		result.matrix[3] = matrix[4];
		result.matrix[4] = matrix[5];
		result.matrix[5] = matrix[6];
		result.matrix[6] = matrix[8];
		result.matrix[7] = matrix[9];
		result.matrix[8] = matrix[10];
		return result;
	}

	Mat4 Mat4::RotationMatrixAboutAxis(const Axis axis, const float angle)
	{
		Mat4 result;

		float angleRad = angle * 0.0174532925f;
		float angleCos = std::cos(angleRad);
		float angleSin = std::sin(angleRad);

		switch (axis)
		{
		case AxisX:
			result.matrix[0] = 1.0f;
			result.matrix[5] = angleCos;
			result.matrix[10] = angleCos;
			result.matrix[6] = angleSin;
			result.matrix[9] = -angleSin;
			break;
		case AxisY:
			result.matrix[5] = 1.0f;
			result.matrix[0] = angleCos;
			result.matrix[10] = angleCos;
			result.matrix[8] = angleSin;
			result.matrix[2] = -angleSin;
			break;
		case AxisZ:
			result.matrix[10] = 1.0f;
			result.matrix[0] = angleCos;
			result.matrix[5] = angleCos;
			result.matrix[1] = angleSin;
			result.matrix[4] = -angleSin;
			break;
		default:
			break;
		}

		result.matrix[15] = 1.0f;

		return result;
	}

	Mat4 Mat4::RotationMatrixFromAxisAngle(const Vec3& axis, const float angle)
	{
		Mat4 result;
		
		float angleRad = angle * 0.0174532925f;
		float angleCos = std::cos(angleRad);
		float oneMinusCos = 1 - angleCos;
		float angleSin = std::sin(angleRad);

		result.matrix[0] = angleCos + ((axis.x * axis.x) * oneMinusCos);
		result.matrix[1] = axis.y * axis.x * oneMinusCos + (axis.z * angleSin);
		result.matrix[2] = axis.z * axis.x * oneMinusCos - (axis.y * angleSin);
		result.matrix[3] = axis.x * axis.y * oneMinusCos - (axis.z * angleSin);
		result.matrix[4] = angleCos + ((axis.y * axis.y) * oneMinusCos);
		result.matrix[5] = axis.z * axis.y * oneMinusCos + (axis.x * angleSin);
		result.matrix[6] = axis.x * axis.z * oneMinusCos + (axis.y * angleSin);
		result.matrix[7] = axis.y * axis.z * oneMinusCos - (axis.x * angleSin);
		result.matrix[8] = angleCos + ((axis.z * axis.z) * oneMinusCos);

		return result;
	}

	Mat4 Mat4::ScaleMatrix(const Vec3& scaleVector)
	{
		Mat4 result;

		result.matrix[0] = scaleVector.x;
		result.matrix[5] = scaleVector.y;
		result.matrix[10] = scaleVector.z;
		result.matrix[15] = 1.0f;

		return result;
	}

	Mat4 Mat4::ScaleMatrix(const float& x, const float& y, const float& z)
	{
		Mat4 result;

		result.matrix[0] = x;
		result.matrix[5] = y;
		result.matrix[10] = z;
		result.matrix[15] = 1.0f;

		return result;
	}

	Mat4 Mat4::TranslationMatrix(const Vec3& translationVector)
	{
		Mat4 result;
		
		result.matrix[12] = translationVector.x;
		result.matrix[13] = translationVector.y;
		result.matrix[14] = translationVector.z;

		result.matrix[0] = 1.0f;
		result.matrix[5] = 1.0f;
		result.matrix[10] = 1.0f;
		result.matrix[15] = 1.0f;

		return result;
	}

	Mat4 Mat4::TranslationMatrix(const float& x, const float& y, const float& z)
	{
		Mat4 result;

		result.matrix[12] = x;
		result.matrix[13] = y;
		result.matrix[14] = z;

		result.matrix[0] = 1.0f;
		result.matrix[5] = 1.0f;
		result.matrix[10] = 1.0f;
		result.matrix[15] = 1.0f;

		return result;
	}
}