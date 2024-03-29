#include "SceneManager.h"
#include "Timer.h"

#include <stack>
#include <vector>
#include <string>
#include <cstring>

SceneNode* SceneManager::rootSceneNode = new SceneNode(0); // The root node of our node hierarchy
int SceneManager::nodeCounterId = 0; // Counter to keep track of the current node id to give to a new node

SceneManager::SceneManager()
{
}

// SceneManager constructor.
// Sets the renderer member with the shared pointer passed as param.
// Creates the scene camera as a shared pointer.
// This is the one that needs to be used;
SceneManager::SceneManager(std::shared_ptr<Renderer> rendererRef)
	: renderer(rendererRef)
{
	currentCamera = std::make_shared<Camera>(Vec3(0.0f, 0.0f, 5.0f));
	//TODO: setupSceneManager();
}

// SceneManager destructor.
SceneManager::~SceneManager() {}

// Creates a new scene node and inits it with a model.
SceneNode* SceneManager::createSceneNode(Model* model)
{
	SceneNode* node = new SceneNode(SceneManager::nodeCounterId++);
	node->model = model;

	return node;
}

// Sets up the scene manager.
// Takes care of creating the uniform block for the shader and creating the scene nodes.
void SceneManager::setupSceneManager()
{
	//renderer->setupRenderer();

	glGenBuffers(1, &uniformBlockId);

	glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, renderer->uboBp, uniformBlockId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// TODO: we could probably do
	// glGenBuffers(1, &renderer->uboId);
	// glBindBuffer(GL_UNIFORM_BUFFER, renderer->uboId);
	// glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4) * 2, 0, GL_STREAM_DRAW);
	// glBindBufferBase(GL_UNIFORM_BUFFER, renderer->uboBp, renderer->uboId);

	renderer->uboId = uniformBlockId;

	/*SceneNode* planeNode = SceneManager::createSceneNode(new Model(std::string("../../projects/engine/src/floor.obj")));
	planeNode->setPosition(Vec3(0.0f));
	planeNode->setRotation(Quat(90.0f, Vec3::UnitX));
	planeNode->setScale(Vec3(1.0f));
	planeNode->model->setPosition(Vec3(0.0f));
	planeNode->model->setRotation(0.0f);
	planeNode->model->setScale(Vec3(1.0f));*/
	SceneNode* planeNode = SceneManager::createSceneNode(new Model());
	planeNode->setPosition(Vec3(0.0f,0.0f,1.0f));
	planeNode->setScale(Vec3(4.0f));
	planeNode->model->setPosition(Vec3(0,0,-1.0f));
	planeNode->model->setRotation(0.0f);
	planeNode->model->setScale(Vec3(1.0f));
	rootSceneNode->addChild(planeNode);

	SceneNode* planeNode2 = SceneManager::createSceneNode(new Model("quad1"));
	planeNode2->setPosition(Vec3(0.0f));
	planeNode2->setScale(Vec3(3.0f,1.5f,1.0f));
	planeNode2->model->setPosition(Vec3(0.0f));
	planeNode2->model->setRotation(0.0f);
	planeNode2->model->setScale(Vec3(1.0f));
	rootSceneNode->addChild(planeNode2);

	nodes.insert(std::pair<std::string, SceneNode*>("plane", planeNode));
	nodes.insert(std::pair<std::string, SceneNode*>("plane2", planeNode2));
}


bool VectorOfStringGetter(void* data, int n, const char** out_text)
{
	const std::vector<std::string>* v = (std::vector<std::string>*)data;
	//v[n].data[0];
	const std::string* a = v[n].data();
	*out_text = v->at(n).c_str();
	return true;
}

// Pushes scene nodes to renderer to be rendered.
void SceneManager::renderScene()
{
	renderer->setProjectionMatrix(currentCamera->getProjectionMatrix());
	renderer->setViewMatrix(currentCamera->getViewMatrix());

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

	static int listbox_item_current = -1, listbox_item_current2 = -1;
	std::vector<std::string> v;
	for (auto it = nodes.begin(); it != nodes.end(); ++it)
	{
		v.push_back(it->first.c_str());
	}
	if (listbox_item_current != -1)
	{
		std::vector<std::string> a;
		for (auto it = nodes[v[listbox_item_current]]->model->materials.begin(); it != nodes[v[listbox_item_current]]->model->materials.end(); ++it)
		{
			a.push_back(it->first.c_str());
		}
	}
}


// Updates each scene node.
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
	currentCamera->processKeyboard(movement, Timer::deltaTime);
}

void SceneManager::updateAspectRatio(float aspectRatio)
{
	currentCamera->aspectRatio = aspectRatio;
}
