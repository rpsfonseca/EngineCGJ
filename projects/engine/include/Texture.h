#pragma once
#include <string>
#include "GL\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class Texture {
private:
	int width, height, bpp;
	unsigned int tex_id;
	unsigned int sampler_id;
	bool mipMapsGenerated;

	int tex_filter_Magnification;
	int tex_filter_Minification;

	std::string path;
public:
	void createTextureFromData();
	bool loadTexture2D(std::string& filepath, bool generateMipMaps);
	void bindTexture(int texureUnit = 0);

	void setFiltering(int tex_filter_Magnification, int tex_filter_Minification);

	void setSamplerParameter(GLenum parameter, GLenum value);

	int getMinificationFilter();
	int getMagnificationFilter();

	int getWidth();
	int getHeight();
	int getBytesPerPixel();

	void releaseTexture();

	Texture();

};
