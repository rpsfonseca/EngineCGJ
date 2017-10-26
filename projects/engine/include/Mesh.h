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
	bool usingIndices = true;

	Mesh(std::vector<Vertex> vertices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	unsigned int getVao();
	inline unsigned int getVbo();
	unsigned int getEbo();

	void setUbo(unsigned int uboId);

	unsigned int getIndicesSize();

	Vec3 getPosition();
	void setPosition(Vec3& pos);

	float getRotation();
	void setRotation(float angle);

	Vec3 getScale();
	void setScale(Vec3& sc);
private:
	unsigned int vao, vbo, ebo, ubo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vec3 worldPosition;
	float worldRotation;
	Vec3 worldScale;

	void setupMesh();
};