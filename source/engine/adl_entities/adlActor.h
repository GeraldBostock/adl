#ifndef adl_actor_h__
#define adl_actor_h__

#include "adlEntity.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adl_resource/adlModel.h"

class adlActor : public adlEntity
{
public:
	adlActor();
	~adlActor();

	virtual void init() override;
	virtual void update(float dt) override;

	adlTransform get_transform();
	adlModel_shared_ptr get_model();
	adlColor get_color();

protected:
	adlTransform transform_;
	adlModel_shared_ptr model_;
	adlColor color_;
private:
};

#endif // adl_actor_h__