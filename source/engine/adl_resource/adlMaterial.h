#ifndef adl_material_h__
#define adl_material_h__

#include "engine/adl_math/adlVector.h"
#include "engine/adlShared_types.h"

#include <string>

class adlMaterial
{
public:
	adlMaterial();
	~adlMaterial();

	void set_material(adlVec3 ambient, adlVec3 diffuse, adlVec3 specular, float shininess);

	adlVec3 get_ambient();
	adlVec3 get_diffuse();
	adlVec3 get_specular();
	float get_shininess();

	void set_shader(adlShader_shared_ptr shader);
	void set_shader_name(const std::string& shader_name);
	std::string get_shader_name();
	adlShader_shared_ptr get_shader();
private:

	struct Material
	{
		adlVec3 ambient;
		adlVec3 diffuse;
		adlVec3 specular;
		float shininess;
	} material_;

	std::string shader_name_;
	adlShader_shared_ptr shader_;
};

#endif // adl_material_h__