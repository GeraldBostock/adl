#version 400 core

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

struct Light
{
	vec3 light_position;
	vec3 light_color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

in vec3 fragment_position;
in vec3 vertex_normal;
in vec2 texture_coords;

out vec4 out_color;

void main()
{
	vec3 ambient = vec3(texture(material.diffuse, texture_coords)) * light.ambient;
	
	vec3 norm = normalize(vertex_normal);
	vec3 view_direction = normalize(camera_position - fragment_position);
	vec3 light_direction = normalize(light.light_position - fragment_position);
	vec3 reflection_direction = reflect(-light_direction, norm);
	
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, texture_coords)) * spec * light.specular;
	
	float diff = max(dot(norm, light_direction), 0.0);
	vec3 diffuse = diff * vec3(texture(material.diffuse, texture_coords)) * light.diffuse;
	
	vec3 result = ambient + diffuse + specular;
	
	out_color = vec4(result, 1.0);
}