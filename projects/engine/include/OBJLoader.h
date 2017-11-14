#pragma once

#include "Model.h"

#include "Vec2.h"

#include <sstream>
#include <string>

void loadOBJModel(const std::string& filename, Model model);

struct OBJIndex
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const OBJIndex& right) const { return vertexIndex < right.vertexIndex; };
};

class OBJLoader
{
public:
	bool hasUVs = false;
	bool hasNormals = false;

	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Vec2> uvs;


	std::vector <Vec3> Vertices, vertexData;
	std::vector <Vec2> Texcoords, texcoordData;
	std::vector <Vec3> Normals, normalData;

	std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;
public:
	OBJLoader(std::string& filename);
	~OBJLoader();

	Model toModel();

	void parseVertex(std::stringstream& sin);

	void parseTexcoord(std::stringstream& sin);

	void parseNormal(std::stringstream& sin);

	void parseFace(std::stringstream& sin);

	void parseLine(std::stringstream& sin);

	void loadMeshData(std::string& filename);

	void processMeshData();

	void freeMeshData();

	const void createMesh(std::string& filename);

private:
	std::vector<OBJIndex> objIndices;
private:
	unsigned int findLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const Model& result);
	void createOBJFace(const std::string& line);

	static bool compareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);

	OBJIndex parseOBJIndex(const std::string& token, bool &hasUVs, bool &hasNormals);
	Vec2 parseOBJVec2(const std::string& line);
	Vec3 parseOBJVec3(const std::string& line);
};

