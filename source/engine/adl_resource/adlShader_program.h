#ifndef adl_shader_h__
#define adl_shader_h__

#include "engine/common.h"
#include "engine/adl_math/adlMath.h"

#include <GL/glew.h>
#include <string>

class adlShader_program
{
public:
	adlShader_program();
	~adlShader_program();

	void init(const std::string& vertex_file_path, const std::string& fragment_file_path);
	void start();
	void stop();
	void clean_up();

protected:
	virtual void bind_attributes() = 0;
	virtual void get_all_uniform_locations() = 0;

	int32 get_uniform_location(const std::string& uniform_name);
	void bind_attribute(int attribute, const std::string& variable_name);
	uint32 load_shader(const std::string& shader_path, int32 shader_type);
	void check_shader_error(uint32 shader, uint32 flag, bool is_program, const std::string& error_message);

	void load_vector(int32 location, adlVec3 vector);
	void load_matrix(int32 location, const adlMat4& matrix);
	void load_float(int32 location, float value);

private:
	uint32 program_id_;
	uint32 vertex_shader_id_;
	uint32 fragment_shader_id_;
};

#endif // adl_shader_h__