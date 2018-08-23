#include "adlActor.h"


adlActor::adlActor()
{
	model_ = nullptr;
}


adlActor::~adlActor()
{
}

void adlActor::init()
{
}

void adlActor::update(float dt)
{
}

adlTransform adlActor::get_transform()
{
	return transform_;
}

adlModel_shared_ptr adlActor::get_model()
{
	return model_;
}

adlColor adlActor::get_color()
{
	return color_;
}

adlMaterial_shared_ptr adlActor::get_material()
{
	return material_;
}

void adlActor::set_material(adlMaterial_shared_ptr material)
{
	material_ = material;
}

void adlActor::set_position(adlVec3 position)
{
	transform_.o = position;
}

void adlActor::set_rotation(adlVec3 rotation)
{
	transform_.rot = rotation;
}

void adlActor::set_scale(adlVec3 scale)
{
	transform_.scale = scale;
}

adlVec3 adlActor::get_position()
{
	return transform_.o;
}

adlVec3 adlActor::get_rotation()
{
	return transform_.rot;
}

adlVec3 adlActor::get_scale()
{
	return transform_.scale;
}