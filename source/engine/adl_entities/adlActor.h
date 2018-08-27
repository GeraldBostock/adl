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

	void setPosition(adlVec3 position);
	void set_position(adlVec3 position);

	void setRotation(adlVec3 rotation);
	void set_rotation(adlVec3 rotation);

	void setScale(adlVec3 scale);
	void set_scale(adlVec3 scale);

	adlVec3 getPosition();
	adlVec3 get_position();

	adlVec3 getRotation();
	adlVec3 get_rotation();

	adlVec3 getScale();
	adlVec3 get_scale();

	adlTransform get_transform();

	adlModel_shared_ptr getModel();
	adlModel_shared_ptr get_model();

	adlColor getColor();
	adlColor get_color();

	adlMaterial_shared_ptr getMaterial();
	adlMaterial_shared_ptr get_material();

protected:
	adlModel_shared_ptr model_ = nullptr;
	adlColor color_;

	adlMaterial_shared_ptr material_;

	void setMaterial(adlMaterial_shared_ptr material);
	void set_material(adlMaterial_shared_ptr material);
private:
	adlTransform transform_;
};

#endif // adl_actor_h__