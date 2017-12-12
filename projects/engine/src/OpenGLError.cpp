#include "OpenGLError.h"

#include "GL\glew.h"
#include <iostream>

OpenGLError::OpenGLError()
{
}

OpenGLError::~OpenGLError()
{
}

bool OpenGLError::isOpenGLError() {
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

void OpenGLError::checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		int wait;
		std::cin >> wait;
		exit(EXIT_FAILURE);
	}
}