#include "Material.h"

Material::Material()
{
	std::string path_vs = SHADERPATH;
	path_vs.append("quad.vs");
	std::string path_fs = SHADERPATH;
	path_fs.append("quad.fs");
	std::cout << path_fs << std::endl << path_vs << std::endl;
	shader = Shader(path_vs.c_str(), path_fs.c_str());

}

Material::Material(std::string shaderName)
{
	/*const char* vertexShaderPath = (SHADERPATH + shaderName + ".vs").c_str();
	const char* fragmentShaderPath = (SHADERPATH + shaderName + ".fs").c_str();*/
	std::string path_vs = SHADERPATH;
	path_vs.append(shaderName);
	path_vs.append(".vs");
	std::string path_fs = SHADERPATH;
	path_fs.append(shaderName);
	path_fs.append(".fs");

	std::cout << path_fs << std::endl << path_vs << std::endl;

	shader = Shader(path_vs.c_str(), path_fs.c_str());
}

Material::~Material()
{

}

void Material::setTexture(std::string name, Texture* value, unsigned int unit)
{
	textures[name].unit = unit;
	textures[name].texture = value;

	shader.use();
	shader.setInteger(name.c_str(), unit);
}
