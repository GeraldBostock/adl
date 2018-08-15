#version 400 core

uniform vec3 object_color;
uniform vec3 light_color;

out vec4 out_color;

void main()
{
	float ambient_strength = 0.2;
	vec3 ambient = ambient_strength * light_color;
	
	vec3 result = ambient * object_color;
	out_color = vec4(result, 1.0);
}