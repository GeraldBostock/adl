#include "Material_test.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlEntity_factory.h"

Material_test::Material_test()
{
	REGISTER_ACTOR(Material_test)
}


Material_test::~Material_test()
{
}

void Material_test::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->get_model("Cube"));
	//adlMaterial_shared_ptr material = adl_rm->get_material("frame");
	//set_material(material);

	set_position(adlVec3(3.0f, 0.0f, 3.0f));
	set_rotation(adlVec3(0.0f));
	set_scale(adlVec3(1.0f));
}

void Material_test::update(float dt)
{
	adlVec3 rotation = get_rotation();
	rotation.z += adlMath::deg_to_rad(0.1f * dt);
	set_rotation(rotation);
}
