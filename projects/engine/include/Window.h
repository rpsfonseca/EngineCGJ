#pragma once



#include "GLFW\glfw3.h"
#include <string>

/**
	This class represents an app window, and is responsible for handling its setup, reshape and buffers.
	A Window has a width, height and a title.
*/
class Window
{
public:
	static int HEIGHT;
	static int WIDTH;
	static std::string TITLE;

	GLFWwindow* window;
public:
	/**
		Default Window constructor.
		Does nothing other than enabling to create a variables of this type.
	*/
	Window();

	/**
		Currently used constructor.
		Sets WIDTH and HEIGHT static variables.

		@param _width Width value to be set.
		@param _height Height value to be set.
	*/
	Window(int _width, int _height);
	~Window();

	/**
		Creates the window with the appropriate context and OpenGL version.

		@param _versionMajor Major OpenGL version.
		@param _versionMinor Minor OpenGL version.
	*/
	void setupWindow(const int& _versionMajor, const int& _versionMinor);

	/**
		Simple wrapper for glfwWindowShouldClose method.
	*/
	bool shouldWindowClose();

	/**
		Simple wrapper for glfwSwapBuffers method.
	*/
	void swapBuffers();

	/**
		When window reshaping happens, it sets the new width and height values to the respective static variables.
	*/
	void reshape(int _newWidth, int _newHeight);
};;

