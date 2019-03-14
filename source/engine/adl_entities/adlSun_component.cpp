#include "adlSun_component.h"

adlSun_component::adlSun_component()
{
	REGISTER_COMPONENT(adlSun_component)

	light_components_.ambient = adlVec3(0.1f);
	light_components_.diffuse = adlVec3(0.8f);
	light_components_.specular = adlVec3(1.0f);
}

adlSun_component::~adlSun_component()
{

}