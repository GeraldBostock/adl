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

struct Sun
{
	vec3 light_position;
	vec3 light_color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Sun sun;

struct Point_light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};
uniform Point_light point_light;

in vec3 fragment_position;
in vec3 vertex_normal;
in vec2 texture_coords;

out vec4 out_color;

vec3 calculate_directional_light(Sun sun, vec3 normal, vec3 view_direction)
{
	vec3 light_direction = normalize(sun.light_position - fragment_position);
	vec3 ambient = vec3(texture(material.diffuse, texture_coords)) * sun.ambient;
	vec3 reflection_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, texture_coords)) * spec * sun.specular;
	
	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diff * vec3(texture(material.diffuse, texture_coords)) * sun.diffuse;
	
	vec3 result = ambient + diffuse + specular;
	
	return result;
}

vec3 calculate_point_light(Point_light light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
	vec3 light_direction = normalize(light.position - fragment_position);
    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflection_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
								light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, texture_coords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, texture_coords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texture_coords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{	
	vec3 norm = normalize(vertex_normal);
	vec3 view_direction = normalize(camera_position - fragment_position);
	
	vec3 directional_result = calculate_directional_light(sun, norm, view_direction);
	vec3 point_light_result = calculate_point_light(point_light, norm, fragment_position, view_direction);
	
	out_color = vec4(directional_result + point_light_result, 1.0);
}