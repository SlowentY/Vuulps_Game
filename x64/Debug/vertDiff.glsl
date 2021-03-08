#version 400 core

in (location = 0) vec3 position;
in (location = 1) vec2 texCoords;
in (location = 3) vec3 normal;

out vec3 Normal;
out vec3 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 trans = projection * view * model;
	gl_Position = trans * vec4(position, 1.0f);
	TexCoords = texCoords;

	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = normal;
}