#include "adlPhysics.h"

#include "adlMemory.h"

adlPhysics_world* adlPhysics::create_new_world()
{
	adlPhysics_world* new_world = ADL_NEW(adlPhysics_world);
	return new_world;
}