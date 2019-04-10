#version 400 core

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

uniform sampler2D background_texture;
uniform sampler2D r_texture;
uniform sampler2D g_texture;
uniform sampler2D b_texture;
uniform sampler2D blend_texture;

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
#define MAX_POINT_LIGHTS 64
uniform Point_light point_lights[MAX_POINT_LIGHTS];
uniform int point_light_number;

in vec3 fragment_position;
in vec3 vertex_normal;
in vec2 texture_coords;

out vec4 out_color;

vec3 calculate_directional_light(Sun sun, vec3 normal, vec3 view_direction, vec4 total_color)
{
	vec3 light_direction = normalize(sun.light_position - fragment_position);
	vec3 ambient = vec3(total_color) * sun.ambient;
	
	float diff = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diff * vec3(total_color) * sun.diffuse;
	
	vec3 result = ambient + diffuse;
	
	return result;
}

vec3 calculate_point_light(Point_light light, vec3 normal, vec3 fragment_position, vec3 view_direction, vec4 total_color)
{
	vec3 light_direction = normalize(light.position - fragment_position);
    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);
    // specular shading
    // attenuation
    float distance    = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
								light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(total_color);
    vec3 diffuse  = light.diffuse  * diff * vec3(total_color);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    return (ambient + diffuse);
}

void main()
{	
	vec4 blend_map_color = texture(blend_texture, texture_coords / 256);
	float background_texture_amount = 1 - (blend_map_color.r + blend_map_color.g + blend_map_color.b);
	
	vec4 background_texture_color = texture(background_texture, texture_coords) * background_texture_amount;

	vec4 r_texture_color = texture(r_texture, texture_coords) * blend_map_color.r;
	vec4 g_texture_color = texture(g_texture, texture_coords) * blend_map_color.g;
	vec4 b_texture_color = texture(b_texture, texture_coords) * blend_map_color.b;
	vec4 total_color = background_texture_color + r_texture_color + g_texture_color + b_texture_color;
	
	vec3 norm = normalize(vertex_normal);
	vec3 view_direction = normalize(camera_position - fragment_position);
	
	vec3 result = calculate_directional_light(sun, norm, view_direction, total_color);
	for(int i = 0; i < point_light_number; i++)
	{
		result += calculate_point_light(point_lights[i], norm, fragment_position, view_direction, total_color);
	}
	
	out_color = vec4(result, 1.0);
}