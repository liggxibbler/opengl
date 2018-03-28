#version 330 core

in vec2 outUV0;
out vec4 outCol;
uniform sampler2D screenTex;

void main()
{
	vec4 col = texture(screenTex, outUV0);
	float avg = .2126 * col.r + .7152 * col.g + .0722 * col.b;
	outCol = vec4(vec3(avg), 1.0);
}
