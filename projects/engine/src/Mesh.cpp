#include "Mesh.h"
#include "GL\glew.h"

#include <iostream>
#include <sstream>

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> _vertices)
	: vertices(_vertices)
{
	worldPosition = Vec3::Zero;
	worldRotation = 0.0f;
	usingIndices = false;
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices)
	: vertices(_vertices), indices(_indices)
{
	worldPosition = Vec3::Zero;
	worldRotation = 0.0f;
	setupMesh();
}

Mesh::~Mesh()
{

}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	if (usingIndices)
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

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

void Mesh::setUbo(unsigned int uboId)
{
	ubo = uboId;
}

unsigned int Mesh::getIndicesSize()
{
	return indices.size();
}

Vec3 Mesh::getPosition()
{
	return worldPosition;
}

void Mesh::setPosition(Vec3& pos)
{
	worldPosition = Vec3(pos);
}

float Mesh::getRotation()
{
	return worldRotation;
}

void Mesh::setRotation(float rot)
{
	worldRotation = rot;
}


Vec3 Mesh::get3DRotation()
{
	return world3DRotation;
}

void Mesh::set3DRotation(Vec3 angle)
{
	world3DRotation = angle;
}

Vec3 Mesh::getScale()
{
	return worldScale;
}

void Mesh::setScale(Vec3& sc)
{
	worldScale = Vec3(sc);
}


Vec4 Mesh::getColor()
{
	return topColor;
}

void Mesh::setColor(Vec4& sc)
{
	topColor = Vec4(sc);
}
