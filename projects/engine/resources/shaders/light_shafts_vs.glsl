#version 330

in vec2 inPosition;
in vec2 inTexCoord;
out vec2 inoutTexCoord;

void main()
{
    inoutTexCoord = inTexCoord;
	gl_Position = vec4(inPosition,0,1);
}
