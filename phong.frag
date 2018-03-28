#version 330 core

in vec2 outUV0;
in vec3 outWorldPos;
in vec3 outNormal;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec4 light_pos;
uniform vec4 eye_pos;
uniform vec4 light_col;
uniform vec4 shininess;

void main()
{
	vec4 col0 = texture(texture0, outUV0);
	vec4 col1 = texture(texture1, outUV0);

	vec3 toLight = light_pos.xyz - outWorldPos;
	vec3 toEye = eye_pos.xyz - outWorldPos;
	vec3 toLightNormal = normalize(toLight);
	float atten = exp(length(toLight) * -.2);

	float diffuse = max(dot(outNormal, toLightNormal), 0);

	vec3 reflected = 2 * dot(toLightNormal, outNormal)*outNormal - toLightNormal;
	float specular = pow(max (dot(normalize(toEye), reflected), 0), 128);
	
	vec4 light_final = (diffuse + specular) * light_col * atten;

	FragColor = mix(col0, col1, .5) * light_final;
}
