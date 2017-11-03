#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::SceneManager(std::shared_ptr<Renderer> rendererRef)
	: renderer(rendererRef)
{
	currentCamera = std::make_shared<Camera>(Vec3(0.0f, -0.25f, 5.0f));

	//setupSceneManager();
}

SceneManager::~SceneManager()
{
}
void SceneManager::setupSceneManager()
{
	//renderer->setupRenderer();

	glGenBuffers(1, &uniformBlockId);

	glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, renderer->uboBp, uniformBlockId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	renderer->uboId = uniformBlockId;
}



void SceneManager::renderScene()
{
	//std::cout << currentCamera->getViewMatrix() << std::endl;
	renderer->setProjectionMatrix(currentCamera->getProjectionMatrix());
	renderer->setViewMatrix(currentCamera->getViewMatrix());
	renderer->draw();
}

void SceneManager::changeCameraProjection()
{
	currentCamera->changeProjection();
}

void SceneManager::toggleArcballCam()
{
	currentCamera->toggleArcballCam();
}

void SceneManager::toggleGimbalLock()
{
	currentCamera->toggleGimbalLock();
}

void SceneManager::rotateCamera(float x, float y)
{
	currentCamera->processMouseMovement(x, y, false);
}

void SceneManager::updateCamera(Camera_Movement movement)
{
	currentCamera->processKeyboard(movement, 0.0005f);
}

void SceneManager::updateAspectRatio(float aspectRatio)
{
	currentCamera->aspectRatio = aspectRatio;
}
