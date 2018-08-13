#include "adlStatic_shader.h"

#include "iostream"


adlStatic_shader::adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file)
{
	init(vertex_file, fragment_file);
}


adlStatic_shader::~adlStatic_shader()
{

}

void adlStatic_shader::bind_attributes()
{
	bind_attribute(0, "position");
	bind_attribute(1, "normal");
	bind_attribute(2, "uv");
}

void adlStatic_shader::get_all_uniform_locations()
{
	mvp_matrix_location_ = get_uniform_location("mvp_matrix");
}

void adlStatic_shader::load_mvp(const adlMat4& matrix)
{
	load_matrix(mvp_matrix_location_, matrix);
}
