#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV0;

out vec2 outUV0;

void main()
{
	gl_Position = vec4(inPos, 1.0f);
	outUV0 = inUV0;
}
