#ifndef adl_entity_component_h__
#define adl_entity_component_h__

#include "../adlShared_types.h"
#include "adlEntity_factory.h"

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
	virtual void update(float dt) {};

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

private:


};

#endif //adl_entity_component_h__