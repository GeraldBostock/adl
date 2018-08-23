#include "Material_new_test.h"

#include "engine/adl_resource/adlResource_manager.h"

Material_new_test::Material_new_test()
{
}


Material_new_test::~Material_new_test()
{
}

void Material_new_test::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model("cube");
	adlMaterial_shared_ptr material = adl_rm->get_material("red_plastic");
	set_material(material);

	set_position(adlVec3(0.0f, 0.0f, 5.0f));
	set_rotation(adlVec3(0, adlMath::deg_to_rad(90), 0));
	set_scale(adlVec3(2.0f));
}

void Material_new_test::update(float dt)
{

}
