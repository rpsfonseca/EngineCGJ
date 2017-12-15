#pragma once
#include "GL\glew.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"
#include <string>
#include <vector>
#include <bitset>


class Skybox
{
public:
	void loadSkybox(std::string t_Front, std::string t_Back, std::string t_Left, std::string t_Right, std::string t_Top, std::string t_Bottom);
	void renderSkybox();
	void releaseSkybox();

	void addData(void* ptrData, GLuint uiDataSize);
private:
	Texture textures[6];
	std::string tFront, tBack, tLeft, tRight, tTop, tBottom;
	GLuint uiVAO;
	GLuint uiBuffer;
	int iSize;
	int iBufferType;
	std::vector<std::bitset<8>> data;
};