#pragma once

#include "Camera.h"
#include "Renderer.h"
#include "SceneNode.h"

#include <memory>
#include <map>

class SceneManager
{
public:
	std::shared_ptr<Camera> currentCamera;
	std::shared_ptr<Renderer> renderer;

	unsigned int uniformBlockId;

	static SceneNode* rootSceneNode;
	static int nodeCounterId;

	std::vector<Mesh> meshes;

	std::map<std::string, SceneNode*> nodes;
public:
	SceneManager();
	SceneManager(std::shared_ptr<Renderer> rendererRef);
	~SceneManager();

	static SceneNode* createSceneNode(Model* model);
	static SceneNode* createSceneNode(Model* model, Vec3& startPos, Vec3& targetPos);

	void setupSceneManager();

	void updateScene();
	void renderScene();

	void toggleArcballCam();
	void toggleGimbalLock();
	void changeCameraProjection();
	void rotateCamera(float x, float y);
	void updateCamera(Camera_Movement movement);
	void updateAspectRatio(float aspectRatio);
};