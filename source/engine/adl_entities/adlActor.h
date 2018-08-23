#ifndef adl_actor_h__
#define adl_actor_h__

#include "adlEntity.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlMaterial.h"
#include "engine/adlShared_types.h"

class adlActor : public adlEntity
{
public:
	adlActor();
	~adlActor();

	virtual void init() override;
	virtual void update(float dt) override;

	void set_position(adlVec3 position);
	void set_rotation(adlVec3 rotation);
	void set_scale(adlVec3 scale);

	adlVec3 get_position();
	adlVec3 get_rotation();
	adlVec3 get_scale();

	adlTransform get_transform();
	adlModel_shared_ptr get_model();
	adlColor get_color();
	adlMaterial_shared_ptr get_material();

protected:
	adlModel_shared_ptr model_;
	adlColor color_;

	adlMaterial_shared_ptr material_;

	void set_material(adlMaterial_shared_ptr material);
private:
	adlTransform transform_;
};

#endif // adl_actor_h__