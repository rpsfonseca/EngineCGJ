#include "Application.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

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
	else if(directions[1] == 1)
	{
		instance->sceneManagerRef->updateCamera(Camera_Movement::FORWARD);

	}
	instance->sceneManagerRef->renderScene();
	instance->windowRef->swapBuffers();
}

void Application::cleanup()
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
	if (instance->firstTimeMoving)
	{
		previousX = x;
		previousY = y;
		firstTimeMoving = false;
	}

	float mouseX = x - previousX;
	float mouseY = previousY - y;

	previousX = x;
	previousY = y;

	instance->sceneManagerRef->rotateCamera(mouseX, mouseY);
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
}

void Application::setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(char_keyboard);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouse);
	glutWarpPointer(320,240);
	glutEntryFunc(entry);
}

void Application::mainLoop()
{
	glutMainLoop();
}