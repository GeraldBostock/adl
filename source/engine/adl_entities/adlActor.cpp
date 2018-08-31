#include "adlActor.h"

#include "adlEntity_factory.h"

adlActor::adlActor()
{
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

void adlActor::set_transform(adlTransform transform)
{
	transform_.o = transform.o;
	transform_.rot = transform.rot;
	transform_.scale = transform.scale;
}

adlModel_shared_ptr adlActor::get_model() const
{
	return model_;
}

adlColor adlActor::get_color() const
{
	return color_;
}

adlMaterial_shared_ptr adlActor::get_material() const
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

adlVec3 adlActor::get_position() const
{
	return transform_.o;
}

adlVec3 adlActor::get_rotation() const
{
	return transform_.rot;
}

adlVec3 adlActor::get_scale() const
{
	return transform_.scale;
}

adlVec3 adlActor::getPosition()
{
	return get_position();
}

adlVec3 adlActor::getRotation()
{
	return get_rotation();
}

adlVec3 adlActor::getScale()
{
	return get_scale();
}

adlModel_shared_ptr adlActor::getModel()
{
	return get_model();
}

adlMaterial_shared_ptr adlActor::getMaterial()
{
	return get_material();
}

void adlActor::setMaterial(adlMaterial_shared_ptr material)
{
	set_material(material);
}

void adlActor::setScale(adlVec3 scale)
{
	set_scale(scale);
}

void adlActor::setPosition(adlVec3 position)
{
	set_position(position);
}

void adlActor::setRotation(adlVec3 rotation)
{
	set_rotation(rotation);
}

adlColor adlActor::getColor()
{
	return get_color();
}

void adlActor::setModel(adlModel_shared_ptr model)
{
	set_model(model);
}

void adlActor::set_model(adlModel_shared_ptr model)
{
	model_ = model;
}