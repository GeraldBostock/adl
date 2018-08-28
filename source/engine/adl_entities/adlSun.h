#ifndef adl_sun_h__
#define adl_sun_h__

#include "adlLight.h"

class adlSun : public adlLight
{
public:
	adlSun();
	~adlSun();

	void init() override;
	void update(float dt) override;

private:

};

#endif // adl_sun_h__