#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV0;

out vec4 vertexColor;
out vec2 UV0;

uniform vec4 time1;

void main()
{
	gl_Position = vec4(aPos.x + .5 * cos(time1.x), aPos.y + .5 * sin(time1.x), 0, 1.0);
	vertexColor.rgb = aPos + .5;
	vertexColor.a = 1;
	UV0 = aUV0;
}
