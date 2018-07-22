#include "adlStatic_shader.h"



adlStatic_shader::adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file)
{
	/*super::*/init(vertex_file, fragment_file);
}


adlStatic_shader::~adlStatic_shader()
{

}

void adlStatic_shader::bind_attributes()
{
	/*super::*/bind_attribute(0, "position");
	/*super::*/bind_attribute(1, "normal");
	/*super::*/bind_attribute(2, "uv");
}

void adlStatic_shader::get_all_uniform_locations()
{
	projection_matrix_location_ = /*super::*/get_uniform_location("projectionMatrix");
	view_matrix_location_ = /*super::*/get_uniform_location("viewMatrix");
}

//void adlStatic_shader::loadProjectionMatrix(glm::mat4 matrix)
//{
//	super::loadMatrix(m_projectionMatrixLocation, matrix);
//}
//
//void adlStatic_shader::loadViewMatrix(Camera camera)
//{
//	glm::mat4 viewMatrix = Maths::CreateViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw());
//	super::loadMatrix(m_viewMatrixLocation, viewMatrix);
//}
