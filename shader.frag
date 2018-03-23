#version 330 core

in vec2 UV0;
out vec4 FragColor;

uniform vec4 time1;
uniform sampler2D texture0;

void main()
{
	vec4 col = texture(texture0, UV0);
	FragColor = col;// + vec4((sin(time1.x)+1)*.5, 0, 0, 1);
}
