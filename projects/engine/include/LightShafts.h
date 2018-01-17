#pragma once

#include "GL\glew.h"
#include "Shader.h"

// Define the uniform buffer elements of light shafts shader
#define SHAFTS_UNIFORM_SIZE 5

// Predefine classes for visibility
class Camera;
class Light;

class LightShafts
{
public:

	LightShafts(GLuint shaderId);
	~LightShafts();

	int samples;
	GLfloat exposure;
	GLfloat decay;
	GLfloat density;
	GLfloat weight;
	GLfloat backLightColor;

	void UpdateUniformBuffer();

	/*
	Order:
		1 - StartDrawingOcclusion
			2 - StartDrawingNormal
				3 - DrawLightShafts
	*/

	void StartDrawingOcclusion();
	void StartDrawingNormal();
	void DrawLightShafts(Camera camera);

private:

	GLuint shader;								
	GLuint vertex_loc;							
	GLuint texcoord_loc;						

	unsigned int renderTextureArrayColor;				
	unsigned int renderTextureArrayDepth;				
	GLuint frameBuffers[2];						

	GLuint VAO;									
	GLuint VBO[2];								
												
	GLuint UBO;									
												

	GLint uniformsOffset[SHAFTS_UNIFORM_SIZE];	
};