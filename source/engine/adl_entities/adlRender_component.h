#ifndef adl_render_component_h__
#define adl_render_component_h__

#include "adlEntity_component.h"
#include "engine/adlShared_types.h"

class adlRender_component : public adlEntity_component
{
public:
	adlRender_component();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override {};
	virtual void destroy() override;
	virtual void editor() override;

	adlModel_shared_ptr get_model();
	adlMaterial_shared_ptr get_material();

	void set_material(adlMaterial_shared_ptr material)
	{
		material_ = material;
	}

private:
	adlModel_shared_ptr model_;
	adlMaterial_shared_ptr material_;
};

#endif //adl_render_component_h__