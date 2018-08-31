#include "adlSun.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "adlEntity_factory.h"


adlSun::adlSun()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlModel_shared_ptr sphere = adl_rm->get_model("sphere");
	set_model(sphere);
	color_ = adlColor(255, 165, 0);

	adlShader_shared_ptr shader = adl_rm->get_shader("light_shader");
	set_shader(shader);

	set_ambient(adlVec3(0.1f));
	set_diffuse(adlVec3(0.8f));
	set_specular(adlVec3(1.0f));

	set_position(adlVec3(0, 5, 4));
	set_rotation(adlVec3(0));
	set_scale(adlVec3(0.02f));
}


adlSun::~adlSun()
{
}

void adlSun::init()
{

}

void adlSun::update(float dt)
{

}
