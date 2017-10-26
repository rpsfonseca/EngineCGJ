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

	static bool firstTimeMoving;

	static float previousX;
	static float previousY;

public:
	Application();
	Application(int _versionMajor, int _versionMinor);
	Application(int _versionMajor, int _versionMinor, int _width, int _height);
	~Application();

	void draw();

	void setupApp();
	void mainLoop();

	static int directions[2];
private:
	static void display();
	static void cleanup();
	static void idle();
	static void reshape(int _w, int _h);
	static void timer(int _val);
	static void char_keyboard(unsigned char key, int x, int y);
	static void keyboard(int key, int x, int y);
	static void keyboard_up(int key, int x, int y);
	static void mouse(int x, int y);

private:
	void setupCallbacks();
};

