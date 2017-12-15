#include "Renderer.h"
#include "Mesh.h"
#include "OpenGLError.h"
#include "GL\glew.h"

#include <ctime>
#include <iostream>

Vec3 Renderer::CLEAR_COLOR = Vec3(0.1f, 0.1f, 0.1f);

// Default constructor.
// Does nothing other than constructing a variable of its type.
// Its setup is called from setupApp in the Application class.
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

// As the name implies, sets up the renderer.
// - Prints OpenGL version to console.
// - Creates its current shader and gets the uniform blcok binding from it.
// - Sets up a few gl options, in terms of rendering.
void Renderer::setupRenderer()
{
	checkOpenGLInfo();

	currentShader = Shader("../../projects/engine/src/vertex_shader.glsl", "../../projects/engine/src/frag_shader.glsl");
	uboBp = currentShader.uniformBlockBinding();

	glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

// As the name implies, it runs before the draw method.
// For now it just:
// - Clears screen and depth buffer
// - Binds the uniform buffer
// - Activates the currentShader
void Renderer::preDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_UNIFORM_BUFFER, uboId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), &viewMatrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), &projectionMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

// Draw method.The one currently being used.
// The pattern here is that we send the model of a SceneNode to be drawn from the SceneManager, along with its transform.
void Renderer::draw(Model* model, Mat4& transform)
{
	model->materials["default"].shader.use();

	glBindVertexArray(model->meshes[0].getVao());

	modelMatrix = Mat4();
	modelMatrix = transform;
	model->materials["default"].shader.setMat4("modelMatrix", modelMatrix);

	if (model->meshes[0].usingIndices)
	{
		glDrawElements(GL_TRIANGLES, model->meshes[0].getIndicesSize(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)model->positions.size());
	}

	OpenGLError::checkOpenGLError("ERROR: Could not draw scene.");
}

// As the name implies, it runs after the draw method.
// For now it just unbinds the shader program and the vertex array.
void Renderer::postDraw()
{
	glUseProgram(0);
	glBindVertexArray(0);
}

// Simple wrapper for glViewport.
void Renderer::reshapeViewport(int _newWidth, int _newHeight)
{
	glViewport(0, 0, _newWidth, _newHeight);
}

void Renderer::setProjectionMatrix(const Mat4& mat)
{
	projectionMatrix = mat;
}

void Renderer::setViewMatrix(const Mat4& mat)
{
	viewMatrix = mat;
}

void Renderer::checkOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}