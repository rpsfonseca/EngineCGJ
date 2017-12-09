#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "GL\glew.h"
#include <vector>

using namespace math;

struct Vertex
{
	Vec3 position;
};

class Mesh
{
public:
	bool usingIndices = true;

	Mesh();
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

	Vec3 get3DRotation();
	void set3DRotation(Vec3 angle);

	Vec3 getScale();
	void setScale(Vec3& sc);

	Vec4 getColor();
	void setColor(Vec4& sc);
protected:
	unsigned int vao, vbo, ebo, ubo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vec3 worldPosition;
	float worldRotation;
	Vec3 world3DRotation;
	Vec3 worldScale;

	Vec4 topColor;

	void setupMesh();
};