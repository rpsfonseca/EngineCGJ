#pragma once

#include "GL\glew.h"

#include "Mat4.h"
#include "Vec3.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define SHADERPATH "../../projects/engine/resources/shaders/"

class Shader
{
private:
	std::string mName;

public:
	Shader();
	Shader(const GLchar* vertexSource, const GLchar* fragmentSource);
	~Shader();

	void Compile(const GLchar* vsCode, const GLchar* fsCode);

	/* Use program */
	Shader& use();
	void deleteProgram();

	void setName(std::string name) { mName = name; }

	void setInteger(const GLchar* field, GLint value);
	void setFloat(const GLchar* field, GLfloat value);
	void setMat4(const GLchar* field, const math::Mat4& matrix);
	void setVec3(const GLchar* field, const math::Vec3& vector);
	void setVec4(const GLchar* field, const math::Vec4& vector);

	void printCompileErrors(int vOrF, GLuint shader, GLchar* infoLog);
	void printLinkingErrors(GLchar* infoLog);
	GLuint shaderID;

	GLuint uniformBlockBinding();

};

