#include "Camera.h"
#include "../include/MathUtils.h""

#include <cmath>
#include <iostream>

Camera::~Camera()
{
}

Mat4 Camera::getViewMatrix()
{
	Vec3 zAxis = (Position - Vec3(0.0f)).Normalize();
	//std::cout << "ZAXIS: " << zAxis << std::endl;
	Vec3 xAxis = Vec3::CrossProduct(WorldUp, zAxis).Normalize();
	//std::cout << "XAXIS: " << xAxis << std::endl;
	Vec3 yAxis = Vec3::CrossProduct(zAxis, xAxis);
	//std::cout << "YAXIS: " << yAxis << std::endl;

	Mat4 translation = Mat4::TranslationMatrix(-Position);
	Mat4 rotation = 
	{
		xAxis.x,            xAxis.y,            xAxis.z,       0.0f,
		yAxis.x,            yAxis.y,            yAxis.z,       0.0f,
		zAxis.x,            zAxis.y,            zAxis.z,       0.0f,
		0.0f,0.0f,0.0f,  1.0f
	};

	Mat4 viewMatrix = rotation * translation;
	/*Mat4 viewMatrix =
	{
		xAxis.x,            xAxis.y,            xAxis.z,       0.0f,
		yAxis.x,            yAxis.y,            yAxis.z,       0.0f,
		zAxis.x,            zAxis.y,            zAxis.z,       0.0f,
		-Vec3::DotProduct(xAxis, Position), -Vec3::DotProduct(yAxis, Position), -Vec3::DotProduct(zAxis, Position),  1.0f
	};*/

	return viewMatrix;
}

Mat4 Camera::getProjectionMatrix()
{
	Mat4 projectionMatrix = Mat4::perspective(30.0f, 640.0f / 480.0f, 1.0f, 10.0f);
	return projectionMatrix;
}

void Camera::updateCameraVectors()
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