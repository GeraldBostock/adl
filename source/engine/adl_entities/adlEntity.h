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


private:
};

#endif // adl_entity_h__