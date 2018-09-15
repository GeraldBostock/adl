#ifndef matrix_h__
#define matrix_h__

#include "engine/adl_math/adlVector.h"
#include "engine/adl_debug/adlAssert.h"

#include <cmath>
#include <iostream>

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
	adlMat3 operator*(const adlMat3& matrix) const;

	adlVec3 operator*(const adlVec3& vector) const;

	inline void operator=(const adlMat3& matrix);
	/*--------------------------------------------------------------*/

	inline static adlMat3 identity();

	adlMat3 get_x_rotation_matrix(float radians);
	adlMat3 get_y_rotation_matrix(float radians);
	adlMat3 get_z_rotation_matrix(float radians);

	/*
	* Matrix Convention
	* Column major
	*
	* | a.x  b.x  c.x |
	* | a.y  b.y  c.y |
	* | a.z  b.z  c.z |
	*
	*/

	union
	{
		struct
		{
			adlVec3 a;
			adlVec3 b;
			adlVec3 c;
		} vectors;
		float mat2d[3][4];
		float mat[12];
	};

private:
};

inline adlMat3::adlMat3()
{
	vectors.a = adlVec3(0.0f);
	vectors.b = adlVec3(0.0f);
	vectors.c = adlVec3(0.0f);
}

inline adlMat3::adlMat3(const adlVec3& s, const adlVec3& f, const adlVec3& u)
{
	vectors.a = s;
	vectors.b = f;
	vectors.c = u;
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
	vectors.a = mat.vectors.a;
	vectors.b = mat.vectors.b;
	vectors.c = mat.vectors.c;
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
	return adlMat3(vectors.a + scalar, vectors.b + scalar, vectors.c + scalar);
}

inline adlMat3 adlMat3::operator-(float scalar) const
{
	return adlMat3(vectors.a - scalar, vectors.b - scalar, vectors.c - scalar);
}

inline adlMat3 adlMat3::operator*(float scalar) const
{
	return adlMat3(vectors.a * scalar, vectors.b * scalar, vectors.c * scalar);
}

inline adlMat3 adlMat3::operator/(float scalar) const
{
	adl_assert(scalar != 0.0f);
	return adlMat3(vectors.a / scalar, vectors.b / scalar, vectors.c / scalar);
}

inline adlMat3 adlMat3::operator+(const adlMat3& matrix) const
{
	return adlMat3(vectors.a + matrix.vectors.a, vectors.b + matrix.vectors.b, vectors.c + matrix.vectors.b);
}

inline adlMat3 adlMat3::operator-(const adlMat3& matrix) const
{
	return adlMat3(vectors.a - matrix.vectors.a, vectors.b - matrix.vectors.b, vectors.c - matrix.vectors.c);
}

inline adlMat3 adlMat3::identity()
{
	adlVec3 a_(1, 0, 0);
	adlVec3 b_(0, 1, 0);
	adlVec3 c_(0, 0, 1);

	return adlMat3(a_, b_, c_);
}

inline void adlMat3::operator=(const adlMat3& matrix)
{
	vectors.a = matrix.vectors.a;
	vectors.b = matrix.vectors.b;
	vectors.c = matrix.vectors.c;
}

class adlMat4
{
public:

	inline adlMat4();
	inline adlMat4(adlVec4 v1, adlVec4 v2, adlVec4 v3, adlVec4 v4);
	inline adlMat4(float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);
	inline adlMat4(float value);
	inline adlMat4(const adlMat4& matrix);
	inline adlMat4(const adlMat3& matrix);

	/*------------------------Operator overloads--------------------*/
	inline float operator[](unsigned int index);
	inline float operator()(unsigned int i, unsigned int j);

	inline adlMat4 operator+(float scalar) const;
	inline adlMat4 operator-(float scalar) const;
	inline adlMat4 operator*(float scalar) const;
	inline adlMat4 operator/(float scalar) const;

	inline adlMat4 operator+(const adlMat4& matrix) const;
	inline adlMat4 operator-(const adlMat4& matrix) const;
	adlMat4 operator*(const adlMat4& matrix) const;

	adlVec4 operator*(const adlVec4& vector) const;

	inline void operator=(const adlMat4& matrix);
	/*--------------------------------------------------------------*/

	inline static adlMat4 identity();
	adlMat4 create_projection_matrix(int window_width, int window_height, float fov_in_radians, float near_plane, float far_plane);
	adlMat4 create_view_matrix(adlVec3 position, adlVec3 rotation);

	adlVec3 transform_to_parent(const adlVec3& vector);
	adlVec3 transform_to_local(const adlVec3& vector);

	/*
	* Matrix Convention
	* Column major
	*
	* | a.x  b.x  c.x  d.x |
	* | a.y  b.y  c.y  d.y |
	* | a.z  b.z  c.z  d.z |
	* | a.w  b.w  c.w  d.w |
	*
	*/

	union
	{
		struct
		{
			adlVec4 a;
			adlVec4 b;
			adlVec4 c;
			adlVec4 d;
		} vectors;
		float mat[16];
		float mat2d[4][4];
	};
};

inline adlMat4::adlMat4()
{
	vectors.a = adlVec4(0.0f);
	vectors.b = adlVec4(0.0f);
	vectors.c = adlVec4(0.0f);
	vectors.d = adlVec4(0.0f);
}

inline adlMat4::adlMat4(adlVec4 v1, adlVec4 v2, adlVec4 v3, adlVec4 v4)
{
	vectors.a = v1;
	vectors.b = v2;
	vectors.c = v3;
	vectors.d = v4;
}

inline adlMat4::adlMat4(float _11, float _12, float _13, float _14,
						float _21, float _22, float _23, float _24,
						float _31, float _32, float _33, float _34,
						float _41, float _42, float _43, float _44)
{
	vectors.a = adlVec4(_11, _12, _13, _14);
	vectors.b = adlVec4(_21, _22, _23, _24);
	vectors.c = adlVec4(_31, _32, _33, _34);
	vectors.d = adlVec4(_41, _42, _43, _44);
}

inline adlMat4::adlMat4(float value)
{
	vectors.a = adlVec4(value);
	vectors.b = adlVec4(value);
	vectors.c = adlVec4(value);
	vectors.d = adlVec4(value);
}

inline adlMat4::adlMat4(const adlMat4& matrix)
{
	vectors.a = matrix.vectors.a;
	vectors.b = matrix.vectors.b;
	vectors.c = matrix.vectors.c;
	vectors.d = matrix.vectors.d;
}

inline adlMat4::adlMat4(const adlMat3& matrix)
{
	vectors.a = matrix.vectors.a;
	vectors.b = matrix.vectors.b;
	vectors.c = matrix.vectors.c;
	vectors.d = adlVec4(0, 0, 0, 1);
}

inline float adlMat4::operator[](unsigned int index)
{
	adl_assert(index >= 0 && index < 16);
	return mat[index];
}

inline float adlMat4::operator()(unsigned int i, unsigned int j)
{
	adl_assert((i >= 0 && i < 4) && (j >= 0 && j < 4));
	return mat2d[i][j];
}

inline adlMat4 adlMat4::operator+(float scalar) const
{
	return adlMat4(vectors.a + scalar, vectors.b + scalar, vectors.c + scalar, vectors.d + scalar);
}

inline adlMat4 adlMat4::operator-(float scalar) const
{
	return adlMat4(vectors.a - scalar, vectors.b - scalar, vectors.c - scalar, vectors.d - scalar);
}

inline adlMat4 adlMat4::operator*(float scalar) const
{
	return adlMat4(vectors.a * scalar, vectors.b * scalar, vectors.c * scalar, vectors.d * scalar);
}

inline adlMat4 adlMat4::operator/(float scalar) const
{
	adl_assert(scalar != 0.0f);
	return adlMat4(vectors.a / scalar, vectors.b / scalar, vectors.c / scalar, vectors.d / scalar);
}

inline adlMat4 adlMat4::operator+(const adlMat4& matrix) const
{
	return adlMat4(vectors.a + matrix.vectors.a, vectors.b + matrix.vectors.b, vectors.c + matrix.vectors.c, vectors.d + matrix.vectors.d);
}

inline adlMat4 adlMat4::operator-(const adlMat4& matrix) const
{
	return adlMat4(vectors.a - matrix.vectors.a, vectors.b - matrix.vectors.b, vectors.c - matrix.vectors.c, vectors.d - matrix.vectors.d);
}

inline adlMat4 adlMat4::identity()
{
	adlMat4 matrix;
	matrix.mat[0] = 1;
	matrix.mat[1] = 0;
	matrix.mat[2] = 0;
	matrix.mat[3] = 0;

	matrix.mat[4] = 0;
	matrix.mat[5] = 1;
	matrix.mat[6] = 0;
	matrix.mat[7] = 0;

	matrix.mat[8] = 0;
	matrix.mat[9] = 0;
	matrix.mat[10] = 1;
	matrix.mat[11] = 0;

	matrix.mat[12] = 0;
	matrix.mat[13] = 0;
	matrix.mat[14] = 0;
	matrix.mat[15] = 1;

	return matrix;
}

inline void adlMat4::operator=(const adlMat4& matrix)
{
	vectors.a = matrix.vectors.a;
	vectors.b = matrix.vectors.b;
	vectors.c = matrix.vectors.c;
	vectors.d = matrix.vectors.d;
}

class adlMatrix_frame
{
public:

	inline adlMatrix_frame();
	inline adlMatrix_frame(adlVec3 o_, adlVec3 rot_, adlVec3 scale_);
	inline adlMatrix_frame(adlMat4 trans_matrix);
	inline adlMatrix_frame(const adlMatrix_frame& frame);

	static adlMatrix_frame identity();

	adlMat4 get_transformation_matrix();
	adlMat4 get_view_matrix();

	void inverse();

	inline adlVec3 transform_to_parent(const adlVec3& vector);
	//adlMatrix_frame transform_to_parent(const adlMatrix_frame& frame);

	inline adlMatrix_frame operator=(const adlMatrix_frame& frame);

	adlVec3 o;
	adlVec3 scale;
	adlVec3 rot;

private:
	void scale_matrix();
	void rotate_matrix();
	void translate_matrix();

	adlMat4 transformation_matrix_;
};

inline adlMatrix_frame::adlMatrix_frame()
{
}

inline adlMatrix_frame::adlMatrix_frame(adlVec3 o_, adlVec3 rot_, adlVec3 scale_)
{
	o = o_;
	rot = rot_;
	scale = scale_;
}

inline adlMatrix_frame::adlMatrix_frame(adlMat4 trans_matrix)
{
	transformation_matrix_ = trans_matrix;
}

inline adlMatrix_frame::adlMatrix_frame(const adlMatrix_frame& frame)
{
	o = frame.o;
	rot = frame.rot;
	scale = frame.scale;
}

inline adlVec3 adlMatrix_frame::transform_to_parent(const adlVec3& vector)
{
	return transformation_matrix_ * vector;
}

inline adlMatrix_frame adlMatrix_frame::operator=(const adlMatrix_frame& frame)
{
	adlMatrix_frame new_frame;
	new_frame.o = frame.o;
	new_frame.rot = frame.rot;
	new_frame.scale = frame.scale;

	return new_frame;
}

typedef adlMatrix_frame adlTransform;

#endif // matrix_h__
