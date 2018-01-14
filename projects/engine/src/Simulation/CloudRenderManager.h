// Module responsible for drawing stuff

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "SimData.h"
#include "Camera2.h"
#include <mutex>
//#include "GUIControls.h"
#include "Shader2.h"
#include "Mat4.h"
#include "Vec3.h"
#include "GLFW\glfw3.h"


class CloudRenderManager {
public:
	CloudRenderManager();
	bool initialize(const int gridX, const int gridY, const int gridZ);
	void terminate();
	void draw(const SimData& data, std::mutex& dataMutex,
		const double frameTime);
	inline void changeShowVRC() { showVRC = !showVRC; };
private:
	const char * windowTitle;

	Shader2 shaderManager;
	GLuint raycasterShaderProgram;
	GLuint guiShaderProgram;
	GLuint VAOs[2];
	GLuint cubeVBO;
	GLuint guiVBO;

	GLuint volumeTexture;
	GLuint planarTextures[3];

	const float nearPlane;
	const float farPlane;

	const float fieldOfView;
	const float tanFOV;

	void interpolateCloudData(const SimData& data,
		const double frameTime);
	void renderRayCastingClouds(const SimData& data,
		const double frameTime);
	void renderGUI();
	void defineRaycasterLayout(const GLuint shaderProgram);
	void defineGUILayout(const GLuint shaderProgram);

	bool showVRC;

	float*** interpolatedData;
	GLFWwindow* window;
	Camera2 camera;
	//GUIControls controls;
	math::Mat4 perspectiveProjection;
	math::Vec3 sunPosition;
	math::Mat4 sunTransformation;
};

#endif#pragma once
