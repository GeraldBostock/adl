#ifndef adl_math_h__
#define adl_math_h__

#define adl_pi 3.1415926535897932f
#define	adl_two_pi 6.28318530717959f
#define	adl_half_pi 1.57079632679f

#define adl_e 2.71828182845904523536f
#define adl_rad_to_deg_conv 57.2957795130823f
#define adl_deg_to_rad_conv 0.0174532925199433f

#define adl_epsilon 0.01f
#define adl_fine_epsilon 0.0001f

//#define deg_to_rad(deg) deg_to_rad(int deg)


#include "adlVector.h"
#include "adlMatrix.h"

namespace adlMath
{
	template<typename a_type>
	static inline a_type min2(a_type x, a_type y)
	{
		return (x < y) ? x : y;
	}

	template<typename a_type>
	static inline a_type max2(a_type x, a_type y)
	{
		return (x < y) ? y : x;
	}

	template<typename a_type>
	static inline a_type min3(a_type x, a_type y, a_type z)
	{
		return (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z);
	}

	template<typename a_type>
	static inline a_type max3(a_type x, a_type y, a_type z)
	{
		return (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);
	}

	static inline float dotp(const adlVec3& v1, const adlVec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static inline float dotp(const adlVec2& v1, const adlVec2& v2)
	{
		return v1.x * v2.x + v1.y + v2.y;
	}

	static inline adlVec3 crossp(const adlVec3& v1, const adlVec3& v2)
	{
		adlVec3 result_vector;
		result_vector.x = v1.y * v2.z - v1.z * v2.y;
		result_vector.y = v1.z * v2.x - v1.x * v2.y;
		result_vector.z = v1.x * v2.y - v1.y * v2.x;

		return result_vector;
	}

	static inline adlVec3 normalize(adlVec3 v)
	{
		adlVec3 normalized_vector;
		float length = v.length();

		normalized_vector.x = v.x / length;
		normalized_vector.y = v.y / length;
		normalized_vector.z = v.z / length;

		return normalized_vector;
	}

	static inline float deg_to_rad(float degree)
	{
		return degree * adl_deg_to_rad_conv;
	}

	static inline int rad_to_deg(float radians)
	{
		return radians * adl_rad_to_deg_conv;
	}
}

#endif // adl_math_h__