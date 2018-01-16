#include "Camera2.h"

Camera2::Camera2() :

	cameraPoint(math::Vec4(0.0f, 1.0f, .0f, 1.0f)),
	lookAtPoint(math::Vec4(0.0f, 0.0f, 0.0f, 1.0f)),
	upAxis(math::Vec4(0.0f, 1.0f, 0.0f, 0.0f))

	{}

void Camera2::initialize(const int gridX, const int gridY, const int gridZ) {

	// Look vector located at the middle of the grid
	cameraPoint.x -= 0.5;
	cameraPoint.y -= 0.5;
	cameraPoint.z -= -0.5;

	lookAtPoint.x -= 0.5;
	lookAtPoint.y -= 0.5;
	lookAtPoint.z -= 0.5;

}

math::Mat4 Camera2::getLookAtMatrix() const {


	return lookAt(
		v4tov3(cameraPoint),
		v4tov3(lookAtPoint),
		v4tov3(upAxis)
	);

}

math::Vec3 Camera2::getViewDirection() const {
	math::Vec4 auxVec = math::Vec4(cameraPoint.x - lookAtPoint.x, cameraPoint.y - lookAtPoint.y, cameraPoint.z - lookAtPoint.z, cameraPoint.w - lookAtPoint.w);
	float mag = std::sqrt(auxVec.x * auxVec.x + auxVec.y + auxVec.y + auxVec.z * auxVec.z + auxVec.w * auxVec.w);
	auxVec = math::Vec4(auxVec.x/mag, auxVec.y/mag, auxVec.z/mag, auxVec.w/mag);

	return v4tov3(auxVec);
}

math::Vec3 Camera2::getEyeLocation()
{
	 return v4tov3(cameraPoint);
}




math::Mat4 lookAt(math::Vec3 cameraPos, math::Vec3 lookAtPos, math::Vec3 upVec) 
{
	math::Vec3 zAxis = (lookAtPos - cameraPos).Normalize();
	math::Vec3 xAxis = (math::Vec3::CrossProduct(upVec,zAxis)).Normalize();
	math::Vec3 yAxis = math::Vec3::CrossProduct(zAxis, xAxis);

	math::Mat4 m1 = math::Mat4( 1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								-cameraPos.x, -cameraPos.y, -cameraPos.z, 1);
	math::Mat4 m2 = math::Mat4( xAxis.x, yAxis.x, zAxis.x, 0,
								xAxis.y, yAxis.y, zAxis.y, 0,
								xAxis.z, yAxis.z, zAxis.z, 0,
								0, 0, 0, 1);


	return m2*m1;
}

math::Vec3 v4tov3(const math::Vec4& v1) {
	return math::Vec3(v1.x, v1.y, v1.z);
}

math::Vec4 v3tov4(const math::Vec3& v1) {
	return math::Vec4(v1.x, v1.y, v1.z, 1.0f);
}
