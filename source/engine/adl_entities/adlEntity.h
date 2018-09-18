#ifndef adl_entity_h__
#define adl_entity_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"

#include <document.h>

class adlEntity
{
public:
	adlEntity();
	~adlEntity();

	virtual void init();
	virtual void update(float dt);

	unsigned int get_id();
	unsigned int getId();

	const std::string& get_name();
	const std::string& getName();

	void set_name(const std::string& name);
	void setName(const std::string& name);

	const std::string& get_type_name();
	const std::string& getTypeName();

	virtual void deserialize(const rapidjson::Value& json_object);

protected:
	std::string type_name;

private:
	static unsigned int current_id;
	unsigned int id_;
	std::string name_;
};

#endif // adl_entity_h__