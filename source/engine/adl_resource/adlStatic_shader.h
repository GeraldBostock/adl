#include <string>

#include "adlShader_program.h"

class adlStatic_shader : public adlShader_program
{
public:
	/*typedef adlShader_program super;*/

	adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file);
	~adlStatic_shader();

	void load_transformation(const adlMat4& matrix);
	//void loadProjectionMatrix(glm::mat4 projectionMatrix);
	//void loadViewMatrix(Camera camera);

protected:
	virtual void bind_attributes();
	virtual void get_all_uniform_locations();

private:
	int32 transformation_matrix_location_;
	int32 projection_matrix_location_;
	int32 view_matrix_location_;
};