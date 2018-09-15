#include "adlRay.h"

adlRay::adlRay()
{

}

adlRay::adlRay(adlVec3 origin, adlVec3 direction)
	:	origin_(origin),
		direction_(direction)
{
}


adlRay::~adlRay()
{
}

adlVec3 adlRay::get_origin()
{
	return origin_;
}

adlVec3 adlRay::get_direction()
{
	return direction_;
}

void adlRay::set_origin(adlVec3 origin)
{
	origin_ = origin;
}

void adlRay::set_direction(adlVec3 direction)
{
	direction_ = direction;
}