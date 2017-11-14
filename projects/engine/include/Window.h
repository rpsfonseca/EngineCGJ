#pragma once



#include "GLFW\glfw3.h"
#include <string>


class Window
{
public:
	static int HEIGHT;
	static int WIDTH;
	static std::string TITLE;

	GLFWwindow* window;
	int windowHandle;
public:
	Window();
	Window(int _width, int _height);
	~Window();

	void setupWindow(const int& _versionMajor, const int& _versionMinor);
	bool shouldWindowClose();
	void swapBuffers();

	void reshape(int _newWidth, int _newHeight);
};;

