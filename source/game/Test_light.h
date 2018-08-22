#ifndef test_light_h__
#define test_light_h__

#include "engine/adl_entities/adlLight.h"
#include "engine/adl_helper/adlTimer.h"

class Test_light : public adlLight
{
public:
	Test_light();
	~Test_light();

	void init() override;
	void update(float dt) override;

private:
	adlTimer timer_;
};

#endif // test_light_h__