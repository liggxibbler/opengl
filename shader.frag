#version 330 core

in vec2 UV0;
out vec4 FragColor;

uniform vec4 time1;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	vec4 col0 = texture(texture0, UV0);
	vec4 col1 = texture(texture1, UV0);

	FragColor = mix(col0, col1, .2);
}
