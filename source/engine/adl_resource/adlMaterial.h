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
	void set_names(const std::string& shader_name, const std::string& texture_name);
	void set_shader_name(const std::string& shader_name);
	std::string get_shader_name();
	adlShader_shared_ptr get_shader();

	std::string get_texture_name();
	void set_texture(adlTexture_shared_ptr texture);
	adlTexture_shared_ptr get_texture();

	void set_name(const std::string& name);
	const std::string& get_name();
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

	std::string texture_name_;
	adlTexture_shared_ptr texture_;

	std::string name_ = "";
};

#endif // adl_material_h__