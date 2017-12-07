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

	static SceneNode* rootSceneNode; /** The root node of our node hierarchy */
	static int nodeCounterId; /** Counter to keep track of the current node id to give to a new node */

	std::map<std::string, SceneNode*> nodes; /** Hashtable to store all scene nodes */
public:
	/**
		SceneManager constructor. Only here because we need it to be able to declare a variable of this type.
	*/
	SceneManager();

	/**
		SceneManager constructor.
		Sets the renderer member with the shared pointer passed as param.
		Creates the scene camera as a shared pointer.
		This is the one that needs to be used;

		@param rendererRef Shared pointer to the renderer being used.
	*/
	SceneManager(std::shared_ptr<Renderer> rendererRef);

	/**
		SceneManager destructor.
	*/
	~SceneManager();

	/**
		Creates a new scene node and inits it with a model.

		@param model Model to assign to node.
	*/
	static SceneNode* createSceneNode(Model* model);

	/**
		Sets up the scene manager.
		Takes care of creating the uniform block for the shader and creating the scene nodes.
	*/
	void setupSceneManager();

	/**
		Pushes scene nodes to renderer to be rendered.
	*/
	void renderScene();

	/**
		Updates each scene node.
	*/
	void updateScene();

	void toggleArcballCam();
	void toggleGimbalLock();
	void changeCameraProjection();
	void rotateCamera(float x, float y);
	void updateCamera(Camera_Movement movement);
	void updateAspectRatio(float aspectRatio);
};