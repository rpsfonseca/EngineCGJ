#version 330 core
layout(location = 0) in vec4 bPosition;
layout(location = 1) in vec4 bColor;

out vec4 aColor;

uniform mat4 modelMatrix;

uniform SharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * bPosition;
	aColor = bColor;
}