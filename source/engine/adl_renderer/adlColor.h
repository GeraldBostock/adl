#ifndef adl_color_h__
#define adl_color_h__

#include "engine/adl_math/adlMath.h"

class adlColor
{
public:
	adlColor();
	adlColor(float r, float g, float b);
	adlColor(float rgb) : r_(rgb), g_(rgb), b_(rgb) {}
	~adlColor();

	inline bool operator<(const adlColor& color) const;
	inline bool operator==(const adlColor& color) const;

	adlVec3 to_vec3();

	static const adlColor WHITE;
	static const adlColor RED;
	static const adlColor GREEN;
	static const adlColor BLUE;
	static const adlColor MAGENTA;
	static const adlColor CYAN;
	static const adlColor YELLOW;
	static const adlColor BLACK;

	float get_r();
	float get_g();
	float get_b();

private:
	float r_;
	float g_;
	float b_;
};

inline bool adlColor::operator<(const adlColor& color) const
{
	if (r_ < color.r_ && g_ < color.g_ && b_ < color.b_)
	{
		return true;
	}

	return false;
}

inline bool adlColor::operator==(const adlColor& color) const
{
	return r_ == color.r_ && g_ == color.g_ && b_ == color.b_;
}

#endif // adl_color_h__