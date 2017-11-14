
#include "GL\freeglut.h"
#include "Window.h"

#include <iostream>

int Window::HEIGHT = 480;
int Window::WIDTH = 640;
std::string Window::TITLE = "EngineCGJ - Development";

Window::Window()
{
}

Window::Window(int _width, int _height)
{
	WIDTH = _width;
	HEIGHT = _height;
}

Window::~Window()
{
}

void Window::setupWindow(const int& _versionMajor, const int& _versionMinor)
{
	/*int argc = 1;
	char *argv[1] = { (char*)"Something" };
	glutInit(&argc, argv);*/

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	/*glutInitContextVersion(_versionMajor, _versionMinor);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	windowHandle = glutCreateWindow(TITLE.c_str());
	if (windowHandle < 1)
	{
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}*/
}

bool Window::shouldWindowClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	//glutSwapBuffers();
	glfwSwapBuffers(window);
}

void Window::reshape(int _newWidth, int _newHeight)
{
	WIDTH = _newWidth;
	HEIGHT = _newHeight;
}