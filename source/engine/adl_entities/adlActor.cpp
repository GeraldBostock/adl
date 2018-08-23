#include "adlActor.h"

#include "engine/adl_resource/adlResource_manager.h"


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

adlVec3 adlActor::getPosition()
{
	return transform_.o;
}

void adlActor::setPosition(adlVec3 position)
{
	transform_.o = position;
}

adlVec3 adlActor::getRotation()
{
	return transform_.rot;
}

void adlActor::setRotation(adlVec3 rotation)
{
	transform_.rot = rotation;
}

adlVec3 adlActor::getScale()
{
	return transform_.scale;
}

void adlActor::setScale(adlVec3 scale)
{
	transform_.scale = scale;
}

adlTransform adlActor::getTransform()
{
	return transform_;
}

void adlActor::setTransform(adlTransform t)
{
	transform_ = t;
}

void adlActor::setTransform(adlVec3 o, adlVec3 rot, adlVec3 scale)
{
	setPosition(o);
	setRotation(rot);
	setScale(scale);
}

adlModel_shared_ptr adlActor::getModel()
{
	return model_;
}

void adlActor::setModel(adlModel_shared_ptr model)
{
	model_ = model;
}

adlColor adlActor::getColor()
{
	return color_;
}

adlMaterial_shared_ptr adlActor::getMaterial()
{
	return material_;
}

void adlActor::setMaterial(adlMaterial_shared_ptr material)
{
	material_ = material;
}
