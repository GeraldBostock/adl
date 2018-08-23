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
	transform_.o = o;
	transform_.rot = rot;
	transform_.scale = scale;
}


adlModel_shared_ptr adlActor::getModel()
{
	return model_;
}

void adlActor::setModel(const std::string& model_name)
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	model_ = adl_rm->get_model(model_name);
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