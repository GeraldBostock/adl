#include "adlColor.h"

const adlColor adlColor::WHITE(255, 255, 255);
const adlColor adlColor::RED(255, 0, 0);
const adlColor adlColor::GREEN(0, 255, 0);
const adlColor adlColor::BLUE(0, 0, 255);
const adlColor adlColor::MAGENTA(255, 0, 255);
const adlColor adlColor::CYAN(0, 255, 255);
const adlColor adlColor::YELLOW(255, 255, 0);
const adlColor adlColor::BLACK(0, 0, 0);

adlColor::adlColor()
{
	r_ = 1.0f;
	g_ = 1.0f;
	b_ = 1.0f;
}

adlColor::adlColor(float r, float g, float b)
{
	r_ = r;
	g_ = g;
	b_ = b;
}

adlColor::~adlColor()
{

}

adlVec3 adlColor::to_vec3()
{
	adlVec3 vec(r_ / (float)255, g_ / (float)255, b_ / (float)255);
	return vec;
}

float adlColor::get_r()
{
	return r_;
}

float adlColor::get_g()
{
	return g_;
}

float adlColor::get_b()
{
	return b_;
}