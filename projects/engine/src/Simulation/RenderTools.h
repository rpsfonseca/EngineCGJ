#ifndef RENDERUTILITY_H
#define RENDERUTILITY_H

#include <string>
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Vec3.h"
#include "Vec2.h"
#include "Mat4.h"

GLuint createVBO(float vertices[], int size);
GLuint createEBO(int elements[], int size);
void deleteVBOs();
void deleteEBOs();
void initializeTextures(GLuint volumeTexture, GLuint* planarTextures);
void deleteTextures(GLuint volumeTexture, GLuint* planarTextures);
void setUniform(const std::string name, const float value);
void setUniform(const std::string name, const math::Vec2 vector);
void setUniform(const std::string name, const math::Vec3 vector);
void setUniform(const std::string name, const math::Mat4 matrix);
float convertXToRelative(const int x);
float convertYToRelative(const int y);

#endif