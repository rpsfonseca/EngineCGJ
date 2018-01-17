// Module responsible for drawing stuff

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "SimData.h"
#include "Camera.h"
#include <mutex>
//#include "GUIControls.h"
#include "Shader2.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Vec2.h"
#include "LightShafts.h"

#include "GLFW\glfw3.h"


class CloudRenderManager {
public:
	CloudRenderManager();
	bool initialize(const int gridX, const int gridY, const int gridZ);
	void terminate();
	void draw(const SimData& data, std::mutex& dataMutex,
		const double frameTime);
	inline void changeShowVRC() { showVRC = !showVRC; };

	LightShafts* lightShafts;
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
		const double frameTime, bool occlusion);
	void renderGUI();
	void defineRaycasterLayout(const GLuint shaderProgram);
	void defineGUILayout(const GLuint shaderProgram);

	void rightButtonUpdates();
	void arrowUpdates(float deltaTime);


	bool showVRC;

	float*** interpolatedData;
	GLFWwindow* window;
	Camera camera;
	//GUIControls controls;
	math::Mat4 perspectiveProjection;
	math::Vec3 sunPosition;
	math::Mat4 sunTransformation;
};

GLuint createVBO(float vertices[], int size);
GLuint createEBO(int elements[], int size);
void deleteVBOs();
void deleteEBOs();
void initializeTextures(GLuint volumeTexture, GLuint* planarTextures);
void deleteTextures(GLuint volumeTexture, GLuint* planarTextures);
void setUniform(const std::string name, const bool value);
void setUniform(const std::string name, const float value);
void setUniform(const std::string name, const math::Vec2 vector);
void setUniform(const std::string name, const math::Vec3 vector);
void setUniform(const std::string name, const math::Mat4 matrix);
float convertXToRelative(const int x);
float convertYToRelative(const int y);

#endif
