#ifndef vector_h__
#define vector_h__

#include "common.h"
#include "adl_debug/adlAssert.h"

class adlVec2
{
public:
	inline adlVec2();
	inline adlVec2(float x, float y);
	inline adlVec2(float value);
	inline adlVec2(const adlVec2& v);

	inline static adlVec2 zero();

	/*------------------------Operator overloads--------------------*/
	inline adlVec2 operator+(const adlVec2& vector) const;
	inline adlVec2 operator-(const adlVec2& vector) const;
	inline adlVec2 operator*(const adlVec2& vector) const;
	inline adlVec2 operator/(const adlVec2& vector) const;

	inline adlVec2 operator+(float value) const;
	inline adlVec2 operator-(float value) const;
	inline adlVec2 operator*(float value) const;
	inline adlVec2 operator/(float value) const;

	inline bool operator==(const adlVec2& vector) const;
	inline bool operator!=(const adlVec2& vector) const;

	inline float operator[](unsigned int index) const;
	/*---------------------------------------------------------------*/

	union
	{
		struct
		{
			float x;
			float y;
		};
		float vec[2];
	};
};

inline adlVec2::adlVec2()
	: x(0), y(0)
{
}

inline adlVec2::adlVec2(float x, float y)
	: x(x), y(y)
{
}

inline adlVec2::adlVec2(float value)
	: x(value), y(value)
{
}

inline adlVec2::adlVec2(const adlVec2& v)
	: x(v.x), y(v.y)
{
}

inline adlVec2 adlVec2::zero()
{
	return adlVec2(0.0f);
}

inline adlVec2 adlVec2::operator+(const adlVec2& vector) const
{
	return adlVec2(x + vector.x, y + vector.y);
}

inline adlVec2 adlVec2::operator-(const adlVec2& vector) const
{
	return adlVec2(x - vector.x, y - vector.y);
}

inline adlVec2 adlVec2::operator*(const adlVec2& vector) const
{
	return adlVec2(x * vector.x, y * vector.y);
}

inline adlVec2 adlVec2::operator/(const adlVec2& vector) const
{
	return adlVec2(x / vector.x, y / vector.y);
}

inline adlVec2 adlVec2::operator+(float value) const
{
	return adlVec2(x + value, y + value);
}

inline adlVec2 adlVec2::operator-(float value) const
{
	return adlVec2(x - value, y - value);
}

inline adlVec2 adlVec2::operator*(float value) const
{
	return adlVec2(x * value, y * value);
}

inline adlVec2 adlVec2::operator/(float value) const
{
	return adlVec2(x / value, y / value);
}

inline bool adlVec2::operator==(const adlVec2& vector) const
{
	return (x == vector.x) && (y == vector.y);
}

inline bool adlVec2::operator!=(const adlVec2& vector) const
{
	return (x != vector.x) && (y != vector.y);
}

inline float adlVec2::operator[](unsigned int index) const
{
	adl_assert((index >= 0) && (index < 2));
	return vec[index];
}

class adlVec2_i32
{
public:
	inline adlVec2_i32();
	inline adlVec2_i32(int32 x, int32 y);
	inline adlVec2_i32(int32 value);
	inline adlVec2_i32(const adlVec2_i32& v);

	inline static adlVec2_i32 zero();
	inline adlVec2 to_vec2();

	/*------------------------Operator overloads--------------------*/
	inline adlVec2_i32 operator+(const adlVec2_i32& vector) const;
	inline adlVec2_i32 operator-(const adlVec2_i32& vector) const;
	inline adlVec2_i32 operator*(const adlVec2_i32& vector) const;
	inline adlVec2_i32 operator/(const adlVec2_i32& vector) const;

	inline adlVec2_i32 operator+(int32 value) const;
	inline adlVec2_i32 operator-(int32 value) const;
	inline adlVec2_i32 operator*(int32 value) const;
	inline adlVec2_i32 operator/(int32 value) const;

	inline bool operator==(const adlVec2_i32& vector) const;
	inline bool operator!=(const adlVec2_i32& vector) const;

	inline int32 operator[](unsigned int index) const;
	/*---------------------------------------------------------------*/

	union
	{
		struct
		{
			int32 x;
			int32 y;
		};
		int32 vec[2];
	};
};

inline adlVec2_i32::adlVec2_i32()
	: x(0), y(0)
{
}

inline adlVec2_i32::adlVec2_i32(int32 x, int32 y)
	: x(x), y(y)
{
}

inline adlVec2_i32::adlVec2_i32(int32 value)
	: x(value), y(value)
{
}

inline adlVec2_i32::adlVec2_i32(const adlVec2_i32& v)
	: x(v.x), y(v.y)
{
}

inline adlVec2_i32 adlVec2_i32::zero()
{
	return adlVec2_i32(0);
}

inline adlVec2 adlVec2_i32::to_vec2()
{
	return adlVec2((float)x, (float)y);
}

inline adlVec2_i32 adlVec2_i32::operator+(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x + vector.x, y + vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator-(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x - vector.x, y - vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator*(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x * vector.x, y * vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator/(const adlVec2_i32& vector) const
{
	return adlVec2_i32(x / vector.x, y / vector.y);
}

inline adlVec2_i32 adlVec2_i32::operator+(int32 value) const
{
	return adlVec2_i32(x + value, y + value);
}

inline adlVec2_i32 adlVec2_i32::operator-(int32 value) const
{
	return adlVec2_i32(x - value, y - value);
}

inline adlVec2_i32 adlVec2_i32::operator*(int32 value) const
{
	return adlVec2_i32(x * value, y * value);
}

inline adlVec2_i32 adlVec2_i32::operator/(int32 value) const
{
	return adlVec2_i32(x / value, y / + value);
}

inline bool adlVec2_i32::operator==(const adlVec2_i32& vector) const
{
	return (x == vector.x) && (y == vector.y);
}

inline bool adlVec2_i32::operator!=(const adlVec2_i32& vector) const
{
	return (x != vector.x) && (y != vector.y);
}

inline int32 adlVec2_i32::operator[](unsigned int index) const
{
	adl_assert((index >= 0) && (index < 3));
	return vec[index];
}

class adlVec3
{
public:
	inline adlVec3();
	inline adlVec3(float x, float y, float z);
	inline adlVec3(adlVec2 xy, float z);
	inline adlVec3(float value);
	inline adlVec3(const adlVec3& v);

	inline static adlVec3 zero();

	/*------------------------Operator overloads--------------------*/
	inline adlVec3 operator+(const adlVec3& vector) const;
	inline adlVec3 operator-(const adlVec3& vector) const;
	inline adlVec3 operator*(const adlVec3& vector) const;
	inline adlVec3 operator/(const adlVec3& vector) const;

	inline adlVec3 operator+(float value) const;
	inline adlVec3 operator-(float value) const;
	inline adlVec3 operator*(float value) const;
	inline adlVec3 operator/(float value) const;

	inline bool operator==(const adlVec3& vector) const;
	inline bool operator!=(const adlVec3& vector) const;

	inline float operator[](unsigned int index) const;
	/*---------------------------------------------------------------*/

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float vec[3];
	};
};

inline adlVec3::adlVec3()
	: x(0), y(0), z(0)
{
}

inline adlVec3::adlVec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

inline adlVec3::adlVec3(adlVec2 xy, float z)
	: x(xy.x), y(xy.y), z(z)
{
}

inline adlVec3::adlVec3(float value)
	: x(value), y(value), z(value)
{
}

inline adlVec3::adlVec3(const adlVec3& v)
	: x(v.x), y(v.y), z(v.z)
{
}

inline adlVec3 adlVec3::zero()
{
	return adlVec3(0.0f);
}


inline adlVec3 adlVec3::operator+(const adlVec3& vector) const
{
	return adlVec3(x + vector.x, y + vector.y, z + vector.z);
}

inline adlVec3 adlVec3::operator-(const adlVec3& vector) const
{
	return adlVec3(x - vector.x, y - vector.y, z - vector.z);
}

inline adlVec3 adlVec3::operator*(const adlVec3& vector) const
{
	return adlVec3(x * vector.x, y * vector.y, z * vector.z);
}

inline adlVec3 adlVec3::operator/(const adlVec3& vector) const
{
	return adlVec3(x / vector.x, y / vector.y, z / vector.z);
}

inline adlVec3 adlVec3::operator+(float value) const
{
	return adlVec3(x + value, y + value, z + value);
}

inline adlVec3 adlVec3::operator-(float value) const
{
	return adlVec3(x - value, y - value, z - value);
}

inline adlVec3 adlVec3::operator*(float value) const
{
	return adlVec3(x * value, y * value, z * value);
}

inline adlVec3 adlVec3::operator/(float value) const
{
	return adlVec3(x / value, y / value, z / value);
}

inline bool adlVec3::operator==(const adlVec3& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}

inline bool adlVec3::operator!=(const adlVec3& vector) const
{
	return (x != vector.x) && (y != vector.y) && (z != vector.z);
}

inline float adlVec3::operator[](unsigned int index) const
{
	adl_assert((index >= 0) && (index < 3));
	return vec[index];
}

class adlVec3_i32
{
public:
	inline adlVec3_i32();
	inline adlVec3_i32(int32 x, int32 y, int32 z);
	inline adlVec3_i32(adlVec2_i32 xy, int32 z);
	inline adlVec3_i32(int32 value);
	inline adlVec3_i32(const adlVec3_i32& v);

	inline static adlVec3_i32 zero();
	inline adlVec3 to_vec3();

	/*------------------------Operator overloads--------------------*/
	inline adlVec3_i32 operator+(const adlVec3_i32& vector) const;
	inline adlVec3_i32 operator-(const adlVec3_i32& vector) const;
	inline adlVec3_i32 operator*(const adlVec3_i32& vector) const;
	inline adlVec3_i32 operator/(const adlVec3_i32& vector) const;

	inline adlVec3_i32 operator+(int32 value) const;
	inline adlVec3_i32 operator-(int32 value) const;
	inline adlVec3_i32 operator*(int32 value) const;
	inline adlVec3_i32 operator/(int32 value) const;

	inline bool operator==(const adlVec3_i32& vector) const;
	inline bool operator!=(const adlVec3_i32& vector) const;

	inline int32 operator[](unsigned int index) const;
	/*---------------------------------------------------------------*/

	union
	{
		struct
		{
			int32 x;
			int32 y;
			int32 z;
		};
		int32 vec[3];
	};
};

inline adlVec3_i32::adlVec3_i32()
	: x(0), y(0), z(0)
{
}

inline adlVec3_i32::adlVec3_i32(int32 x, int32 y, int32 z)
	: x(x), y(y), z(z)
{
}

inline adlVec3_i32::adlVec3_i32(adlVec2_i32 xy, int32 z)
	: x(xy.x), y(xy.y), z(z)
{
}

inline adlVec3_i32::adlVec3_i32(int32 value)
	: x(value), y(value), z(value)
{
}

inline adlVec3_i32::adlVec3_i32(const adlVec3_i32& v)
	: x(v.x), y(v.y), z(v.z)
{
}

inline adlVec3_i32 adlVec3_i32::zero()
{
	return adlVec3_i32(0);
}

inline adlVec3 adlVec3_i32::to_vec3()
{
	return adlVec3((float)x, (float)y, (float)z);
}

inline adlVec3_i32 adlVec3_i32::operator+(const adlVec3_i32& vector) const
{
	return adlVec3_i32(x + vector.x, y + vector.y, z + vector.z);
}

inline adlVec3_i32 adlVec3_i32::operator-(const adlVec3_i32& vector) const
{
	return adlVec3_i32(x - vector.x, y - vector.y, z - vector.z);
}

inline adlVec3_i32 adlVec3_i32::operator*(const adlVec3_i32& vector) const
{
	return adlVec3_i32(x * vector.x, y * vector.y, z * vector.z);
}

inline adlVec3_i32 adlVec3_i32::operator/(const adlVec3_i32& vector) const
{
	return adlVec3_i32(x / vector.x, y / vector.y, z / vector.z);
}

inline adlVec3_i32 adlVec3_i32::operator+(int32 value) const
{
	return adlVec3_i32(x + value, y + value, z + value);
}

inline adlVec3_i32 adlVec3_i32::operator-(int32 value) const
{
	return adlVec3_i32(x - value, y - value, z - value);
}

inline adlVec3_i32 adlVec3_i32::operator*(int32 value) const
{
	return adlVec3_i32(x * value, y * value, z * value);
}

inline adlVec3_i32 adlVec3_i32::operator/(int32 value) const
{
	return adlVec3_i32(x / value, y / value, z / value);
}

inline bool adlVec3_i32::operator==(const adlVec3_i32& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}

inline bool adlVec3_i32::operator!=(const adlVec3_i32& vector) const
{
	return (x != vector.x) && (y != vector.y) && (z != vector.z);
}

inline int32 adlVec3_i32::operator[](unsigned int index) const
{
	adl_assert((index >= 0) && (index < 3));
	return vec[index];
}
#endif // vector_h__