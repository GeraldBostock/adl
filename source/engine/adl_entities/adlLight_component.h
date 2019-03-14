#ifndef adl_light_component_h__
#define adl_light_component_h__

#include "adlEntity_component.h"
#include "../adl_math/adlVector.h"
#include "engine/adl_renderer/adlColor.h"

class adlLight_component : public adlEntity_component
{
public:
	adlLight_component();
	~adlLight_component();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override {};
	virtual void update(float dt) override {};
	virtual void destroy() override {};

	void set_ambient(const adlVec3& ambient);
	const adlVec3& get_ambient();

	void set_diffuse(const adlVec3& diffuse);
	const adlVec3& get_diffuse();

	void set_specular(const adlVec3& specular);
	const adlVec3& get_specular();

	void set_color(const adlColor& color);
	adlColor get_color();

	const adlShader_shared_ptr get_shader();


protected:
	void set_shader(const adlShader_shared_ptr shader);

	adlColor color_;
	struct Light_components
	{
		adlVec3 ambient;
		adlVec3 diffuse;
		adlVec3 specular;
	} light_components_;

private:
	adlShader_shared_ptr light_shader_;
};

#endif //adl_light_component_h__