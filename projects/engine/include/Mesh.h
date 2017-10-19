#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "GL\glew.h"
#include <vector>

using namespace math;

struct Vertex
{
	Vec4 position;
	Vec4 rgba;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	unsigned int getVao();
	inline unsigned int getVbo();
	unsigned int getEbo();

	unsigned int getIndicesSize();

	Vec3 getPosition();
private:
	unsigned int vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vec3 worldPosition;

	void setupMesh();
};