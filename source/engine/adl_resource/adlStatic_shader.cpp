#include "adlStatic_shader.h"

#include <iostream>
#include "engine/adl_entities/adlLight.h"
#include "engine/adl_resource/adlMaterial.h"


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
	model_matrix_location_ = get_uniform_location("model_matrix");
	camera_position_location_ = get_uniform_location("camera_position");
	text_color_location_ = get_uniform_location("text_color");
	projection_matrix_location_ = get_uniform_location("projection");

	ambient_location_ = get_uniform_location("material.ambient");
	diffuse_location_ = get_uniform_location("material.diffuse");
	specular_location_ = get_uniform_location("material.specular");
	shininess_location_ = get_uniform_location("material.shininess");

	light_color_location_ = get_uniform_location("light.light_color");
	light_position_location_ = get_uniform_location("light.light_position");
	light_ambient_location_ = get_uniform_location("light.ambient");
	light_diffuse_location_ = get_uniform_location("light.diffuse");
	light_specular_location_ = get_uniform_location("light.specular");

	texture_location_ = get_uniform_location("material.diffuse");
	texture_specular_location_ = get_uniform_location("material.specular");
}

void adlStatic_shader::load_mvp(const adlMat4& matrix)
{
	load_matrix(mvp_matrix_location_, matrix);
}

void adlStatic_shader::load_model_matrix(const adlMat4& model_matrix)
{
	load_matrix(model_matrix_location_, model_matrix);
}

void adlStatic_shader::load_camera_position(adlVec3 position)
{
	load_vector(camera_position_location_, position);
}

void adlStatic_shader::load_text_color(adlVec3 color)
{
	load_vector(text_color_location_, color);
}

void adlStatic_shader::load_projection_matrix(const adlMat4& matrix)
{
	load_matrix(projection_matrix_location_, matrix);
}

void adlStatic_shader::load_material(adlMaterial_shared_ptr material)
{
	load_vector(ambient_location_, material->get_ambient());
	load_vector(diffuse_location_, material->get_diffuse());
	load_vector(specular_location_, material->get_specular());
	load_float(shininess_location_, material->get_shininess());
}

void adlStatic_shader::load_light(adlLight_shared_ptr light)
{
	load_vector(light_color_location_, light->get_color().to_vec3());
	load_vector(light_position_location_, light->get_transform().o);

	load_vector(light_ambient_location_, light->get_ambient());
	load_vector(light_diffuse_location_, light->get_diffuse());
	load_vector(light_specular_location_, light->get_specular());
}

void adlStatic_shader::load_texture()
{
	load_int(texture_location_, 0);
	load_int(texture_specular_location_, 1);
}
