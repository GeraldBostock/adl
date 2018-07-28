#ifndef matrix_h__
#define matrix_h__

#include "engine/adl_math/adlVector.h"
#include "engine/adl_debug/adlAssert.h"

class adlMat3
{
public:
	inline adlMat3();
	inline adlMat3(const adlVec3& s, const adlVec3& f, const adlVec3& u);
	inline adlMat3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33);
	inline adlMat3(const adlMat3& mat);

	/*------------------------Operator overloads--------------------*/
	inline float operator[](unsigned int index);
	inline float operator()(unsigned int i, unsigned int j);

	inline adlMat3 operator+(float scalar) const;
	inline adlMat3 operator-(float scalar) const;
	inline adlMat3 operator*(float scalar) const;
	inline adlMat3 operator/(float scalar) const;

	inline adlMat3 operator+(const adlMat3& matrix) const;
	inline adlMat3 operator-(const adlMat3& matrix) const;
	inline adlMat3 operator*(const adlMat3& matrix) const;

	inline adlVec3 operator*(const adlVec3& vector) const;
	/*--------------------------------------------------------------*/

	static adlMat3 identity();

	union
	{
		struct
		{
			adlVec3 a;
			adlVec3 b;
			adlVec3 c;
		};
		float mat2d[3][4];
		float mat[12];
	};
};

inline adlMat3::adlMat3()
	: a(adlVec3(0.0f)), b(adlVec3(0.0f)), c(adlVec3(0.0f))
{

}

inline adlMat3::adlMat3(const adlVec3& s, const adlVec3& f, const adlVec3& u)
{
	a = s;
	b = f;
	c = u;
}

inline adlMat3::adlMat3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33)
{
	mat2d[0][0] = _11;
	mat2d[0][1] = _12;
	mat2d[0][2] = _13;

	mat2d[1][0] = _21;
	mat2d[1][1] = _22;
	mat2d[1][2] = _23;

	mat2d[2][0] = _31;
	mat2d[2][1] = _32;
	mat2d[2][2] = _33;
}

inline adlMat3::adlMat3(const adlMat3& mat)
{
	a = mat.a;
	b = mat.b;
	c = mat.c;
}

inline float adlMat3::operator[](unsigned int index)
{
	adl_assert((0 <= index) && (index < 12));
	return mat[index];
}

inline float adlMat3::operator()(unsigned int i, unsigned int j)
{
	adl_assert((0 <= i && i < 4) && (0 <= j && j < 4));
	return mat2d[i][j];
}

inline adlMat3 adlMat3::operator+(float scalar) const
{
	return adlMat3(a + scalar, b + scalar, c + scalar);
}

inline adlMat3 adlMat3::operator-(float scalar) const
{
	return adlMat3(a - scalar, b - scalar, c - scalar);
}

inline adlMat3 adlMat3::operator*(float scalar) const
{
	return adlMat3(a * scalar, b * scalar, c * scalar);
}

inline adlMat3 adlMat3::operator/(float scalar) const
{
	adl_assert(scalar != 0.0f);
	return adlMat3(a / scalar, b / scalar, c / scalar);
}

inline adlMat3 adlMat3::operator+(const adlMat3& matrix) const
{
	return adlMat3(a + matrix.a, b + matrix.b, c + matrix.b);
}

inline adlMat3 adlMat3::operator-(const adlMat3& matrix) const
{
	return adlMat3(a - matrix.a, b - matrix.b, c - matrix.c);
}

inline adlMat3 adlMat3::operator*(const adlMat3& matrix) const
{
	adlVec3 a_((a.x * matrix.a.x) + (a.y * matrix.b.x) + (a.z * matrix.c.x), (a.x * matrix.a.y) + (a.y * matrix.b.y) + (a.z * matrix.c.y), (a.x * matrix.a.z) + (a.y * matrix.b.z) + (a.z * matrix.c.z));
	adlVec3 b_((b.x * matrix.a.x) + (b.y * matrix.b.x) + (b.z * matrix.c.x), (b.x * matrix.a.y) + (b.y * matrix.b.y) + (b.z * matrix.c.y), (b.x * matrix.a.z) + (b.y * matrix.b.z) + (b.z * matrix.c.z));
	adlVec3 c_((c.x * matrix.a.x) + (c.y * matrix.b.x) + (c.z * matrix.c.x), (c.x * matrix.a.y) + (c.y * matrix.b.y) + (c.z * matrix.c.y), (c.x * matrix.a.z) + (c.y * matrix.b.z) + (c.z * matrix.c.z));

	return adlMat3(a_, b_, c_);
}

inline adlVec3 adlMat3::operator*(const adlVec3& vector) const
{
	float a_ = (a.x * vector.x) + (a.y * vector.y) + (a.z * vector.z);
	float b_ = (b.x * vector.x) + (b.y * vector.y) + (b.z * vector.z);
	float c_ = (c.x * vector.x) + (c.y * vector.y) + (c.z * vector.z);

	return adlVec3(a_, b_, c_);
}

inline adlMat3 adlMat3::identity()
{
	adlVec3 a_(1, 0, 0);
	adlVec3 b_(0, 1, 0);
	adlVec3 c_(0, 0, 1);

	return adlMat3(a_, b_, c_);
}

class adlMatrix_frame
{
public:
	struct
	{
		adlVec3 o;
		float scale;

		adlMat3 rot_x;
		adlMat3 rot_y;
		adlMat3 rot_z;
	};
};

#endif // matrix_h__