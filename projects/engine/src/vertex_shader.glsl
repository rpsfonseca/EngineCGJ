#version 330 core
layout(location = 0) in vec4 bPosition;
layout(location = 1) in vec4 bColor;

out vec4 aColor;

uniform mat4 Matrix;

void main()
{
	gl_Position = Matrix * bPosition;
	aColor = bColor;
}