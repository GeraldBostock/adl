#ifndef adl_entity_component_h__
#define adl_entity_component_h__

#include "../adlShared_types.h"
#include "adlEntity_factory.h"
#include "engine/adl_debug/imgui/imgui.h"

#include <string>
#include <document.h>

class adlEntity_component
{
public:
	adlEntity_component() {}
	virtual ~adlEntity_component() 
	{ 
		owner.reset();
	}

	virtual bool init(const rapidjson::Value& json_object) = 0;
	virtual void post_init() = 0;
	virtual void update(float dt) {}
	virtual void destroy() = 0;
	virtual void editor() {}

	const std::string& get_engine_component_name()
	{
		return engine_component_name;
	}

	void set_owner(adlEntity_shared_ptr entity) 
	{ 
		owner = entity;
	}

	const std::string& get_type_name()
	{
		return type_name;
	}

protected:
	adlEntity_shared_ptr owner;
	std::string type_name;

	std::string engine_component_name;

private:


};

#endif //adl_entity_component_h__