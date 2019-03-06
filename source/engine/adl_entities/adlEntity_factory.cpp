#include "adlEntity_factory.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlEntity.h"

#include <document.h>

adlEntity_id adlEntity_factory::next_id = 1;

adlEntity_factory::adlEntity_factory()
{
}

const std::vector<std::string>& adlEntity_factory::get_all_registered_entities() const
{
	return registered_components_;
}

const std::vector<std::string>& adlEntity_factory::get_all_registered_lights() const
{
	return registered_lights_;
}


adlEntity_shared_ptr adlEntity_factory::construct_entity(const std::string& entity_name)
{
	adlLogger* logger = &adlLogger::get();
	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlEntity_shared_ptr entity = MAKE_SHARED(adlEntity, next_id++);

	const std::string& entity_json = adl_rm->get_entity_json(entity_name);
	if (entity_json == "")
	{
		logger->log_error("JSON resource for entity " + entity_name + " not found");
	}
	else
	{
		rapidjson::Document document;
		document.Parse(entity_json.c_str());
		adl_assert(document.IsObject());

		if (!document.IsObject())
		{
			logger->log_error("JSON resource file for entity " + entity_name + " is faulty");
			return nullptr;
		}

		entity->set_name(document["type"].GetString());

		const rapidjson::Value& components = document["components"];
		adl_assert(components.IsArray());

		for (rapidjson::Value::ConstValueIterator it = components.Begin(); it != components.End(); ++it)
		{
			const rapidjson::Value& component_object = *it;

			adlEntity_component* component = (adlEntity_component*)construct_component(component_object["type"].GetString());
			if (component != nullptr)
			{
				component->init(component_object);
				entity->add_component(adlEntity_component_shared_ptr(component));
				component->set_owner(entity);
				component->post_init();
			}
		}	
	}

	return entity;
}

void adlEntity_factory::add_component_to_entity(adlEntity_shared_ptr entity, const std::string& component_name)
{
	adlEntity_component* component = (adlEntity_component*)construct_component(component_name);
	if (component != nullptr)
	{
		entity->add_component(adlEntity_component_shared_ptr(component));
		component->set_owner(entity);
		component->post_init();
	}
}

void* adlEntity_factory::construct_component(const std::string& component_name)
{
	adlLogger* logger = &adlLogger::get();

	map_type::iterator it = components_.find(component_name);
	if (it == components_.end())
	{
		logger->log_error("Component " + component_name + " is not registered");
		return nullptr;
	}

	return it->second();
}

void* adlEntity_factory::construct_light(const std::string& class_name)
{
	adlLogger* logger = &adlLogger::get();

	map_type::iterator i = lights_.find(class_name);
	if (i == lights_.end())
	{
		logger->log_error("Light " + class_name + " is not registered.");
		return nullptr;
	}

	return i->second();
}