#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


bool Texture::loadTexture2D(std::string & filename, bool generateMipMaps)
{
	int components;
	GLuint texID;
	int tWidth, tHeight;

	std::string filepath = std::string(TEXTURE_PATH);
	filepath.append(filename);

	unsigned char* data = stbi_load(filepath.c_str(), &tWidth, &tHeight, &components, 3);
	if (data)
	{

		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);

	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if(generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

	}
	else {
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
		return false;
	}

	width = tWidth;
	height = tHeight;
	if ((width == 0) || (height == 0)) {
	//shouldn't be possible to get inside
		stbi_image_free(data);
		return false;
	}





	return true;
}


void Texture::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, tex_id);
}

void Texture::releaseTexture()
{
	glDeleteTextures(1, &tex_id);
}

Texture::Texture()
{
}
