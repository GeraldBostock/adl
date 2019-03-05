#ifndef adl_render_component_h__
#define adl_render_component_h__

#include "adlEntity_component.h"
#include "engine/adlShared_types.h"

class adlRender_component : public adlEntity_component
{
public:
	adlRender_component();

	virtual bool init(const rapidjson::Value& json_object);

	adlModel_shared_ptr get_model();
	adlMaterial_shared_ptr get_material();

private:
	adlModel_shared_ptr model_;
	adlMaterial_shared_ptr material_;
};

#endif //adl_render_component_h__