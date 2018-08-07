#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec4 color;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;

void main()
{
	vec4 transformed_position = projection_matrix * transformation_matrix * vec4(position, 1.0f);
	gl_Position = transformed_position;

	color = vec4(transformed_position.y, transformed_position.y, transformed_position.y, 1.0);
}