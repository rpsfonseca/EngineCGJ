#pragma once

#include "Camera.h"
#include "Renderer.h"

#include <memory>

class SceneManager
{
public:
	std::shared_ptr<Camera> currentCamera;
	std::shared_ptr<Renderer> renderer;

	unsigned int uniformBlockId;

	std::vector<Mesh> meshes;

public:
	SceneManager();
	SceneManager(std::shared_ptr<Renderer> rendererRef);
	~SceneManager();

	void setupSceneManager();

	void renderScene();
};