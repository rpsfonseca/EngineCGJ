#include "Renderer.h"
#include "Mesh.h"
#include "GL\glew.h"

#include <iostream>

Vec3 Renderer::CLEAR_COLOR = Vec3(0.1f, 0.1f, 0.1f);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}
void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_UNIFORM_BUFFER, uboId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), &viewMatrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), &projectionMatrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	currentShader.use();
	for (Mesh& m : meshes)
	{
		glBindVertexArray(m.getVao());

		modelMatrix = Mat4();
		modelMatrix.matrix[0] = 1.0f;
		modelMatrix.matrix[5] = 1.0f;
		modelMatrix.matrix[10] = 1.0f;
		modelMatrix.matrix[15] = 1.0f;
		modelMatrix = modelMatrix * modelMatrix.TranslationMatrix(m.getPosition());
		modelMatrix = modelMatrix * modelMatrix.RotationMatrixAboutAxis(Axis::AxisZ, -m.getRotation());
		modelMatrix = modelMatrix * modelMatrix.ScaleMatrix(m.getScale());

		currentShader.setMat4("modelMatrix", modelMatrix);

		if (m.usingIndices)
		{
			glDrawElements(GL_TRIANGLES, m.getIndicesSize(), GL_UNSIGNED_INT, (GLvoid*)0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	glUseProgram(0);
	glBindVertexArray(0);
	checkOpenGLError("ERROR: Could not draw scene.");
}

void Renderer::setupRenderer()
{
	checkOpenGLInfo();

	currentShader = Shader("../../projects/engine/src/vertex_shader.glsl", "../../projects/engine/src/frag_shader.glsl");
	uboBp = currentShader.uniformBlockBinding();

	/*std::vector<Vertex> v(3);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }
	};
	Mesh triangle = Mesh(v, { 0,1,2 });
	triangle.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	triangle.setRotation(-45.0f);
	triangle.setScale(Vec3(1.0f));
	meshes.push_back(triangle);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } }
	};
	Mesh triangle2 = Mesh(v, { 0,1,2 });
	triangle2.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	triangle2.setRotation(45.0f);
	triangle2.setScale(Vec3(1.0f));
	meshes.push_back(triangle2);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } }
	};
	Mesh triangle3 = Mesh(v, { 0,1,2 });
	triangle3.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	triangle3.setRotation(-135.0f);
	triangle3.setScale(Vec3(0.5f));
	meshes.push_back(triangle3);

	v = {
		Vertex{ { -0.5f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { -0.25f, 0.25f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } }
	};
	Mesh paralelogram = Mesh(v, { 0,1,2,2,1,3 });
	paralelogram.setPosition(Vec3(0.0f, -0.5f, 0.0f));
	paralelogram.setRotation(45.0f);
	paralelogram.setScale(Vec3(1.0f));
	meshes.push_back(paralelogram);

	v = {
		Vertex{ { -0.5f, -0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		Vertex{ { 0.5f, -0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	Mesh square = Mesh(v, { 0,1,2,2,1,3 });
	square.setPosition(Vec3(0.5f, -0.5f, 0.0f));
	square.setRotation(0.0f);
	square.setScale(Vec3(0.35f));
	meshes.push_back(square);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } }
	};
	Mesh triangle4 = Mesh(v, { 0,1,2 });
	triangle4.setPosition(Vec3(-0.5f, 0.5f, 0.0f));
	triangle4.setRotation(135.0f);
	triangle4.setScale(Vec3(0.5f));
	meshes.push_back(triangle4);

	v = {
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		Vertex{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } },
		Vertex{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 1.0f, 0.0f, 1.0f, 1.0f } }
	};
	Mesh triangle5 = Mesh(v, { 0,1,2 });
	triangle5.setPosition(Vec3(0.0f, -1.0f, 0.0f));
	triangle5.setRotation(0.0f);
	triangle5.setScale(Vec3(0.70f));
	meshes.push_back(triangle5);*/

	std::vector<Vertex> v(36);

	/*v = {
		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 1.0f, 0.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 1.0f, 1.0f } },
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
	};

	Mesh cube = Mesh(v, { 0,1,2,2,3,0,1,5,6,6,2,1,2,6,7,7,3,2,5,4,7,7,6,5,4,0,3,3,7,4,0,4,5,5,1,0 });*/

	v = {
		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.9f, 0.0f, 0.0f, 1.0f }}, // 0 - FRONT
		Vertex{ { 1.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 1
		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 2
		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 2	
		Vertex{ { 0.0f, 1.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 3
		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 0

		Vertex{ { 1.0f, 0.0f, 1.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 1 - RIGHT
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 5
		Vertex{ { 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 6
		Vertex{ { 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 6	
		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 2
		Vertex{ { 1.0f, 0.0f, 1.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 1

		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 2 - TOP
		Vertex{ { 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 6
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 7
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 7	
		Vertex{ { 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 3
		Vertex{ { 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 2

		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 5 - BACK
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 4
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 7
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 7	
		Vertex{ { 1.0f, 1.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 6
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 5

		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 4 - LEFT
		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 0
		Vertex{ { 0.0f, 1.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 3
		Vertex{ { 0.0f, 1.0f, 1.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 3	
		Vertex{ { 0.0f, 1.0f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 7
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 4

		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 0 - BOTTOM
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 4
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 5
		Vertex{ { 1.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 5	
		Vertex{ { 1.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 1
		Vertex{ { 0.0f, 0.0f, 1.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }  // 0
	};

	Mesh cube = Mesh(v);

	cube.setPosition(Vec3(-0.5f, -0.65f, 0.0f));
	cube.setRotation(0.0f);
	cube.setScale(Vec3(0.25f));
	cube.setColor(Vec4());

	meshes.push_back(cube);

	std::vector<Vertex> Pyramid =
	{
		//front
		Vertex { { 0.0f, 0.0f, 0.25f, 1.0f }, {} },
		Vertex { { 0.25f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.25f, 1.0f },{} },

		//right
		Vertex{ { 0.25f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.25f, 1.0f },{} },

		//back
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.0f, 1.0f },{} },

		//top
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.25f, 0.0f, 1.0f },{} },
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{} },
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{} },

		//bottom
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.0f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.25f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{} },
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{} },

	};

	Mesh pyramid = Mesh(Pyramid);

	/*pyramid.setPosition(Vec3(0.0f, 0.25f, 0.0f));
	pyramid.setRotation(0.0f);
	pyramid.setScale(Vec3(1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);*/

	/*std::vector<Vertex> Cube =
	{
		//front
		Vector4(0.0f, 0.0f, 0.25f, 1.0f),
		Vector4(0.25f, 0.0f, 0.25f, 1.0f),
		Vector4(0.25f, 0.25f, 0.25f, 1.0f),
		Vector4(0.25f, 0.25f, 0.25f, 1.0f),
		Vector4(0.0f, 0.25f, 0.25f, 1.0f),
		Vector4(0.0f, 0.0f, 0.25f, 1.0f),

		//right
		Vector4(0.25f, 0.0f, 0.25f, 1.0f),
		Vector4(0.25f, 0.0f, 0.0f, 1.0f),
		Vector4(0.25f, 0.25f, 0.0f, 1.0f),
		Vector4(0.25f, 0.25f, 0.0f, 1.0f),
		Vector4(0.25f, 0.25f, 0.25f, 1.0f),
		Vector4(0.25f, 0.0f, 0.25f, 1.0f),

		//top
		Vector4(0.25f, 0.25f, 0.25f, 1.0f),
		Vector4(0.25f, 0.25f, 0.0f, 1.0f),
		Vector4(0.0f, 0.25f, 0.0f, 1.0f),
		Vector4(0.0f, 0.25f, 0.0f, 1.0f),
		Vector4(0.0f, 0.25f, 0.25f, 1.0f),
		Vector4(0.25f, 0.25f, 0.25f, 1.0f),

		//back
		Vector4(0.25f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.25f, 0.0f, 1.0f),
		Vector4(0.0f, 0.25f, 0.0f, 1.0f),
		Vector4(0.25f, 0.25f, 0.0f, 1.0f),
		Vector4(0.25f, 0.0f, 0.0f, 1.0f),

		//left
		Vector4(0.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.25f, 1.0f),
		Vector4(0.0f, 0.25f, 0.25f, 1.0f),
		Vector4(0.0f, 0.25f, 0.25f, 1.0f),
		Vector4(0.0f, 0.25f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 1.0f),

		//bottom
		Vector4(0.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.25f, 0.0f, 0.0f, 1.0f),
		Vector4(0.25f, 0.0f, 0.25f, 1.0f),
		Vector4(0.25f, 0.0f, 0.25f, 1.0f),
		Vector4(0.0f, 0.0f, 0.25f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 1.0f),

	};*/

	std::vector<Vertex> Parallelipiped =
	{
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 0 - FRONT
		Vertex{ { 0.425f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 1
		Vertex{ { 0.25f, 0.175f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 2
		Vertex{ { 0.25f, 0.175f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 2	
		Vertex{ { -0.175f, 0.175f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 3
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.0f, 1.0f } }, // 0

		Vertex{ { 0.425f, 0.0f, 0.25f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 1 - RIGHT
		Vertex{ { 0.425f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 5
		Vertex{ { 0.25f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 6
		Vertex{ { 0.25f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 6	
		Vertex{ { 0.25f, 0.175f, 0.25f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 2
		Vertex{ { 0.425f, 0.0f, 0.25f, 1.0f },{ 0.0f, 0.9f, 0.0f, 1.0f } }, // 1

		Vertex{ { 0.25f, 0.175f, 0.25f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 2 - TOP
		Vertex{ { 0.25f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 6
		Vertex{ { -0.175f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 7
		Vertex{ { -0.175f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 7	
		Vertex{ { -0.175f, 0.175f, 0.25f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 3
		Vertex{ { 0.25f, 0.175f, 0.25f, 1.0f },{ 0.0f, 0.0f, 0.9f, 1.0f } }, // 2

		Vertex{ { 0.425f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 5 - BACK
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 4
		Vertex{ { -0.175f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 7
		Vertex{ { -0.175f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 7	
		Vertex{ { 0.25f, 0.175f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 6
		Vertex{ { 0.425f, 0.0f, 0.0f, 1.0f },{ 0.0f, 0.9f, 0.9f, 1.0f } }, // 5

		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 4 - LEFT
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 0
		Vertex{ { -0.175f, 0.175f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 3
		Vertex{ { -0.175f, 0.175f, 0.25f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 3	
		Vertex{ { -0.175f, 0.175f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 7
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.0f, 0.9f, 1.0f } }, // 4

		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 0 - BOTTOM
		Vertex{ { 0.425f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 4
		Vertex{ { 0.425f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 5
		Vertex{ { 0.425f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 5	
		Vertex{ { 0.0f, 0.0f, 0.25f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }, // 1
		Vertex{ { 0.0f, 0.0f, 0.0f, 1.0f },{ 0.9f, 0.9f, 0.0f, 1.0f } }  // 0
	};

	Mesh parallelipiped = Mesh(Parallelipiped);

	parallelipiped.setPosition(Vec3(0.35f, -0.35f, 0.0f));
	parallelipiped.setRotation(135.0f);
	parallelipiped.setScale(Vec3(1.0f));
	parallelipiped.setColor(Vec4());

	meshes.push_back(parallelipiped);

	pyramid.setPosition(Vec3(0.0f, -0.65f, 0.0f));
	pyramid.set3DRotation(Vec3(0.0f, 180.0f, 0.0f));
	pyramid.setScale(Vec3(-1.0f, 1.0f, 1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);

	pyramid.setPosition(Vec3(-0.25f, -0.35f, 0.0f));
	pyramid.setRotation(45.0f);
	pyramid.setScale(Vec3(1.5f, 1.5f, 1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);

	pyramid.setPosition(Vec3(-0.50f, -0.65f, 0.0f));
	pyramid.setRotation(-90.0f);
	pyramid.setScale(Vec3(1.0f, 1.0f, 1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);

	pyramid.setPosition(Vec3(-1.0f, -0.15f, 0.0f));
	pyramid.setRotation(20.0f);
	pyramid.setScale(Vec3(3.0f, 3.0f, 1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);

	pyramid.setPosition(Vec3(-0.50f, -0.15f, 0.0f));
	pyramid.setRotation(20.0f);
	pyramid.setScale(Vec3(3.0f, 3.0f, 1.0f));
	pyramid.setColor(Vec4());

	meshes.push_back(pyramid);

	glClearColor(CLEAR_COLOR.x, CLEAR_COLOR.y, CLEAR_COLOR.z, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Renderer::reshapeViewport(int _newWidth, int _newHeight)
{
	glViewport(0, 0, _newWidth, _newHeight);
}

void Renderer::setProjectionMatrix(const Mat4& mat)
{
	projectionMatrix = mat;
}

void Renderer::setViewMatrix(const Mat4& mat)
{
	viewMatrix = mat;
}

void Renderer::checkOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}