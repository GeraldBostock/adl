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
	adlMaterial_shared_ptr material = adl_rm->get_material("frame");
	setMaterial(material);

	setPosition(adlVec3(3.0f, 0.0f, 3.0f));
	setRotation(adlVec3(0.0f));
	setScale(adlVec3(1.0f));
}

void Material_test::update(float dt)
{

}
