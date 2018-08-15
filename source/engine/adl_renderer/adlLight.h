#ifndef adl_light_h__
#define adl_light_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_renderer/adlColor.h"

class adlLight
{
public:
	adlLight(adlModel_shared_ptr model, adlColor color);
	~adlLight();

	adlModel_shared_ptr get_model();
	adlColor get_color();
	adlMatrix_frame get_frame();
	adlShader_shared_ptr get_shader();

	void set_frame(adlMatrix_frame frame);

private:
	adlModel_shared_ptr light_model_;
	adlColor light_color_;
	adlShader_shared_ptr light_shader_;

	adlMatrix_frame frame_;
};

#endif // adl_light_h__