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

	float diffuse = max(dot(outNormal, light_pos.xyz - outWorldPos), 0);

	vec3 toEye = normalize(eye_pos.xyz - outWorldPos);
	vec3 fromSrc = normalize(outWorldPos - light_pos.xyz);
	vec3 reflected = -2*dot(fromSrc, outNormal)*outNormal + fromSrc;
	float specular = max (0, dot(toEye, reflected));
	
	vec4 light_final = (diffuse + specular) * light_col;

	FragColor = mix(col0, col1, .2) * light_final;
}
