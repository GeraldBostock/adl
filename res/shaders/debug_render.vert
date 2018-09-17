#version 400 core

in vec3 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection;
uniform int switch_;

void main()
{
	if(switch_ == 1)
	{
		gl_Position = projection * view_matrix * model_matrix * vec4(position, 1.0);
	}
	else
	{
		gl_Position = projection * view_matrix * vec4(position, 1.0);
	}
}
