#ifndef adl_transform_component_h__
#define adl_transform_component_h__

#include "adlEntity_component.h"
#include "../adl_math/adlMatrix.h"

class adlTransform_component : public adlEntity_component
{
public:
	adlTransform_component();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override {};
	virtual void update(float dt);
	virtual void destroy() override;
	virtual void editor() override;

	const adlVec3& get_position();
	void set_position(const adlVec3& position);

	const adlVec3& get_rotation();
	void set_rotation(const adlVec3& rotation);

	const adlVec3& get_scale();
	void set_scale(const adlVec3& scale);

	adlTransform get_transform();
	void set_transform(const adlTransform& transform);

private:
	adlTransform transform_;
};

#endif //adl_transform_component_h__