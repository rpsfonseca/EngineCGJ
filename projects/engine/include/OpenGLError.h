#pragma once

#include <string>

class OpenGLError
{
public:
	OpenGLError();
	~OpenGLError();

	static void checkOpenGLError(std::string error);

private:
	static bool isOpenGLError();
};
