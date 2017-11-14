#version 330 core
layout(location = 0) in vec4 bPosition;
layout(location = 1) in vec2 bTexCoord;
layout(location = 2) in vec3 bNormal;

out vec4 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

uniform mat4 modelMatrix;

uniform SharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

void main()
{
	exPosition = bPosition;
	exTexcoord = bTexCoord;
	exNormal = bNormal;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * bPosition;
}