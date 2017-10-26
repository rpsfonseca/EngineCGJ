#pragma once

#include "Window.h"
#include "Renderer.h"
#include "SceneManager.h"

#include <memory>

class Application
{
	static unsigned int FRAME_COUNT;

	std::shared_ptr<Window> windowRef;
	std::shared_ptr<Renderer> rendererRef;
	std::shared_ptr<SceneManager> sceneManagerRef;
	
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

private:
	static void display();
	static void cleanup();
	static void idle();
	static void reshape(int _w, int _h);
	static void timer(int _val);

private:
	void setupCallbacks();
};

