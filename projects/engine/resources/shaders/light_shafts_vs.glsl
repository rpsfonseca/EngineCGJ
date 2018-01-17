/**
 * This file is a part of a project from http://zompi.pl/light-shafts/
 * (c) 2014 Damian Nowakowski
 */

#version 330

in vec2 inPosition;
in vec2 inTexCoord;
out vec2 inoutTexCoord;

void main()
{
	// Just pass the position and texture coordinates to the fragment shader.
    inoutTexCoord = inTexCoord;
	gl_Position = vec4(inPosition,0,1);
}
