#ifndef adl_light_h__
#define adl_light_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adl_entities/adlActor.h"

class adlLight : public adlActor
{
public:
	adlLight();
	~adlLight();

	virtual void init() override;
	virtual void update(float dt) override;

	adlShader_shared_ptr get_shader();

private:
	adlShader_shared_ptr light_shader_;
};

#endif // adl_light_h__