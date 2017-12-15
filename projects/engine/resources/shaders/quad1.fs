#version 330 core

in vec3 exPosition;
out vec4 FragColor;

uniform float runTime;


void main(void)
{
	FragColor = vec4(1+cos(runTime)-exPosition,1);
}