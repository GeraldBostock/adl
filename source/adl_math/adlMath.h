#ifndef adl_math_h__
#define adl_math_h__

#define adl_pi 3.1415926535897932f
#define	adl_two_pi 6.28318530717959f
#define	adl_half_pi 1.57079632679f

#define adl_e 2.71828182845904523536f
#define adl_rad_to_deg_conv 57.2957795130823f
#define adl_deg_to_rad_conv 0.0174532925199433f

//#define deg_to_rad(deg) deg_to_rad(int deg)


#include "vector.h"

namespace adlMath
{
	template<typename a_type>
	static inline a_type min(a_type x, a_type y)
	{
		return (x < y) ? x : y;
	}

	template<typename a_type>
	static inline a_type max(a_type x, a_type y)
	{
		return (x < y) ? y : x;
	}
}

#endif // adl_math_h__