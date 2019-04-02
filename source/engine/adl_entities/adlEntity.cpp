#include "adlEntity.h"

#include "adlEntity_factory.h"
#include "../adl_debug/adlLogger.h"

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
	for (auto component : components_)
	{
		component->update(dt);
	}
}

void adlEntity::destroy()
{
	components_.clear();
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
	components_.push_back(component);
}

void adlEntity::remove_component(const std::string& component_name)
{
	adlLogger* logger = &adlLogger::get();

	for (unsigned int i = 0; i < components_.size(); i++)
	{
		adlEntity_component_shared_ptr component = components_[i];
		std::string component_type = component->get_type_name();

		if (component_name == component_type)
		{
			logger->log_info("Removing " + component_name + " from " + name_);
			component->destroy();
			components_.erase(components_.begin() + i);

			return;
		}
	}
	logger->log_error("Can not remove " + component_name + " from " + name_);
}

bool adlEntity::has_component(const std::string& component_name)
{
	for (auto component : components_)
	{
		if (component_name == component->get_type_name())
		{
			return true;
		}

		if (component_name == component->get_engine_component_name())
		{
			return true;
		}
	}

	return false;
}