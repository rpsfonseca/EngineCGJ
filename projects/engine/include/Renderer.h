#pragma once

#include "Vec3.h"
#include "Mesh.h"
#include "Shader.h"

#include <vector>

using namespace math;

class Renderer
{
public:
	static Vec3 CLEAR_COLOR;
	Shader currentShader;
	Mat4 modelMatrix;
	Mat4 projectionMatrix;
	Mat4 viewMatrix;

	unsigned int uboBp;
	unsigned int uboId;

private:
	std::vector<Mesh> meshes;

public:
	Renderer();
	~Renderer();

	void draw();
	void update();

	void setupRenderer();

	void reshapeViewport(int _newWidth, int _newHeight);

	void setProjectionMatrix(const Mat4& mat);
	void setViewMatrix(const Mat4& mat);

private:
	void checkOpenGLInfo();
};

