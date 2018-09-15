#ifndef adl_ray_h__
#define adl_ray_h__

#include "adlVector.h"

class adlRay
{
public:
	adlRay();
	adlRay(adlVec3 origin, adlVec3 direction);
	~adlRay();

	void set_origin(adlVec3 origin);
	adlVec3 get_origin();

	void set_direction(adlVec3 direction);
	adlVec3 get_direction();
private:
	adlVec3 origin_;
	adlVec3 direction_;
};

#endif // adl_ray_h__