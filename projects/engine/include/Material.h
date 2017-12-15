#pragma once

#include "Shader.h"
#include "Texture.h"

#include <map>

/**
	This struct represents a shader uniform of type sampler2d.
*/
struct UniformSampler
{
	unsigned int unit;
	Texture* texture;
};

class Material
{
public:
	Shader shader;
	std::map<std::string, UniformSampler> textures;

	Material();
	Material(std::string shaderName);
	~Material();

	void setTexture(std::string name, Texture* value, unsigned int unit = 0);
};