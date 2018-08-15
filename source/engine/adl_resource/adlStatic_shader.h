#include <string>

#include "adlShader_program.h"
#include "engine/adl_renderer/adlColor.h"

class adlStatic_shader : public adlShader_program
{
public:

	adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file);
	~adlStatic_shader();

	void load_mvp(const adlMat4& mvp_matrix);
	void load_object_color(adlVec3 color);
	void load_light_color(adlVec3 color);
	void load_model_matrix(const adlMat4& model_matrix);
	void load_light_position(adlVec3 position);

protected:
	virtual void bind_attributes();
	virtual void get_all_uniform_locations();

private:
	int32 mvp_matrix_location_;
	int32 object_color_location_;
	int32 light_color_location_;
	int32 model_matrix_location_;
	int32 light_position_location_;
};