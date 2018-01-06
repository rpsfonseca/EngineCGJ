#pragma once
#include <string>
#include <iostream>
#include "GL\glew.h"

#define TEXTURE_PATH "../../projects/engine/resources/textures/"

class Texture {
private:
	int width, height;
	bool mipMapsGenerated;

	int tex_filter_Magnification;
	int tex_filter_Minification;

	std::string path;
public:
	unsigned int tex_id;

	bool generateRTTexture();
	bool loadTexture2D(std::string& filepath, bool generateMipMaps = true);

	void bind(unsigned int unit);
	void releaseTexture();

	Texture();

};
