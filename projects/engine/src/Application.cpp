#include "Application.h"
#include "GL\glew.h"
#include "GL\freeglut.h"

#include <iostream>
#include <sstream>

unsigned int Application::FRAME_COUNT = 0;

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
}

void Application::mainLoop()
{
	glutMainLoop();
}