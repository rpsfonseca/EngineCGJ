#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "GL\glew.h"


class Shader2 {
public:
	GLuint createFromFile(const char * const vertexFile,
		const char * const fragmentFile);
	void terminate();
private:
	GLuint vertexShader;
	GLuint fragmentShader;
};

#endif
