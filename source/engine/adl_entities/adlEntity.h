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

	/*adlMatrix_frame get_frame();
	void set_frame(adlMatrix_frame frame);

	void set_model(adlModel_shared_ptr model);
	adlModel_shared_ptr get_model();*/

private:
	/*adlModel_shared_ptr model_;
	adlMatrix_frame frame_;*/
};

#endif // adl_entity_h__