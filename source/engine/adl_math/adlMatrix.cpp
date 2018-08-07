#include "adlMatrix.h"

#include <iostream>

adlMat3 adlMat3::operator*(const adlMat3& matrix) const
{
	adlMat3 result_matrix = adlMat3::identity();

	adlVec3 row1(a.x, b.x, c.x);
	adlVec3 row2(a.y, b.y, c.y);
	adlVec3 row3(a.z, b.z, c.z);

	result_matrix.mat[0] = row1.dotp(matrix.a);
	result_matrix.mat[1] = row2.dotp(matrix.a);
	result_matrix.mat[2] = row3.dotp(matrix.a);

	result_matrix.mat[4] = row1.dotp(matrix.b);
	result_matrix.mat[5] = row2.dotp(matrix.b);
	result_matrix.mat[6] = row3.dotp(matrix.b);

	result_matrix.mat[8] = row1.dotp(matrix.c);
	result_matrix.mat[9] = row2.dotp(matrix.c);
	result_matrix.mat[10] = row3.dotp(matrix.c);

	return result_matrix;
}

adlVec3 adlMat3::operator*(const adlVec3& vector) const
{
	float a_ = (a.x * vector.x) + (a.y * vector.y) + (a.z * vector.z);
	float b_ = (b.x * vector.x) + (b.y * vector.y) + (b.z * vector.z);
	float c_ = (c.x * vector.x) + (c.y * vector.y) + (c.z * vector.z);

	return adlVec3(a_, b_, c_);
}

adlMat3 adlMat3::get_x_rotation_matrix(float radians)
{
	/*
	* Matrix for x axis rotation
	* 
	* | 1	  0	     0   |
	* | 0    cosθ  -sinθ |
	* | 0    sinθ   cosθ |
	* 
	*/

	adlMat3 rot_matrix = adlMat3::identity();
	rot_matrix.b.y = std::cos(radians);
	rot_matrix.b.z = std::sin(radians);

	rot_matrix.c.y = -std::sin(radians);
	rot_matrix.c.z = std::cos(radians);

	return rot_matrix;
}

adlMat3 adlMat3::get_y_rotation_matrix(float radians)
{
	/*
	* Matrix for y axis rotation
	*
	* | cosθ  0	    sinθ |
	* | 0     1       0  |
	* | -sinθ 0     cosθ |
	*
	*/

	adlMat3 rot_matrix = adlMat3::identity();

	rot_matrix.a.x = std::cos(radians);
	rot_matrix.a.z = -std::sin(radians);

	rot_matrix.c.x = std::sin(radians);
	rot_matrix.c.z = std::cos(radians);

	return rot_matrix;
}

adlMat3 adlMat3::get_z_rotation_matrix(float radians)
{
	/*
	* Matrix for y axis rotation
	*
	* | cosθ  -sinθ	   0 |
	* | sinθ   cosθ    0 |
	* | 0       0      1 |
	*
	*/

	adlMat3 rot_matrix = adlMat3::identity();
	rot_matrix.a.x = std::cos(radians);
	rot_matrix.a.y = std::sin(radians);

	rot_matrix.b.x = -std::sin(radians);
	rot_matrix.b.y = std::cos(radians);

	return rot_matrix;
}

adlMat4 adlMat4::operator*(const adlMat4& matrix) const
{
	adlMat4 result_matrix = adlMat4::identity();

	adlVec4 row1(a.x, b.x, c.x, d.x);
	adlVec4 row2(a.y, b.y, c.y, d.y);
	adlVec4 row3(a.z, b.z, c.z, d.z);
	adlVec4 row4(a.w, b.w, c.w, d.w);

	result_matrix.mat[0] = row1.dotp(matrix.a);
	result_matrix.mat[1] = row2.dotp(matrix.a);
	result_matrix.mat[2] = row3.dotp(matrix.a);
	result_matrix.mat[3] = row4.dotp(matrix.a);

	result_matrix.mat[4] = row1.dotp(matrix.b);
	result_matrix.mat[5] = row2.dotp(matrix.b);
	result_matrix.mat[6] = row3.dotp(matrix.b);
	result_matrix.mat[7] = row4.dotp(matrix.b);

	result_matrix.mat[8] = row1.dotp(matrix.c);
	result_matrix.mat[9] = row2.dotp(matrix.c);
	result_matrix.mat[10] = row3.dotp(matrix.c);
	result_matrix.mat[11] = row4.dotp(matrix.c);

	result_matrix.mat[12] = row1.dotp(matrix.d);
	result_matrix.mat[13] = row2.dotp(matrix.d);
	result_matrix.mat[14] = row3.dotp(matrix.d);
	result_matrix.mat[15] = row4.dotp(matrix.d);

	return result_matrix;
}

adlVec4 adlMat4::operator*(const adlVec4& vector) const
{
	float a_ = (a.x * vector.x) + (a.y * vector.y) + (a.z * vector.z) + (a.w * vector.w);
	float b_ = (b.x * vector.x) + (b.y * vector.y) + (b.z * vector.z) + (b.w * vector.w);
	float c_ = (c.x * vector.x) + (c.y * vector.y) + (c.z * vector.z) + (c.w * vector.w);
	float d_ = (d.x * vector.x) + (d.y * vector.y) + (d.z * vector.z) + (d.w * vector.w);

	return adlVec4(a_, b_, c_, d_);
}

void adlMatrix_frame::scale_matrix()
{
	/*
	* Scale matrix
	* | A 0 0 0 |
	* | 0 B 0 0 |
	* | 0 0 C 0 |
	* | 0 0 0 1 |
	*
	* A: scale.x
	* B: scale.y
	* C: scale.z
	*/

	transformation_matrix_.a.x = scale.x;
	transformation_matrix_.b.y = scale.y;
	transformation_matrix_.c.z = scale.z;
}

void adlMatrix_frame::rotate_matrix()
{
	adlMat3 x_rotation = adlMat3::identity();
	x_rotation = x_rotation.get_x_rotation_matrix(rot.x);

	adlMat3 y_rotation = adlMat3::identity();
	y_rotation = y_rotation.get_y_rotation_matrix(rot.y);

	adlMat3 z_rotation = adlMat3::identity();
	z_rotation = z_rotation.get_z_rotation_matrix(rot.z);

	adlMat3 rotation_matrix = (x_rotation * y_rotation) * z_rotation;

	adlMat4 mat4(rotation_matrix);

	transformation_matrix_ = transformation_matrix_ * mat4;
}

void adlMatrix_frame::translate_matrix()
{
	/*
	* Translation matrix
	* | 1 0 0 A | 
	* | 0 1 0 B |
	* | 0 0 1 C |
	* | 0 0 0 1 |
	*
	* A = o.x
	* B = o.y
	* C 0 o.z
	*/

	transformation_matrix_.d.x = o.x;
	transformation_matrix_.d.y = o.y;
	transformation_matrix_.d.z = o.z;
}

adlMat4 adlMatrix_frame::get_transformation_matrix()
{
	transformation_matrix_ = adlMat4::identity();

	scale_matrix();
	rotate_matrix();
	translate_matrix();

	return transformation_matrix_;
}

adlMatrix_frame adlMatrix_frame::identity()
{
	adlMatrix_frame frame;
	frame.o = adlVec3(0.0f);
	frame.rot = adlVec3(0.0f);
	frame.scale = adlVec3(1.0f);

	return frame;
}

adlMat4 adlMat4::create_projection_matrix(int window_width, int window_height, float fov_in_radians, float near_plane, float far_plane)
{
	float adl_pi = 3.1415926535897932f;

	adlMat4 projection_matrix = adlMat4::identity();
	float aspect_ratio = (float)window_width / (float)window_height;
	float y_scale = (float)(1.0f / (std::tan(fov_in_radians / 2.0f) * aspect_ratio));
	float x_scale = y_scale / aspect_ratio;
	float frustum_length = far_plane - near_plane;

	projection_matrix.a.x = x_scale;
	projection_matrix.b.y = y_scale;
	projection_matrix.c.z = -((far_plane + near_plane) / frustum_length);
	projection_matrix.c.w = -1;
	projection_matrix.d.z = -((2 * far_plane * near_plane) / frustum_length);
	projection_matrix.d.w = 0;

	return projection_matrix;
}