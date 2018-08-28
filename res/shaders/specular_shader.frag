#version 400 core

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

in vec3 fragment_position;
in vec3 vertex_normal;

out vec4 out_color;

void main()
{
	float ambient_strength = 0.2;
	vec3 ambient = ambient_strength * light_color;
	
	float specular_strength = 0.8;
	
	vec3 norm = normalize(vertex_normal);
	vec3 view_direction = normalize(camera_position - fragment_position);
	vec3 light_direction = normalize(light_position - fragment_position);
	vec3 reflection_direction = reflect(-light_direction, norm);
	
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
	vec3 specular = specular_strength * spec * light_color;
	
	vec3 result = (ambient + specular) * object_color;
	
	out_color = vec4(result, 1.0);
}