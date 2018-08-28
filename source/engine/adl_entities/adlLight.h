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

	virtual void init() = 0;
	virtual void update(float dt) = 0;

	adlShader_shared_ptr getShader();
	adlShader_shared_ptr get_shader();

	void setAmbient(adlVec3 ambient);
	void set_ambient(adlVec3 ambient);

	void setDiffuse(adlVec3 diffuse);
	void set_diffuse(adlVec3 diffuse);

	void setSpecular(adlVec3 specular);
	void set_specular(adlVec3 specular);

	adlVec3 getAmbient();
	adlVec3 get_ambient();

	adlVec3 getDiffuse();
	adlVec3 get_diffuse();

	adlVec3 getSpecular();
	adlVec3 get_specular();

protected:
	void setShader(adlShader_shared_ptr shader);
	void set_shader(adlShader_shared_ptr shader);

	struct Light_components
	{
		adlVec3 ambient;
		adlVec3 diffuse;
		adlVec3 specular;
	} light_components_;

private:
	adlShader_shared_ptr light_shader_;
};

#endif // adl_light_h__