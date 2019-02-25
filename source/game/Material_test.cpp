#include "Material_test.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlEntity_factory.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       

Material_test::Material_test()
{
	REGISTER_ACTOR(Material_test)
	srand(time(NULL));
}


Material_test::~Material_test()
{
}

void Material_test::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->get_model("Sphere"));
	setMaterial(adl_rm->get_material("copper"));

	set_position(adlVec3(3.0f, 0.0f, 3.0f));
	set_rotation(adlVec3(0.0f));
	set_scale(adlVec3(0.5f));
}

void Material_test::update(float dt)
{

}
