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