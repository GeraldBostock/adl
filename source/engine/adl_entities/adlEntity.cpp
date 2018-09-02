#include "adlEntity.h"

#include "adlEntity_factory.h"

unsigned int adlEntity::current_id = 1;

adlEntity::adlEntity()
	: id_(current_id++)
{
	name_ = "Entity_" + std::to_string(id_);
}

adlEntity::~adlEntity()
{

}

void adlEntity::init()
{
}

void adlEntity::update(float dt)
{
}

unsigned int adlEntity::get_id()
{
	return id_;
}

const std::string& adlEntity::get_name()
{
	return name_;
}

void adlEntity::set_name(const std::string& name)
{
	name_ = name;
}