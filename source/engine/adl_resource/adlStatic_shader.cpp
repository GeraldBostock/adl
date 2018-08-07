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
	transformation_matrix_location_ = get_uniform_location("transformation_matrix");
	projection_matrix_location_ = get_uniform_location("projection_matrix");
	view_matrix_location_ = get_uniform_location("viewMatrix");
}

void adlStatic_shader::load_transformation(const adlMat4& matrix)
{
	load_matrix(transformation_matrix_location_, matrix);
}

void adlStatic_shader::load_projection(const adlMat4& matrix)
{
	load_matrix(projection_matrix_location_, matrix);
}

//void adlStatic_shader::loadViewMatrix(Camera camera)
//{
//	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw());
//	super::loadMatrix(m_viewMatrixLocation, viewMatrix);
//}
