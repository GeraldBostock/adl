#version 400 core

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;

out vec3 fragment_position;
out vec3 vertex_normal;
out vec2 texture_coords;

void main()
{
	vec4 transformed_position = mvp_matrix * vec4(position, 1.0);
	gl_Position = transformed_position;
	
	vertex_normal = mat3(transpose(inverse(model_matrix))) * normal;
	fragment_position = vec3(model_matrix * vec4(position, 1.0));
	
	texture_coords = uv;
}