#version 400 core

layout (location = 0) in vec3 position;

out vec3 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = view * projection * vec4(position, 1.0f);
	TexCoord = position;
	gl_Position = pos.xyzw;
}