#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec4 color;

uniform mat4 mvp_matrix;

void main()
{
	vec4 transformed_position = mvp_matrix * vec4(position, 1.0);
	gl_Position = transformed_position;

	color = vec4(0.8, 0.6, 0.4, 1.0);
}