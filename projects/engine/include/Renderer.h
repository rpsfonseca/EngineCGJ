#pragma once

#include "Vec3.h"
#include "Mesh.h"
#include "Shader.h"
#include "Model.h"

#include <vector>

using namespace math;

/**
	This class represents the engine renderer.
	As a renderer it is responsible for drawing the models to the screen.
*/
class Renderer
{
public:

	static Vec3 CLEAR_COLOR;
	Shader currentShader;
	Mat4 modelMatrix;
	Mat4 projectionMatrix;
	Mat4 viewMatrix;

	unsigned int uboBp; // Uniform block pointer used to retrieve uniform block ID
	unsigned int uboId; // The actual uniform block ID

public:
	/**
		Default constructor.
		Does nothing other than constructing a variable of its type.
		Its setup is called from setupApp in the Application class.
	*/
	Renderer();
	~Renderer();

	/**
		As the name implies, sets up the renderer.
		- Prints OpenGL version to console.
		- Creates its current shader and gets the uniform blcok binding from it.
		- Sets up a few gl options, in terms of rendering.
	*/
	void setupRenderer();

	/**
		As the name implies, it runs before the draw method.
		For now it just:
		- Clears screen and depth buffer
		- Binds the uniform buffer
		- Activates the currentShader
	*/
	void preDraw();

	/**
		Draw method. Old one.
		Before we had the SceneManager, the meshes were stored on this class, and so we just looped over them and draw them.
		This was left here for now in case we want to send the whole scene nodes into this function, instead of the current method.
	*/
	void draw();

	/**
		Draw method. The one currently being used.
		The pattern here is that we send the model of a SceneNode to be drawn from the SceneManager, along with its transform.
	*/
	void draw(Model* model, Mat4& transform);

	/**
		As the name implies, it runs after the draw method.
		For now it just unbinds the shader program and the vertex array.
	*/
	void postDraw();

	/**
	
	*/
	void update();

	/**
		Simple wrapper for glViewport.

		@param _newWidth New width value to be set on glViewport.
		@param _newHeight New height value to be set on glViewport.
	*/
	void reshapeViewport(int _newWidth, int _newHeight);

	void setProjectionMatrix(const Mat4& mat);
	void setViewMatrix(const Mat4& mat);

private:
	void checkOpenGLInfo();
};

