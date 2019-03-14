#ifndef adl_static_shader_h__
#define adl_static_shader_h__

#include <string>
#include <vector>

#include "adlShader_program.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adl_resource/adlMaterial.h"
#include "engine/adlShared_types.h"

#define MAX_POINT_LIGHTS 64

class adlStatic_shader : public adlShader_program
{
public:

	adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file);
	~adlStatic_shader();

	void load_mvp(const adlMat4& mvp_matrix);
	void load_model_matrix(const adlMat4& model_matrix);
	void load_light(adlEntity_shared_ptr light);
	void load_point_lights(const std::vector<adlEntity_shared_ptr>& point_lights);
	void load_camera_position(adlVec3 position);
	void load_text_color(adlVec3 color);
	void load_projection_matrix(const adlMat4& matrix);
	void load_material(adlMaterial_shared_ptr material);
	void load_light_color(adlVec3 color);
	void load_color(adlVec3 color);
	void load_view_matrix(const adlMat4& matrix);
	void load_switch(bool yn);
	void load_texture();

protected:
	virtual void bind_attributes();
	virtual void get_all_uniform_locations();

private:
	int32 mvp_matrix_location_;
	int32 light_color_location_;
	int32 model_matrix_location_;
	int32 light_position_location_;
	int32 camera_position_location_;
	int32 view_matrix_location_;
	int32 color_location_;

	int32 text_color_location_;
	int32 projection_matrix_location_;

	int32 ambient_location_;
	int32 diffuse_location_;
	int32 specular_location_;
	int32 shininess_location_;

	int32 light_ambient_location_;
	int32 light_diffuse_location_;
	int32 light_specular_location_;

	int32 texture_location_;
	int32 texture_specular_location_;

	std::vector<int32> point_light_position_locations_;
	std::vector<int32> point_light_ambient_locations_;
	std::vector<int32> point_light_diffuse_locations_;
	std::vector<int32> point_light_specular_locations_;
	std::vector<int32> point_light_constant_locations_;
	std::vector<int32> point_light_linear_locations_;
	std::vector<int32> point_light_quadratic_locations_;
	int32 point_light_count_location_;

	int32 switch_location_;
};

#endif // adl_static_shader_h__