#version 330 core
layout(location = 0) in vec3 position;

out vec3 exPosition;

uniform mat4 modelMatrix;
uniform float runTime;


uniform SharedMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

void main()
{
	exPosition = position;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}