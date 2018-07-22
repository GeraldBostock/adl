#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec4 color;

void main()
{
	gl_Position = vec4(position, 1.0);

	color = vec4(position.y, position.y, position.y, 1.0);
}