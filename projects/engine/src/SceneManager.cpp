#include "SceneManager.h"
#include "Timer.h"

#include <stack>

SceneNode* SceneManager::rootSceneNode = new SceneNode(0);
int SceneManager::nodeCounterId = 0;

SceneManager::SceneManager()
{
}

SceneManager::SceneManager(std::shared_ptr<Renderer> rendererRef)
	: renderer(rendererRef)
{
	currentCamera = std::make_shared<Camera>(Vec3(0.0f, 0.0f, 12.0f));

	//setupSceneManager();
}

SceneManager::~SceneManager()
{
}

SceneNode* SceneManager::createSceneNode(Model* model)
{
	SceneNode* node = new SceneNode(SceneManager::nodeCounterId++);
	node->model = model;
	node->model->animation = new Animation();

	return node;
}

SceneNode* SceneManager::createSceneNode(Model* model, Vec3& startPos, Vec3& targetPos)
{
	SceneNode* node = new SceneNode(SceneManager::nodeCounterId++);
	node->model = model;
	node->model->animation = new Animation(startPos, targetPos);

	return node;
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

	SceneNode* planeNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/floor.obj")));
	planeNode->setPosition(Vec3(0.0f));
	planeNode->setRotation(Quat());
	planeNode->setScale(Vec3(1.0f));
	planeNode->model->setPosition(Vec3(0.0f));
	planeNode->model->setRotation(0.0f);
	planeNode->model->setScale(Vec3(1.0f));
	rootSceneNode->addChild(planeNode);

	SceneNode* cubeNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/cube.obj")), Vec3(-0.50174f, 0.50f, 0.0f), Vec3(5.0f));
	cubeNode->setPosition(Vec3(-0.50174f, 0.50f, 0.0f));
	cubeNode->setRotation(Quat(0.0f, Vec3::UnitY));
	cubeNode->setScale(Vec3(1.0f, 0.5f, 1.0f));
	cubeNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	cubeNode->model->setRotation(0.0f);
	cubeNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(cubeNode);

	SceneNode* parallelogramNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/parallelogram.obj")));
	parallelogramNode->setPosition(Vec3(0.25137f, 0.50f, -0.75111f));
	parallelogramNode->setRotation(Quat(90.0f, Vec3::UnitY));
	parallelogramNode->setScale(Vec3(1.0f, 0.5f, 1.0f));
	parallelogramNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	parallelogramNode->model->setRotation(0.0f);
	parallelogramNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(parallelogramNode);

	SceneNode* bigTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/big_tri.obj")));
	bigTriNode->setPosition(Vec3(0.0f, 0.25f, 0.66666f));
	bigTriNode->setRotation(Quat(0.0f, Vec3::UnitY));
	bigTriNode->setScale(Vec3(1.0f, 0.25f, 1.0f));
	bigTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	bigTriNode->model->setRotation(0.0f);
	bigTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(bigTriNode);

	bigTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/big_tri.obj")));
	bigTriNode->setPosition(Vec3(0.66465f, 0.50f, 0.0f));
	bigTriNode->setRotation(Quat(90.0f, Vec3::UnitY));
	bigTriNode->setScale(Vec3(1.0f, 0.70f, 1.0f));
	bigTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	bigTriNode->model->setRotation(0.0f);
	bigTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(bigTriNode);

	SceneNode* mediumTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/medium_tri.obj")));
	mediumTriNode->setPosition(Vec3(-0.66666f, 0.50f, -0.66732f));
	mediumTriNode->setRotation(Quat(90.0f, Vec3::UnitY));
	mediumTriNode->setScale(Vec3(1.0f, 0.75f, 1.0f));
	mediumTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	mediumTriNode->model->setRotation(0.0f);
	mediumTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(mediumTriNode);

	SceneNode* smallTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/small_tri.obj")));
	smallTriNode->setPosition(Vec3(0.0f, 0.50f, -0.33383f));
	smallTriNode->setRotation(Quat(90.0f, Vec3::UnitY));
	smallTriNode->setScale(Vec3(1.0f, 1.0f, 1.0f));
	smallTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	smallTriNode->model->setRotation(0.0f);
	smallTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(smallTriNode);

	smallTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/small_tri.obj")));
	smallTriNode->setPosition(Vec3(-0.83290f, 0.50f, 0.50174f));
	smallTriNode->setRotation(Quat(180.0f, Vec3::UnitY));
	smallTriNode->setScale(Vec3(1.0f, 0.85f, 1.0f));
	smallTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	smallTriNode->model->setRotation(0.0f);
	smallTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(smallTriNode);

	nodes.insert(std::pair<std::string, SceneNode*>("plane", planeNode));
}

void SceneManager::updateScene()
{
	std::stack<SceneNode*> nodeStack;
	nodeStack.push(rootSceneNode);
	for (unsigned int i = 0; i < rootSceneNode->childNodes.size(); ++i)
	{
		nodeStack.push(rootSceneNode->childNodes[i]);
	}
	while (!nodeStack.empty())
	{
		SceneNode* node = nodeStack.top();
		nodeStack.pop();

		if (node->model && node->model->animation->hasAnimationRunning)
		{
			node->model->animation->updateAnimation();
			node->setPosition(node->model->animation->currentPos);
		}
		for (unsigned int i = 0; i < node->childNodes.size(); ++i)
		{
			nodeStack.push(node->childNodes[i]);
		}
	}
}

void SceneManager::renderScene()
{
	renderer->setProjectionMatrix(currentCamera->getProjectionMatrix());
	renderer->setViewMatrix(currentCamera->getViewMatrix());
	//renderer->draw();
	renderer->preDraw();

	std::stack<SceneNode*> nodeStack;
	nodeStack.push(rootSceneNode);
	for (unsigned int i = 0; i < rootSceneNode->childNodes.size(); ++i)
	{
		nodeStack.push(rootSceneNode->childNodes[i]);
	}
	while (!nodeStack.empty())
	{
		SceneNode* node = nodeStack.top();
		nodeStack.pop();

		node->updateTransform();
		if (node->model)
		{
			renderer->draw(node->model, node->transform);
		}
		for (unsigned int i = 0; i < node->childNodes.size(); ++i)
		{
			nodeStack.push(node->childNodes[i]);
		}
	}

	renderer->postDraw();
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
	currentCamera->processKeyboard(movement, Timer::deltaTime);
}

void SceneManager::updateAspectRatio(float aspectRatio)
{
	currentCamera->aspectRatio = aspectRatio;
}
