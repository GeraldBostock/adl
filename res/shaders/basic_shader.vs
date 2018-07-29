#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec4 color;

uniform mat4 transformation_matrix;

void main()
{
	gl_Position = transformation_matrix * vec4(position, 1.0f);

	color = vec4(position.y, position.y, position.y, 1.0);
}