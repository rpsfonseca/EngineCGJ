#pragma once

#include "Shader.h"

class Material
{
public:
	Shader shader;

	Material();
	Material(std::string shaderName);
	~Material();
};