#include "Shader.h"

Shader::Shader() {}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// Ensures ifstream objects can throw exceptions
	vertexShaderFile.exceptions(std::ifstream::badbit);
	vertexShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		// Open files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		// Read the file's buffer into streams
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Convert stream into GLchar array
		vertexSource = vertexShaderStream.str();
		fragmentSource = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar* vertexShaderSource = vertexSource.c_str();
	const GLchar* fragmentShaderSource = fragmentSource.c_str();

	// Compile shaders
	GLuint vertex, fragment;
	GLchar infoLog[512];

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	printCompileErrors(0, vertex, infoLog);

	// Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	printCompileErrors(1, fragment, infoLog);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	// Print linking errors if any
	printLinkingErrors(infoLog);

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader()
{
}

void Shader::Compile(const GLchar* vsCode, const GLchar* fsCode)
{
	// Compile shaders
	GLuint vertex, fragment;
	GLchar infoLog[512];

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vsCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	printCompileErrors(0, vertex, infoLog);

	// Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fsCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	printCompileErrors(1, fragment, infoLog);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertex);
	glAttachShader(shaderID, fragment);
	glLinkProgram(shaderID);
	// Print linking errors if any
	printLinkingErrors(infoLog);

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader& Shader::use()
{
	glUseProgram(shaderID);
	return *this;
}

void Shader::deleteProgram()
{
	glDeleteProgram(shaderID);
}

void Shader::setInteger(const GLchar* field, GLint value)
{
	GLint loc = glGetUniformLocation(shaderID, field);
	glUniform1i(loc, value);
}

void Shader::setFloat(const GLchar* field, GLfloat value)
{
	GLfloat loc = glGetUniformLocation(shaderID, field);
	glUniform1f(loc, value);
}

void Shader::setMat4(const GLchar* field, const math::Mat4& mat)
{
	GLint loc = glGetUniformLocation(shaderID, field);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat.matrix[0]);
}

void Shader::setVec3(const GLchar* field, const math::Vec3& vector)
{
	GLint loc = glGetUniformLocation(shaderID, field);
	glUniform3f(loc, vector.x, vector.y, vector.z);
}

void Shader::setVec4(const GLchar* field, const math::Vec4& vector)
{
	GLint loc = glGetUniformLocation(shaderID, field);
	glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
}

void Shader::printCompileErrors(int vOrF, GLuint shader, GLchar* infoLog)
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (vOrF == 0)
		{
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}

void Shader::printLinkingErrors(GLchar* infoLog)
{
	GLint success = 0;
	glGetProgramiv(shaderID, GL_LINK_STATUS, (int *)&success);
	if (success == GL_FALSE)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

GLuint Shader::uniformBlockBinding()
{
	GLuint test = 0;
	GLint uboID = glGetUniformBlockIndex(shaderID, "SharedMatrices");
	glUniformBlockBinding(shaderID, uboID, test);
	return test;
}