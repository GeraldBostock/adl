#include "Cube_actor.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlInput.h"

Cube_actor::Cube_actor()
{
	REGISTER_ACTOR(Cube_actor)
}

Cube_actor::~Cube_actor()
{

}

void Cube_actor::init()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->get_model("Cube"));
}

void Cube_actor::update(float dt)
{
	adlInput* input = &adlInput::get();
	
	adlVec3 position = get_position();
	adlVec3 rotation = get_rotation();
	if (input->get_key(adl_key_up))
	{
		position.z -= 0.02f * dt;
	}
	if (input->get_key(adl_key_down))
	{
		position.z += 0.02f * dt;
	}
	if (input->get_key(adl_key_left))
	{
		position.x -= 0.02f * dt;
	}
	if (input->get_key(adl_key_right))
	{
		position.x += 0.02f * dt;
	}
	if (input->get_key(adl_key_r))
	{
		rotation.y += adlMath::deg_to_rad(0.2f) * dt;
	}
	set_position(position);
	set_rotation(rotation);
}