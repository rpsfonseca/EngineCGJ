#include "Model.h"
#include "OBJLoader.h"
#include "OpenGLError.h"
#include "Quad.h"
#include <string>
#include <iostream>
#include "Timer.h"


// Model constructor.
// Just creates the variable of this type.
// Sets hasTextures and hasNormals.
Model::Model()
{
	hasNormals = false;
	hasTextures = false;

	meshes.push_back(Quad());
	materials["default"] = Material();
}

Model::Model(std::string shaderName, int a)
{
	hasNormals = false;
	hasTextures = false;

	meshes.push_back(Quad());
	materials["default"] = Material(shaderName);
}

// Model constructor.
// This is the one normally used.
// You load a 3d model by passing the filename.
// Also setups up the VBO's.
Model::Model(std::string& filename)
{
	OBJLoader modelLoader = OBJLoader(filename);
	*this = modelLoader.toModel();

	setupModel();
}

Model::~Model()
{
}

// Setups up the VBO's.
void Model::setupModel()
{
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

void Model::draw(Mat4& transform)
{
	for (auto it = materials.begin(); it != materials.end(); ++it)
	{
		it->second.shader.use();
		auto aux = it->second.textures;
		for (auto it2 = aux.begin(); it2 != aux.end(); ++it2)
		{
			it2->second.texture->bind(it2->second.unit);
		}
	}

	glBindVertexArray(meshes[0].getVao());

	Mat4 modelMatrix = Mat4();
	modelMatrix = transform;
	materials["default"].shader.setMat4("modelMatrix", modelMatrix);
	materials["default"].shader.setFloat("runTime", glfwGetTime());
	if (meshes[0].usingIndices)
	{
		glDrawElements(GL_TRIANGLES, meshes[0].getIndicesSize(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)positions.size());
	}

	OpenGLError::checkOpenGLError("ERROR: Could not draw model.");
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