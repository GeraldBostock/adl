#include "adlEntity.h"

#include "adlEntity_factory.h"

adlEntity::adlEntity(adlEntity_id id)
	: id_(id)
{
	name_ = "Entity_" + std::to_string(id_);
	type_name = "adlEntity";
}

adlEntity::~adlEntity()
{
}

void adlEntity::init()
{
}

void adlEntity::update(float dt)
{
	for (Entity_Components::iterator it = components_.begin(); it != components_.end(); ++it)
	{
		it->second->update(dt);
	}
}

adlEntity_id adlEntity::get_id()
{
	return id_;
}

adlEntity_id adlEntity::getId()
{
	return get_id();
}

const std::string& adlEntity::get_name()
{
	return name_;
}

const std::string& adlEntity::getName()
{
	return get_name();
}
void adlEntity::set_name(const std::string& name)
{
	name_ = name;
}

void adlEntity::setName(const std::string & name)
{
	set_name(name);
}

const std::string& adlEntity::get_type_name()
{
	return type_name;
}

const std::string & adlEntity::getTypeName()
{
	return get_type_name();
}

void adlEntity::deserialize(const rapidjson::Value& json_object)
{

}

void adlEntity::add_component(adlEntity_component_shared_ptr component)
{
	components_.insert(std::make_pair(0, component));
}