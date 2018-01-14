#ifndef CAMERA2_H
#define CAMERA2_H

#include "Vec3.h"
#include "Mat4.h"
#include "MathUtils.h"
#include "GLFW\glfw3.h"

class Camera2 {
public:
	Camera2();
	void initialize(const int gridX, const int gridY, const int gridZ);
	void updateCamera();
	math::Mat4 getLookAtMatrix() const;
	math::Vec3 getViewDirection() const;
	inline math::Vec3 getEyeLocation() { return v4tov3(cameraPoint); };
private:
	math::Vec4 cameraPoint;
	math::Vec4 lookAtPoint;
	math::Vec4 upAxis;

	int prevMouseX;
	int prevMouseY;
	int prevWheel;
	bool prevMousePressed;

	math::Vec3 v4tov3(const math::Vec4& vector) const;
	math::Vec4 v3tov4(const math::Vec3& vector) const;

	void rightButtonUpdates();
	void scrollWheelUpdates();
	void arrowUpdates();

	math::Mat4 lookAt(math::Vec3 cameraPos, math::Vec3 lookAtPos, math::Vec3 upVec) const;
};

#endif
