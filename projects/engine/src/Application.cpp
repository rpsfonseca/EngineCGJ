
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Application.h"
#include "Keyboard.h"

#include <iostream>
#include <sstream>

unsigned int Application::FRAME_COUNT = 0;
int Application::directions[2] = { 0.0f, 0.0f };
float Application::previousX;
float Application::previousY;
bool Application::firstTimeMoving = true;

static Application* instance;

Application::Application()
{
	instance = this;
}

Application::Application(int _versionMajor, int _versionMinor)
	: versionMajor(_versionMajor), versionMinor(_versionMinor)
{
	windowRef = std::make_shared<Window>();
	rendererRef = std::make_shared<Renderer>();
	sceneManagerRef = std::make_shared<SceneManager>(rendererRef);

	windowWidth = windowRef->WIDTH;
	windowHeight = windowRef->HEIGHT;

	instance = this;
}

Application::Application(int _versionMajor, int _versionMinor, int _width, int _height)
	: versionMajor(_versionMajor), versionMinor(_versionMinor), windowWidth(_width), windowHeight(_height)
{
	windowRef = std::make_shared<Window>(windowWidth, windowHeight);
	rendererRef = std::make_shared<Renderer>();
	sceneManagerRef = std::make_shared<SceneManager>(rendererRef);

	instance = this;
}

Application::~Application()
{
}

void Application::draw()
{
	display();
}

void Application::display()
{
	++FRAME_COUNT;

	//instance->rendererRef->draw();
	
	if (input::Keyboard::GetInstance().Pressed(GLFW_KEY_1))
	{
		instance->sceneManagerRef->toggleArcballCam();
	}

	directions[0] = 0;
	directions[1] = 0;
	if (input::Keyboard::GetInstance().isKeyDown(GLFW_KEY_A))
	{
		if (directions[0] == 1 || directions[0] == 0)
		{
			directions[0] -= 1;
		}
	}
	if (input::Keyboard::GetInstance().isKeyDown(GLFW_KEY_D))
	{
		if (directions[0] == -1 || directions[0] == 0)
		{
			directions[0] += 1;
		}
	}
	if (input::Keyboard::GetInstance().isKeyDown(GLFW_KEY_W))
	{
		if (directions[1] == -1 || directions[1] == 0)
		{
			directions[1] += 1;
		}
	}
	if (input::Keyboard::GetInstance().isKeyDown(GLFW_KEY_S))
	{
		if (directions[1] == 1 || directions[1] == 0)
		{
			directions[1] -= 1;
		}
	}

	if (input::Keyboard::GetInstance().isKeyDown(GLFW_KEY_UP))
	{
		instance->sceneManagerRef->nodes["plane"]->setPosition(instance->sceneManagerRef->nodes["plane"]->getPosition() + Vec3(0.0f, 0.0005f, 0.0f));
		instance->sceneManagerRef->nodes["plane"]->model->setPosition(instance->sceneManagerRef->nodes["plane"]->model->worldPosition + Vec3(0.0f, 0.0005f, 0.0f));
	}

	if (directions[0] == -1)
	{
		instance->sceneManagerRef->updateCamera(Camera_Movement::LEFT);

	}
	else if (directions[0] == 1)
	{
		instance->sceneManagerRef->updateCamera(Camera_Movement::RIGHT);

	}
	if (directions[1] == -1)
	{
		instance->sceneManagerRef->updateCamera(Camera_Movement::BACKWARD);

	}
	else if (directions[1] == 1)
	{
		instance->sceneManagerRef->updateCamera(Camera_Movement::FORWARD);

	}

	instance->sceneManagerRef->renderScene();
	instance->windowRef->swapBuffers();
}

void Application::cleanup()
{

}

void Application::cleanup(GLFWwindow * window)
{
}

void Application::idle()
{
	glutPostRedisplay();
}

void Application::reshape(int _w, int _h)
{
	instance->windowWidth = _w;
	instance->windowHeight = _h;
	instance->sceneManagerRef->updateAspectRatio((float)_w / (float)_h);
	instance->windowRef->reshape(_w, _h);
	instance->rendererRef->reshapeViewport(_w, _h);
}

void Application::reshapeWindow(GLFWwindow* window, int _w, int _h)
{
	instance->windowWidth = _w;
	instance->windowHeight = _h;
	instance->sceneManagerRef->updateAspectRatio((float)_w / (float)_h);
	instance->windowRef->reshape(_w, _h);
}

void Application::reshapeFramebuffer(GLFWwindow* window, int _w, int _h)
{
	instance->rendererRef->reshapeViewport(_w, _h);
}

void Application::timer(int _val)
{
	std::ostringstream oss;
	oss << instance->windowRef->TITLE << ": " << FRAME_COUNT << " FPS @ (" << instance->windowWidth << "x" << instance->windowHeight << ")";
	std::string s = oss.str();
	glutSetWindow(instance->windowRef->windowHandle);
	glutSetWindowTitle(s.c_str());
	FRAME_COUNT = 0;
	glutTimerFunc(1000, timer, 0);
}

void Application::char_keyboard(unsigned char key, int x, int y)
{
	std::cout << key << std::endl;

	switch (key)
	{
	case 'a':
		instance->sceneManagerRef->toggleArcballCam();
		break;
	case 'g':
		instance->sceneManagerRef->toggleGimbalLock();
		break;
	case 'p':
		instance->sceneManagerRef->changeCameraProjection();
		break;
	default:
		break;
	}
}

void Application::keyboard_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		directions[0] = 0.0f;
		break;
	case GLUT_KEY_RIGHT:
		directions[0] = 0.0f;
		break;
	case GLUT_KEY_UP:
		directions[1] = 0.0f;
		break;
	case GLUT_KEY_DOWN:
		directions[1] = 0.0f;
		break;
	default:
		break;
	}
}

void Application::mouse(int x, int y)
{
	/*if (instance->firstTimeMoving)
	{
		previousX = x;
		previousY = y;
		firstTimeMoving = false;
	}

	float mouseX = x - previousX;
	float mouseY = previousY - y;

	previousX = x;
	previousY = y;

	instance->sceneManagerRef->rotateCamera(mouseX, mouseY);*/

	previousX = x;
	previousY = y;

	int cx = (instance->windowWidth >> 1);
	int cy = (instance->windowHeight >> 1);

	float deltaX = float(previousX - cx) / 10;
	float deltaY = float(previousY - cy);

	if (abs(deltaX) > 0.5f)
	{
		glutWarpPointer(cx, y);
	}
	if (abs(deltaY) > 0.5f) {
		glutWarpPointer(x, cy);
	}

	instance->sceneManagerRef->rotateCamera(deltaX, deltaY);
}

void Application::mouse(GLFWwindow* window, double x, double y)
{
	previousX = x;
	previousY = y;

	int cx = (instance->windowWidth >> 1);
	int cy = (instance->windowHeight >> 1);

	float deltaX = float(previousX - cx) * 0.1f;
	float deltaY = float(previousY - cy) * 0.1f;

	std::cout << "DeltaX: " << abs(deltaX) << std::endl;
	std::cout << "DeltaY: " << abs(deltaY) << std::endl;
	if (abs(deltaX) > 0.5f)
	{
		glfwSetCursorPos(window, cx, y);
	}
	else
	{
		deltaX = 0.0f;
	}
	if (abs(deltaY) > 0.5f)
	{
		glfwSetCursorPos(window, x, cy);
	}
	else
	{
		deltaY = 0.0f;
	}


	glfwSetWindowPos(instance->windowRef->window, 320, 240);

	instance->sceneManagerRef->rotateCamera(deltaX, deltaY);
}

void Application::entry(int state)
{
	if (state == GLUT_LEFT)
	{
		firstTimeMoving = true;
	}
}

void Application::keyboard(int key, int x, int y)
{
	directions[0] = 0.0f;
	directions[1] = 0.0f;
	switch (key)
	{
		case GLUT_KEY_LEFT:
			if (directions[0] == 1 || directions[0] == 0)
			{
				directions[0] -= 1;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (directions[0] == -1 || directions[0] == 0)
			{
				directions[0] += 1;
			}
			break;
		case GLUT_KEY_UP:
			if (directions[1] == -1 || directions[1] == 0)
			{
				directions[1] += 1;
			}
			break;
		case GLUT_KEY_DOWN:
			if (directions[1] == 1 || directions[1] == 0)
			{
				directions[1] -= 1;
			}
			break;
		default:
			break;
	}
}

void Application::keyboard(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:
		input::Keyboard::GetInstance().KeyPressed(key);
		break;
	case GLFW_RELEASE:
		input::Keyboard::GetInstance().KeyReleased(key);
		break;
	default:
		break;
	}
}

void Application::setupApp()
{
	windowRef->setupWindow(versionMajor, versionMinor);

	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();

	rendererRef->setupRenderer();
	sceneManagerRef->setupSceneManager();

	setupCallbacks();

	glfwSetInputMode(windowRef->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	instance->sceneManagerRef->updateAspectRatio(640.0f/480.0f);
}

void Application::setupCallbacks()
{
	/*glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(char_keyboard);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboard_up);
	glutMotionFunc(mouse);
	glutWarpPointer(320,240);
	glutEntryFunc(entry);*/

	glfwSetWindowCloseCallback(windowRef->window, cleanup);
	glfwSetWindowSizeCallback(windowRef->window, reshapeWindow);
	glfwSetFramebufferSizeCallback(windowRef->window, reshapeFramebuffer);
	glfwSetCursorPosCallback(windowRef->window, mouse);
	glfwSetKeyCallback(windowRef->window, keyboard);
}

void Application::mainLoop()
{
	//glutMainLoop();

	while (!windowRef->shouldWindowClose())
	{
		draw();

		glfwPollEvents();
	}

	glfwDestroyWindow(instance->windowRef->window);
	glfwTerminate();
}