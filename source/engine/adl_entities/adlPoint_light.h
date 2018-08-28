#ifndef adl_point_light_h__
#define adl_point_light_h__

#include "adlLight.h"

class adlPoint_light : public adlLight
{
public:
	adlPoint_light();
	~adlPoint_light();

	virtual void init() override;
	virtual void update(float dt) override;

	void set_constant(float constant);
	float get_constant();

	void set_linear(float linear);
	float get_linear();

	void set_quadratic(float quadratic);
	float get_quadratic();

private:
	float constant_;
	float linear_;
	float quadratic_;

};

#endif // adl_point_light_h__