#pragma once

#include <string>

class Window
{
public:
	static int HEIGHT;
	static int WIDTH;
	static std::string TITLE;

	int windowHandle;
public:
	Window();
	Window(int _width, int _height);
	~Window();

	void setupWindow(const int& _versionMajor, const int& _versionMinor);

	void swapBuffers();

	void reshape(int _newWidth, int _newHeight);
};;

