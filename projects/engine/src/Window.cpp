#include "Window.h"

#include "GL\glew.h"
#include "GL\freeglut.h"

#include <iostream>

int Window::HEIGHT = 640;
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
	int argc = 1;
	char *argv[1] = { (char*)"Something" };
	glutInit(&argc, argv);

	glutInitContextVersion(_versionMajor, _versionMinor);
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
	}
}

void Window::swapBuffers()
{
	glutSwapBuffers();
}

void Window::reshape(int _newWidth, int _newHeight)
{
	WIDTH = _newWidth;
	HEIGHT = _newHeight;
}