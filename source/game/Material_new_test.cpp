#include "Material_new_test.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlEntity_factory.h"

Material_new_test::Material_new_test()
{
	REGISTER_ACTOR(Material_new_test)
}


Material_new_test::~Material_new_test()
{
}

void Material_new_test::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->getModel("Cube"));
	//adlMaterial_shared_ptr material = adl_rm->getMaterial("red_rubber");
	//setMaterial(material);

	setPosition(adlVec3(0.0f, 0.0f, 5.0f));
	setRotation(adlVec3(0, adlMath::deg_to_rad(90), 0));
	setScale(adlVec3(2.0f));
}

void Material_new_test::update(float dt)
{
}
