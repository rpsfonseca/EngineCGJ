#pragma once

#include "Window.h"
#include "Renderer.h"

#include <memory>

class Application
{
	static unsigned int FRAME_COUNT;

	std::shared_ptr<Window> windowRef;
	std::shared_ptr<Renderer> rendererRef;
	
	int versionMajor;
	int versionMinor;
	int windowWidth;
	int	windowHeight;

public:
	Application();
	Application(int _versionMajor, int _versionMinor);
	Application(int _versionMajor, int _versionMinor, int _width, int _height);
	~Application();

	void draw();

	void setupApp();
	void mainLoop();

public:
	static void display();
	static void cleanup();
	static void idle();
	static void reshape(int _w, int _h);
	static void timer(int _val);

private:
	void setupCallbacks();
};

