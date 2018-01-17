#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "GL\glew.h"

#define SHADER2PATH "../../projects/engine/resources/shaders/"


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
