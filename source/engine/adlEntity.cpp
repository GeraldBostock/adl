#include "adlEntity.h"

adlEntity::adlEntity()
{

}

adlEntity::~adlEntity()
{

}

adlMatrix_frame adlEntity::get_frame()
{
	return frame_;
}

void adlEntity::set_frame(adlMatrix_frame frame)
{
	frame_.o = frame.o;
	frame_.rot = frame.rot;
	frame_.scale = frame.scale;
}

adlModel_shared_ptr adlEntity::get_model()
{
	return model_;
}

void adlEntity::set_model(adlModel_shared_ptr model)
{
	model_ = model;
}
