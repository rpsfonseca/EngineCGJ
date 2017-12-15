#version 330 core

in vec3 exPosition;
out vec4 FragColor;

void main(void)
{
	FragColor = vec4(.5-exPosition,1);
}