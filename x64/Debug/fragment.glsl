#version 400 core

in vec2 TexCoord;

out vec4 color;
uniform sampler2D tex;
uniform vec3 brightness;

void main()
{
	vec4 ambient = vec4(brightness.xyz, 1.0f) * 0.15f;
	color = texture(tex, TexCoord) * ambient;
}