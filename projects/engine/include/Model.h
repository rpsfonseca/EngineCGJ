#pragma once

#include "Mesh.h"
#include "Vec2.h"
#include "Vec3.h"

#include <map>

struct AdvancedVertex
{
	Vec4 position;
	Vec2 texCoords;
	Vec3 normals;
};

class Model
{
public:
	//Mesh modelMesh;
	std::vector<AdvancedVertex> vertices;
	std::vector<Vec3> positions;
	std::vector<Vec3> normals;
	std::vector<Vec2> texCoords;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo, ubo;
	GLuint VboVertices, VboTexcoords, VboNormals;

	bool hasTextures;
	bool hasNormals;

public:
	Model();
	Model(std::string& filename);
	~Model();

	void setupModel();

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


	Vec3 worldPosition;
	float worldRotation;
	Vec3 world3DRotation;
	Vec3 worldScale;

	Vec4 topColor;
};

