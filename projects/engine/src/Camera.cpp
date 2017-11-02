#include "Camera.h"
#include "../include/MathUtils.h"

#include <cmath>
#include <iostream>

Camera::~Camera()
{
}

Mat4 Camera::getViewMatrix()
{
	Mat4 viewMatrix;
	if (gimbalLock)
	{
		//Vec3 zAxis = (Position - (Position + Front)).Normalize();
		Vec3 zAxis = (Position - Vec3(0.0f, 0.0f, 0.0f)).Normalize();
		Vec3 xAxis = Vec3::CrossProduct(WorldUp, zAxis).Normalize();
		Vec3 yAxis = Vec3::CrossProduct(zAxis, xAxis);

		Mat4 translation = Mat4::TranslationMatrix(-Position);
		Mat4 rotation =
		{
			xAxis.x,            xAxis.y,            xAxis.z,       0.0f,
			yAxis.x,            yAxis.y,            yAxis.z,       0.0f,
			zAxis.x,            zAxis.y,            zAxis.z,       0.0f,
			0.0f,0.0f,0.0f,  1.0f
		};

		viewMatrix = rotation * translation;
		
		viewMatrix = translation * Mat4(Mat3::RodriguezRotation(Vec3::UnitX, Pitch)) * Mat4(Mat3::RodriguezRotation(Vec3::UnitY, Yaw));

		std::cout << viewMatrix << std::endl;
	}
	else
	{

	}

	return viewMatrix;
}

Mat4 Camera::getProjectionMatrix()
{
	Mat4 projectionMatrix;
	if (currentProjectionType == Projection_Type::PERSPECTIVE)
	{
		projectionMatrix = Mat4::perspective(30.0f, aspectRatio, 0.1f, 100.0f);
	}
	else
	{
		projectionMatrix = Mat4::orthographic(2.0f, -2.0f, 2.0f, -2.0f, 0.1f, 100.0f);
	}

	return projectionMatrix;
}

void Camera::updateCameraVectors()
{
	if (!arcballCam)
	{
		// Calculate the new Front vector
		Vec3 front;
		front.x = std::cos(MathUtils::radians(Yaw)) * std::cos(MathUtils::radians(Pitch));
		front.y = std::sin(MathUtils::radians(Pitch));
		front.z = std::sin(MathUtils::radians(Yaw)) * std::cos(MathUtils::radians(Pitch));
		Front = front.Normalize();

		// Also re-calculate the Right and Up vector
		Right = Vec3::CrossProduct(Front, WorldUp).Normalize(); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = Vec3::CrossProduct(Right, Front).Normalize();
	}
	else
	{
		std::cout << std::sin(MathUtils::radians(Pitch)) << std::endl;
		Vec3 front;
		front.x = std::cos(MathUtils::radians(Yaw)) * std::cos(MathUtils::radians(Pitch)) * 5.0f;
		front.y = std::sin(MathUtils::radians(Pitch)) * 5.0f;
		front.z = std::sin(MathUtils::radians(Yaw)) * std::cos(MathUtils::radians(Pitch)) * 5.0f;

		//Position = front;

		//Up = Vec3(std::cos(MathUtils::radians(Yaw)), std::sin(MathUtils::radians(Yaw)), 1.0f);

		/*Quat q1 = Quat(Yaw, Up);
		Quat q2 = Quat(Pitch, Right);

		Mat4 matQ1;
		Mat4 matQ2;

		q1.getMatrix(matQ1);
		q2.getMatrix(matQ2);

		Front = matQ2 * Front;
		Front = matQ1 * Front;

		Position = Front;*/
	}
}

void Camera::changeProjection()
{
	currentProjectionType = currentProjectionType == PERSPECTIVE ? ORTHOGRAPHIC : PERSPECTIVE;
}