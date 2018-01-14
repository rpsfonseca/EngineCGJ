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
	math::Mat4 getLookAtMatrix() const;
	math::Vec3 getViewDirection() const;
	math::Vec3 getEyeLocation();

public:
	math::Vec4 cameraPoint;
	math::Vec4 lookAtPoint;
	math::Vec4 upAxis;

};
	math::Vec3 v4tov3(const math::Vec4& vector) ;
	math::Vec4 v3tov4(const math::Vec3& vector) ;
	math::Mat4 lookAt(math::Vec3 cameraPos, math::Vec3 lookAtPos, math::Vec3 upVec) ;

#endif
