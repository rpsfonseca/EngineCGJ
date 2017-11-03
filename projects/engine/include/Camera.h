#pragma once

#include "Vec3.h"
#include "Mat4.h"
#include "MathUtils.h"
#include "GL\glew.h"

#include "Quat.h"

#include <vector>

using namespace math;

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

enum Projection_Type
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// Camera attributes
	Vec3 Position;
	Vec3 Front;
	Vec3 Up;
	Vec3 Right;
	Vec3 WorldUp;

	// Euler angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	float aspectRatio;

	Projection_Type currentProjectionType;

	bool arcballCam = true;
	bool gimbalLock = true;

	Quat cameraQuaternion;

	Camera(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Vec3 up = Vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	//Camera();
	~Camera();

	Mat4 getViewMatrix();
	Mat4 getProjectionMatrix();

	void processKeyboard(Camera_Movement direction, float deltaTime);

	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void processMouseScroll(float yoffset);

	void changeProjection();
	void toggleArcballCam();
	void toggleGimbalLock();

private:
	void updateCameraVectors();
};

