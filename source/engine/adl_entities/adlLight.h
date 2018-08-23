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

	adlShader_shared_ptr getShader();
	adlShader_shared_ptr get_shader();

	adlVec3 getAmbient();
	adlVec3 get_ambient();

	adlVec3 getDiffuse();
	adlVec3 get_diffuse();

	adlVec3 getSpecular();
	adlVec3 get_specular();

private:
	adlShader_shared_ptr light_shader_;

	struct Light_components
	{
		adlVec3 ambient;
		adlVec3 diffuse;
		adlVec3 specular;
	} light_components_;
};

#endif // adl_light_h__