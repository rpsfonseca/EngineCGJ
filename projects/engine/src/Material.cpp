#include "Material.h"

Material::Material()
{
	shader = Shader("quad.vs", "quad.fs");
}

Material::Material(std::string shaderName)
{
	const char* vertexShaderPath = (shaderName + ".vs").c_str();
	const char* fragmentShaderPath = (shaderName + ".fs").c_str();
	shader = Shader(vertexShaderPath, fragmentShaderPath);
}

Material::~Material()
{

}