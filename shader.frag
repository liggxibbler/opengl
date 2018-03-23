#version 330 core

uniform vec4 time1;

out vec4 FragColor;

void main()
{
	FragColor = gl_FragCoord + sin(time1.x);
}
