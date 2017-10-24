#include "Mat3.h"

#include "Mat2.h"
#include "Mat4.h"
#include "Vec4.h"
#include "Application.h"

#include <iostream>
#include <vector>
using namespace math;

int main()
{
	/*Mat3 mat1 = Mat3();
	Mat3 mat2 = Mat3();

	mat1.matrix[0] = 0;
	mat1.matrix[1] = 3;
	mat1.matrix[2] = 6;
	mat1.matrix[3] = 1;
	mat1.matrix[4] = 4;
	mat1.matrix[5] = 7;
	mat1.matrix[6] = 2;
	mat1.matrix[7] = 5;
	mat1.matrix[8] = 8;

	mat2.matrix[0] = 0;
	mat2.matrix[1] = 1;
	mat2.matrix[2] = 2;
	mat2.matrix[3] = 3;
	mat2.matrix[4] = 4;
	mat2.matrix[5] = 5;
	mat2.matrix[6] = 6;
	mat2.matrix[7] = 7;
	mat2.matrix[8] = 8;

	Mat3 aux = mat1 * mat2;

	std::cout << aux << std::endl;
	std::cout << std::endl;
	mat2 += mat2;
	std::cout << mat2 << std::endl;*/

	/*Vec3 Vi = Vec3(0.5f, 0.0f, 0.0f);
	Vec4 Vi4 = Vec4(Vi);
	Vec3 Ni = Vec3(0.0f, 1.0f, 0.0f);

	Mat4 Translation = Mat4::TranslationMatrix(Vec3(1.0f, 0.0f, 0.0f));

	Mat4 Rotation = Mat4::RotationMatrixAboutAxis(Axis::AxisY, 90.0f);

	std::cout << Rotation << std::endl;

	Mat4 Scale = Mat4::ScaleMatrix(Vec3(2.0f, 2.0f, 2.0f));

	Mat4 modelMatrix = Translation*Rotation*Scale;

	Mat3 Normal = modelMatrix.Upper3x3Matrix();
	Normal = Normal.Inverse(Normal);
	Normal = Normal.Transpose(Normal);

	std::cout << modelMatrix << std::endl;
	std::cout << modelMatrix * Vi4 << std::endl;

	std::cout << std::endl;

	std::cout << Normal << std::endl;
	std::cout << Normal * Ni << std::endl;*/

	Application app = Application(3, 3);
	app.setupApp();
	app.mainLoop();
	exit(EXIT_SUCCESS);
}