#pragma once
#include <string>
#include <iostream>
#include "GL\glew.h"

#define TEXTURE_PATH "../../projects/engine/resources/textures/"

class Texture {
private:
	int width, height;
	unsigned int tex_id;
	bool mipMapsGenerated;

	int tex_filter_Magnification;
	int tex_filter_Minification;

	std::string path;
public:
	bool loadTexture2D(std::string& filepath, bool generateMipMaps = true);

	void bind(unsigned int unit);
	void releaseTexture();

	Texture();

};
