#ifndef adl_point_light_component_h__
#define adl_point_light_component_h__

#include "adlLight_component.h"

class adlPoint_light_component : public adlLight_component
{
public:
	adlPoint_light_component();
	~adlPoint_light_component();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void editor() override;

	float get_constant() const;
	void set_constant(float constant);

	float get_linear() const;
	void set_linear(float linear);

	float get_quadratic() const;
	void set_quadratic(float quadratic);

private:
	float constant_;
	float linear_;
	float quadratic_;
};

#endif //adl_point_light_component_h__