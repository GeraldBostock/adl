#include <string>

#include "adlShader_program.h"

class adlStatic_shader : public adlShader_program
{
public:

	adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file);
	~adlStatic_shader();

	void load_mvp(const adlMat4& mvp_matrix);

protected:
	virtual void bind_attributes();
	virtual void get_all_uniform_locations();

private:
	int32 mvp_matrix_location_;
};