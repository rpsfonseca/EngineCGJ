#include "Texture.h"

void Texture::createTextureFromData()
{
	mipMapsGenerated = false;	
}

bool Texture::loadTexture2D(std::string & filepath, bool generateMipMaps)
{
	int components;
	GLuint texID;
	int tWidth, tHeight;

	unsigned char* data = stbi_load(filepath.c_str(), &tWidth, &tHeight, &components, 3);



	return false;
}

void Texture::bindTexture(int texureUnit)
{
}

void Texture::setFiltering(int tex_filter_Magnification, int tex_filter_Minification)
{
}

void Texture::setSamplerParameter(GLenum parameter, GLenum value)
{
}

int Texture::getMinificationFilter()
{
	return 0;
}

int Texture::getMagnificationFilter()
{
	return 0;
}

int Texture::getWidth()
{
	return 0;
}

int Texture::getHeight()
{
	return 0;
}

int Texture::getBytesPerPixel()
{
	return 0;
}

void Texture::releaseTexture()
{
}

Texture::Texture()
{
}
