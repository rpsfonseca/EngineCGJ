#include "Renderer.h"
#include "Mesh.h"
#include "GL\glew.h"

#include <iostream>

Vec3 Renderer::CLEAR_COLOR = Vec3(0.1f, 0.1f, 0.1f);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentShader.Use();
	for (Mesh& m : meshes)
	{
		glBindVertexArray(m.getVao());

		modelMatrix = Mat4();
		modelMatrix = modelMatrix * modelMatrix.TranslationMatrix(m.getPosition());
		currentShader.SetMat4("Matrix", modelMatrix);

		glDrawElements(GL_TRIANGLES, m.getIndicesSize(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
	glBindVertexArray(0);
}

void Renderer::setupRenderer()
{
	checkOpenGLInfo();

	currentShader = Shader("../../projects/engine/src/vertex_shader.glsl", "../../projects/engine/src/frag_shader.glsl");
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
	std::vector<Vertex> v(3);
	v = {
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { 0.75f, 0.25f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 0.50f, 0.75f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	Mesh triangle = Mesh(v, { 0,1,2 });
	meshes.push_back(triangle);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 0.0f, 0.25f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } }
	};
	Mesh triangle2 = Mesh(v, { 0,1,2 });
	meshes.push_back(triangle2);

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

void Renderer::reshapeViewport(int _newWidth, int _newHeight)
{
	glViewport(0, 0, _newWidth, _newHeight);
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