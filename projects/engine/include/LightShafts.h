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
	/**
	* Simple constructor and destructor
	*/
	LightShafts(GLuint shaderId);
	~LightShafts();

	/// Light shafts parameters (names explain everything)
	int samples;
	GLfloat exposure;
	GLfloat decay;
	GLfloat density;
	GLfloat weight;
	GLfloat backLightColor;

	/**
	* Update the uniform buffer with new light shafts parameters.
	*/
	void UpdateUniformBuffer();

	/// Always render using functions below in that order:
	/// 1 - StartDrawingOcclusion
	/// 2 - StartDrawingNormal
	/// 3 - DrawLightShafts
	/*
	* Run this before rendering the occlusion. The occlusion will be saved
	* to texture and used to compose the light shafts effect.
	* @param scene - the current scene
	*/
	void StartDrawingOcclusion();

	/*
	* Run this before rendering the normal scene. This scene will be saved
	* to texture and used to compose the light shafts effect.
	* @param scene - the current scene
	*/
	void StartDrawingNormal();

	/*
	* After getting occlusion texture and normal scene texture run this method.
	* It will compose previous textures and render the final scene on the screen.
	* @param camera - currently using camera
	* @param light	- currently using point light
	*/
	void DrawLightShafts(Camera camera);

private:

	GLuint shader;								///< Handler of the shader that draws final scene	
	GLuint vertex_loc;							///< Vertex pointer needed for shader
	GLuint texcoord_loc;						///< Texture coordinates pointer needed for shader

	unsigned int renderTextureArrayColor;				///< Textures array for color handler
	unsigned int renderTextureArrayDepth;				///< Textures array for depth handler
	GLuint frameBuffers[2];						///< Frame buffers for rendering to textures

	GLuint VAO;									///< Vertex array object for shader that renders final scene
	GLuint VBO[2];								///< Vertex buffer object for shader that renders final scene 
												///< (for verticies and texcoodrs)
	GLuint UBO;									///< Uniform buffer object for shader that render final scene 
												///< where light shafts parameters are stored.

	GLint uniformsOffset[SHAFTS_UNIFORM_SIZE];	///< Array that stores offsets of values in uniform buffer
};