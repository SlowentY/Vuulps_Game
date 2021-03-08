#version 400 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos

out vec4 color;

uniform vec3 brightness;
uniform vec3 lightPos;

unifor sampler2D tex

void main()
{
	vec4 ambient = vec4(brightness.xyz, 1.0f) * 0.15f;

	vec3 norm = normalize(Normal);
	vec3 dir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, dir), 0.0);

	vec3 diffusion = diff * brightness;

	vec3 res = (ambient + diffusion) * texture(tex, TexCoords);

	color = vec4(res, 1.0f);
}