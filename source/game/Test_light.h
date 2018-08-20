#ifndef test_light_h__
#define test_light_h__

#include "engine/adl_renderer/adlLight.h"

class Test_light : public adlLight
{
public:
	Test_light();
	~Test_light();

	void init() override;
	void update(float dt) override;

private:

};

#endif // test_light_h__