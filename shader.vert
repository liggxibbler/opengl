#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV0;

out vec2 UV0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(aPos, 1.0);
	UV0 = aUV0;
}
