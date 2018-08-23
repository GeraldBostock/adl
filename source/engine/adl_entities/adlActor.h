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

	adlTransform getTransform();
	void setTransform(adlTransform t);
	void setTransform(adlVec3 o, adlVec3 rot, adlVec3 scale);

	adlModel_shared_ptr getModel();
	void setModel(const std::string& model_name);

	adlColor getColor();

	adlMaterial_shared_ptr getMaterial();
	void setMaterial(adlMaterial_shared_ptr material);

protected:
	adlTransform transform_;
	adlModel_shared_ptr model_;
	adlColor color_;

	adlMaterial_shared_ptr material_;

private:
};

#endif // adl_actor_h__