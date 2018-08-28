#version 400 core

in vec2 texture_coordinates;
out vec4 color;

uniform sampler2D text;
uniform vec3 text_color;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texture_coordinates).r);
	color = vec4(text_color, 1.0) * sampled;
}