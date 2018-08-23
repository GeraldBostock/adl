#include "Material_test.h"

#include "engine/adl_resource/adlResource_manager.h"

Material_test::Material_test()
{
}


Material_test::~Material_test()
{
}

void Material_test::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model("cube");
	adlMaterial_shared_ptr material = adl_rm->get_material("wood");
	setMaterial(material);

	transform_.o = adlVec3(3.0f, 0.0f, 0.0f);
	transform_.rot = adlVec3(0.0f);
	transform_.scale = adlVec3(1.0f);
}

void Material_test::update(float dt)
{

}
