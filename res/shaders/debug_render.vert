#version 400 core

in vec3 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view_matrix * model_matrix * vec4(position, 1.0);
}
