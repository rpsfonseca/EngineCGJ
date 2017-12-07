#include "Model.h"
#include "OBJLoader.h"
#include "OpenGLError.h"
#include <string>
#include <iostream>

Model::Model()
{
	hasNormals = false;
	hasTextures = false;
}

Model::Model(std::string& filename)
{
	//loadOBJModel(filename, *this);

	OBJLoader modelLoader = OBJLoader(filename);
	*this = modelLoader.toModel();

	/*for (int i = 0; i < positions.size(); i++)
	{
		AdvancedVertex aux;
		aux.position = Vec4(positions[i]);
		aux.normals = Vec3(normals[i]);
		aux.texCoords = Vec2(texCoords[i]);
		vertices.push_back(aux);
	}*/

	setupModel();
}


Model::~Model()
{
}

void Model::setupModel()
{
	/*glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(AdvancedVertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (GLvoid*)offsetof(AdvancedVertex, texCoords));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(AdvancedVertex), (GLvoid*)offsetof(AdvancedVertex, normals));

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Vec3), &positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);

		if (hasTextures)
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(Vec3), &texCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);
		}

		if (hasNormals)
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vec3), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	OpenGLError::checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

unsigned int Model::getVao()
{
	return vao;
}

unsigned int Model::getVbo()
{
	return vbo;
}

unsigned int Model::getEbo()
{
	return ebo;
}

void Model::setUbo(unsigned int uboId)
{
	ubo = uboId;
}

unsigned int Model::getIndicesSize()
{
	return indices.size();
}

Vec3 Model::getPosition()
{
	return worldPosition;
}

void Model::setPosition(Vec3& pos)
{
	worldPosition = Vec3(pos);
}

float Model::getRotation()
{
	return worldRotation;
}

void Model::setRotation(float rot)
{
	worldRotation = rot;
}


Vec3 Model::get3DRotation()
{
	return world3DRotation;
}

void Model::set3DRotation(Vec3 angle)
{
	world3DRotation = angle;
}

Vec3 Model::getScale()
{
	return worldScale;
}

void Model::setScale(Vec3& sc)
{
	worldScale = Vec3(sc);
}


Vec4 Model::getColor()
{
	return topColor;
}

void Model::setColor(Vec4& sc)
{
	topColor = Vec4(sc);
}