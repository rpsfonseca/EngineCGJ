#include "Mesh.h"
#include "GL\glew.h"

#include <iostream>
#include <sstream>

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
	: vertices(_vertices), indices(_indices)
{
	setupMesh();
}

Mesh::~Mesh()
{

}

void Mesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, rgba));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

unsigned int Mesh::getVao()
{
	return vao;
}

unsigned int Mesh::getVbo()
{
	return vbo;
}

unsigned int Mesh::getEbo()
{
	return ebo;
}

unsigned int Mesh::getIndicesSize()
{
	return indices.size();
}

Vec3 Mesh::getPosition()
{
	return worldPosition;
}
