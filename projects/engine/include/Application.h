#pragma once

/**
	Application.h
	Purpose: Holds the class declarations for the engine app

	@author Ricardo Fonseca
	@version 0.1 
*/


#include "Renderer.h"
#include "SceneManager.h"
#include "Window.h"
#include "GLFW\glfw3.h"

#include <memory>



class Application
{
	// "Global" variable mainly used FPS counter
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

	float currentFrame;
	float lastFrame = 0.0f;

	bool firstTimeT = false;
public:
	/**
		Constructs Application with no args.
		Inits the singleton.
	*/
	Application();

	/**
		Inits Application with params indicating the version of OpenGL we want to target.
		Also creates the smart pointers for windowRef, rendererRef and sceneManagerRef,
		sets windowWidth and windowHeight and inits the singleton.

		@param _versionMajor Major OpenGL version to target.
		@param _versionMinor Minor OpenGL version to target.
	*/
	Application(int _versionMajor, int _versionMinor);

	/**
		Inits Application with params indicating the version of OpenGL we want to target.
		Also creates the smart pointers for windowRef, rendererRef and sceneManagerRef,
		sets windowWidth and windowHeight and inits the singleton.

		@param _versionMajor Major OpenGL version to target.
		@param _versionMinor Minor OpenGL version to target.
		@param _width Width value to set windowWidth.
		@param _height Height value to set windowHeight.
	*/
	Application(int _versionMajor, int _versionMinor, int _width, int _height);
	~Application();

	void draw();

	void setupApp();
	void mainLoop();

	static int directions[2];
private:
	static void display();
	/**
		Cleanup callback used by GLFW when window is closed.

		@param window GLFW window pointer.
	*/
	static void cleanup(GLFWwindow* window);
	/**
		Window reshape callback used by GLFW when the specified window is resized.

		@param window GLFW window pointer.
		@param _w New window width.
		@param _h New window height.
	*/
	static void reshapeWindow(GLFWwindow* window, int _w, int _h);
	/**
		Framebuffer reshape callback used by GLFW when the framebuffer of the specified window is resized.

		@param window GLFW window pointer.
		@param _w New framebuffer width.
		@param _h New framebuffer height.
	*/
	static void reshapeFramebuffer(GLFWwindow* window, int _w, int _h);
	static void timer(int _val);
	/**
		Keyboard callback used by GLFW to send keyboard input info.

		@param window GLFW window pointer.
		@param key Integer key identifier.
		@param scancode Mouse y position.
	*/
	static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mode);
	/**
		Mouse callback used by GLFW to send mouse position.

		@param window GLFW window pointer.
		@param x Mouse x position.
		@param y Mouse y position.
	*/
	static void mouse(GLFWwindow* window, double x, double y);
	static void entry(int state);
private:
	/**
		Sets the appropriate callbacks to glfw.
	*/
	void setupCallbacks();
};

