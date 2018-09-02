#ifndef adl_entity_h__
#define adl_entity_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"

class adlEntity
{
public:
	adlEntity();
	~adlEntity();

	virtual void init();
	virtual void update(float dt);

	unsigned int get_id();
	const std::string& get_name();
	void set_name(const std::string& name);

private:
	static unsigned int current_id;
	unsigned int id_;
	std::string name_;
};

#endif // adl_entity_h__