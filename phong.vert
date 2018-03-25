#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inUV0;
layout (location = 2) in vec3 inNormal;

out vec2 outUV0;
out vec3 outWorldPos;
out vec3 outNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalTrans;

void main()
{
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(inPos, 1.0);
	
	outUV0 = inUV0;
	outWorldPos = (model * vec4(inPos, 1.0)).xyz;
	outNormal = (normalTrans * vec4(inNormal, 1.0)).xyz;
}
