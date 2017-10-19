#pragma once

#include "GL\glew.h"

#include "Mat4.h"
#include "Vec3.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
	Shader& Use();
	void DeleteProgram();

	void SetName(std::string name) { mName = name; }

	void SetInteger(const GLchar* field, GLint value);
	void SetFloat(const GLchar* field, GLfloat value);
	void SetMat4(const GLchar* field, const math::Mat4& matrix);
	void SetVec3(const GLchar* field, const math::Vec3& vector);

	void PrintCompileErrors(int vOrF, GLuint shader, GLchar* infoLog);
	void PrintLinkingErrors(GLchar* infoLog);
	GLuint shaderID;

};

