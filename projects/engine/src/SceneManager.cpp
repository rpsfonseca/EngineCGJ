#include "SceneManager.h"

#include <stack>

SceneNode* SceneManager::rootSceneNode = new SceneNode(0);
int SceneManager::nodeCounterId = 0;

SceneManager::SceneManager()
{
}

SceneManager::SceneManager(std::shared_ptr<Renderer> rendererRef)
	: renderer(rendererRef)
{
	currentCamera = std::make_shared<Camera>(Vec3(0.0f, 0.0f, 5.0f));

	//setupSceneManager();
}

SceneManager::~SceneManager()
{
}

SceneNode* SceneManager::createSceneNode(Model* model)
{
	SceneNode* node = new SceneNode(SceneManager::nodeCounterId++);
	node->model = model;
	/*node->model.positions = model->positions;
	node->model.normals = model->normals;
	node->model.texCoords = model->texCoords;*/

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

	SceneNode* cubeNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/cube_vn.obj")));
	cubeNode->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	cubeNode->setRotation(Quat());
	cubeNode->setScale(Vec3(1.0f));
	cubeNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	cubeNode->model->setRotation(0.0f);
	cubeNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(cubeNode);

	SceneNode* parallelogramNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/parallelogram.obj")));
	parallelogramNode->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	parallelogramNode->setRotation(Quat());
	parallelogramNode->setScale(Vec3(1.0f));
	parallelogramNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	parallelogramNode->model->setRotation(0.0f);
	parallelogramNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(parallelogramNode);

	SceneNode* bigTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/big_tri.obj")));
	bigTriNode->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	bigTriNode->setRotation(Quat());
	bigTriNode->setScale(Vec3(1.0f));
	bigTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	bigTriNode->model->setRotation(0.0f);
	bigTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(bigTriNode);

	SceneNode* mediumTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/medium_tri.obj")));
	mediumTriNode->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	mediumTriNode->setRotation(Quat());
	mediumTriNode->setScale(Vec3(1.0f));
	mediumTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	mediumTriNode->model->setRotation(0.0f);
	mediumTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(mediumTriNode);

	SceneNode* smallTriNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/small_tri.obj")));
	smallTriNode->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	smallTriNode->setRotation(Quat());
	smallTriNode->setScale(Vec3(1.0f));
	smallTriNode->model->setPosition(Vec3(0.0f, 0.50f, 0.0f));
	smallTriNode->model->setRotation(0.0f);
	smallTriNode->model->setScale(Vec3(1.0f));
	planeNode->addChild(smallTriNode);

	nodes.insert(std::pair<std::string, SceneNode*>("plane", planeNode));
}



void SceneManager::renderScene()
{
	renderer->setProjectionMatrix(currentCamera->getProjectionMatrix());
	renderer->setViewMatrix(currentCamera->getViewMatrix());
	renderer->draw();

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
