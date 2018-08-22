#version 400 core

struct Light
{	
	vec3 light_color;
};
uniform Light light;

out vec4 out_color;

void main()
{
	out_color = vec4(light.light_color, 1.0);
}