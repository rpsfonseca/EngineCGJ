
#include "GL\freeglut.h"
#include "Window.h"

#include <iostream>
#include <sstream>
#include <string>

int Window::HEIGHT = 480;
int Window::WIDTH = 640;
std::string Window::TITLE = "EngineCGJ - Development";

// Default Window constructor.
// Does nothing other than enabling to create a variables of this type.
Window::Window()
{
}

// Currently used constructor.
// Sets WIDTH and HEIGHT static variables.
Window::Window(int _width, int _height)
{
	WIDTH = _width;
	HEIGHT = _height;
}

Window::~Window()
{
}

// Creates the window with the appropriate context and OpenGL version.
void Window::setupWindow(const int& _versionMajor, const int& _versionMinor)
{
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
}

void Window::setWindowTitle(int fps)
{
	std::ostringstream oss;
	oss << TITLE << ": " << fps << " FPS @ (" << WIDTH << "x" << HEIGHT << ")";
	std::string s = oss.str();
	glfwSetWindowTitle(window, s.c_str());
}

// Simple wrapper for glfwWindowShouldClose method.
bool Window::shouldWindowClose()
{
	return glfwWindowShouldClose(window);
}

// Simple wrapper for glfwSwapBuffers method.
void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

// When window reshaping happens, it sets the new width and height values to the respective static variables.
void Window::reshape(int _newWidth, int _newHeight)
{
	WIDTH = _newWidth;
	HEIGHT = _newHeight;
}