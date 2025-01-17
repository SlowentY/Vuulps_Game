#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	mat4 trans = projection * view * model;
	gl_Position = trans * vec4(position, 1.0f);
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}