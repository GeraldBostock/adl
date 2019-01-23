#include "adlMatrix.h"

#include <iostream>

adlMat3 adlMat3::operator*(const adlMat3& matrix) const
{
	adlMat3 result_matrix = adlMat3::identity();

	adlVec3 row1(vectors.a.x, vectors.b.x, vectors.c.x);
	adlVec3 row2(vectors.a.y, vectors.b.y, vectors.c.y);
	adlVec3 row3(vectors.a.z, vectors.b.z, vectors.c.z);

	result_matrix.mat[0] = row1.dotp(matrix.vectors.a);
	result_matrix.mat[1] = row2.dotp(matrix.vectors.a);
	result_matrix.mat[2] = row3.dotp(matrix.vectors.a);

	result_matrix.mat[4] = row1.dotp(matrix.vectors.b);
	result_matrix.mat[5] = row2.dotp(matrix.vectors.b);
	result_matrix.mat[6] = row3.dotp(matrix.vectors.b);

	result_matrix.mat[8] = row1.dotp(matrix.vectors.c);
	result_matrix.mat[9] = row2.dotp(matrix.vectors.c);
	result_matrix.mat[10] = row3.dotp(matrix.vectors.c);

	return result_matrix;
}

adlVec3 adlMat3::operator*(const adlVec3& vector) const
{
	float a_ = (vectors.a.x * vector.x) + (vectors.a.y * vector.y) + (vectors.a.z * vector.z);
	float b_ = (vectors.b.x * vector.x) + (vectors.b.y * vector.y) + (vectors.b.z * vector.z);
	float c_ = (vectors.c.x * vector.x) + (vectors.c.y * vector.y) + (vectors.c.z * vector.z);

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
	rot_matrix.vectors.b.y = std::cos(radians);
	rot_matrix.vectors.b.z = std::sin(radians);

	rot_matrix.vectors.c.y = -std::sin(radians);
	rot_matrix.vectors.c.z = std::cos(radians);

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

	rot_matrix.vectors.a.x = std::cos(radians);
	rot_matrix.vectors.a.z = -std::sin(radians);

	rot_matrix.vectors.c.x = std::sin(radians);
	rot_matrix.vectors.c.z = std::cos(radians);

	return rot_matrix;
}

adlMat3 adlMat3::get_z_rotation_matrix(float radians)
{
	/*
	* Matrix for z axis rotation
	*
	* | cosθ  -sinθ	   0 |
	* | sinθ   cosθ    0 |
	* | 0       0      1 |
	*
	*/

	adlMat3 rot_matrix = adlMat3::identity();
	rot_matrix.vectors.a.x = std::cos(radians);
	rot_matrix.vectors.a.y = std::sin(radians);

	rot_matrix.vectors.b.x = -std::sin(radians);
	rot_matrix.vectors.b.y = std::cos(radians);

	return rot_matrix;
}

adlMat4 adlMat4::operator*(const adlMat4& matrix) const
{
	adlMat4 result_matrix = adlMat4::identity();

	adlVec4 row1(vectors.a.x, vectors.b.x, vectors.c.x, vectors.d.x);
	adlVec4 row2(vectors.a.y, vectors.b.y, vectors.c.y, vectors.d.y);
	adlVec4 row3(vectors.a.z, vectors.b.z, vectors.c.z, vectors.d.z);
	adlVec4 row4(vectors.a.w, vectors.b.w, vectors.c.w, vectors.d.w);

	result_matrix.mat[0] = row1.dotp(matrix.vectors.a);
	result_matrix.mat[1] = row2.dotp(matrix.vectors.a);
	result_matrix.mat[2] = row3.dotp(matrix.vectors.a);
	result_matrix.mat[3] = row4.dotp(matrix.vectors.a);

	result_matrix.mat[4] = row1.dotp(matrix.vectors.b);
	result_matrix.mat[5] = row2.dotp(matrix.vectors.b);
	result_matrix.mat[6] = row3.dotp(matrix.vectors.b);
	result_matrix.mat[7] = row4.dotp(matrix.vectors.b);

	result_matrix.mat[8] = row1.dotp(matrix.vectors.c);
	result_matrix.mat[9] = row2.dotp(matrix.vectors.c);
	result_matrix.mat[10] = row3.dotp(matrix.vectors.c);
	result_matrix.mat[11] = row4.dotp(matrix.vectors.c);

	result_matrix.mat[12] = row1.dotp(matrix.vectors.d);
	result_matrix.mat[13] = row2.dotp(matrix.vectors.d);
	result_matrix.mat[14] = row3.dotp(matrix.vectors.d);
	result_matrix.mat[15] = row4.dotp(matrix.vectors.d);

	return result_matrix;
}

adlVec4 adlMat4::operator*(const adlVec4& vector) const
{
	float a = (vector.x * vectors.a.x) + (vector.y * vectors.b.x) + (vector.z * vectors.c.x) + (vector.w * vectors.d.x);
	float b = (vector.x * vectors.a.y) + (vector.y * vectors.b.y) + (vector.z * vectors.c.y) + (vector.w * vectors.d.y);
	float c = (vector.x * vectors.a.z) + (vector.y * vectors.b.z) + (vector.z * vectors.c.z) + (vector.w * vectors.d.z);
	float d = (vector.x * vectors.a.w) + (vector.y * vectors.b.w) + (vector.z * vectors.c.w) + (vector.w * vectors.d.w);

	return adlVec4(a, b, c, d);
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

	transformation_matrix_.vectors.a.x = scale.x;
	transformation_matrix_.vectors.b.y = scale.y;
	transformation_matrix_.vectors.c.z = scale.z;
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
	* C = o.z
	*/

	transformation_matrix_.vectors.d.x = o.x;
	transformation_matrix_.vectors.d.y = o.y;
	transformation_matrix_.vectors.d.z = o.z;
}

adlMat4 adlMatrix_frame::get_transformation_matrix()
{
	transformation_matrix_ = adlMat4::identity();

	scale_matrix();
	rotate_matrix();
	translate_matrix();

	return transformation_matrix_;
}

adlMat4 adlMatrix_frame::get_view_matrix()
{
	transformation_matrix_ = adlMat4::identity();
	float cos_pitch = std::cos(rot.x);
	float sin_pitch = std::sin(rot.x);
	float cos_yaw = std::cos(rot.y);
	float sin_yaw = std::sin(rot.y);

	adlVec3 x_axis(cos_yaw, 0, -sin_yaw);
	adlVec3 y_axis(sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch);
	adlVec3 z_axis(sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw);

	transformation_matrix_.vectors.a = adlVec4(x_axis.x, y_axis.x, z_axis.x, 0);
	transformation_matrix_.vectors.b = adlVec4(x_axis.y, y_axis.y, z_axis.y, 0);
	transformation_matrix_.vectors.c = adlVec4(x_axis.z, y_axis.z, z_axis.z, 0);
	transformation_matrix_.vectors.d = adlVec4(-x_axis.dotp(o), -y_axis.dotp(o), -z_axis.dotp(o), 1);

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

void adlMatrix_frame::inverse()
{
	adlVec3 inverse_a;
	adlVec3 inverse_b;
	adlVec3 inverse_c;
	adlVec3 inverse_d;

	inverse_a.x = transformation_matrix_.vectors.a.x;
	inverse_a.y = transformation_matrix_.vectors.b.x;
	inverse_a.z = transformation_matrix_.vectors.c.x;
	inverse_a.w = transformation_matrix_.vectors.d.x;

	inverse_b.x = transformation_matrix_.vectors.a.y;
	inverse_b.y = transformation_matrix_.vectors.b.y;
	inverse_b.z = transformation_matrix_.vectors.c.y;
	inverse_b.w = transformation_matrix_.vectors.d.y;

	inverse_c.x = transformation_matrix_.vectors.a.z;
	inverse_c.y = transformation_matrix_.vectors.b.z;
	inverse_c.z = transformation_matrix_.vectors.c.z;
	inverse_c.w = transformation_matrix_.vectors.d.z;

	inverse_d.x = transformation_matrix_.vectors.a.w;
	inverse_d.y = transformation_matrix_.vectors.b.w;
	inverse_d.z = transformation_matrix_.vectors.c.w;
	inverse_d.w = transformation_matrix_.vectors.d.w;

	transformation_matrix_.vectors.a = inverse_a;
	transformation_matrix_.vectors.b = inverse_b;
	transformation_matrix_.vectors.c = inverse_c;
	transformation_matrix_.vectors.d = inverse_d;
}

adlMat4 adlMat4::create_projection_matrix(int window_width, int window_height, float fov_in_radians, float near_plane, float far_plane)
{
	adlMat4 projection_matrix = adlMat4::identity();
	float aspect_ratio = (float)window_width / (float)window_height;
	float y_scale = (float)(1.0f / (std::tan(fov_in_radians / 2.0f) * aspect_ratio));
	float x_scale = y_scale / aspect_ratio;
	float frustum_length = far_plane - near_plane;

	projection_matrix.vectors.a.x = x_scale;
	projection_matrix.vectors.b.y = y_scale;
	projection_matrix.vectors.c.z = -((far_plane + near_plane) / frustum_length);
	projection_matrix.vectors.c.w = -1;
	projection_matrix.vectors.d.z = -((2 * far_plane * near_plane) / frustum_length);
	projection_matrix.vectors.d.w = 0;

	return projection_matrix;
}

adlMat4 adlMat4::create_view_matrix(adlVec3 position, adlVec3 rotation)
{
	adlMat4 view_matrix = adlMat4::identity();
	float cos_pitch = std::cos(rotation.x);
	float sin_pitch = std::sin(rotation.x);
	float cos_yaw = std::cos(rotation.y);
	float sin_yaw = std::sin(rotation.y);

	adlVec3 x_axis(cos_yaw, 0, -sin_yaw);
	adlVec3 y_axis(sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch);
	adlVec3 z_axis(sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw);

	view_matrix.vectors.a = adlVec4(x_axis.x, y_axis.x, z_axis.x, 0);
	view_matrix.vectors.b = adlVec4(x_axis.y, y_axis.y, z_axis.y, 0);
	view_matrix.vectors.c = adlVec4(x_axis.z, y_axis.z, z_axis.z, 0);
	view_matrix.vectors.d = adlVec4(-x_axis.dotp(position), -y_axis.dotp(position), -z_axis.dotp(position), 1);

	return view_matrix;
}

adlVec3 adlMat4::transform_to_local(const adlVec3& vector)
{
	adlVec3 result_vector(0.0f);

	result_vector.x = vectors.a.dotp(vector);
	result_vector.y = vectors.b.dotp(vector);
	result_vector.z = vectors.c.dotp(vector);
	result_vector.w = vectors.d.dotp(vector);

	return result_vector;
}

adlVec3 adlMat4::transform_to_parent(const adlVec3& vector)
{
	adlVec3 padded_vector = vector;
	padded_vector.w = 1.0f;

	float a = (padded_vector.x * vectors.a.x) + (padded_vector.y * vectors.b.x) + (padded_vector.z * vectors.c.x) + (padded_vector.w * vectors.d.x);
	float b = (padded_vector.x * vectors.a.y) + (padded_vector.y * vectors.b.y) + (padded_vector.z * vectors.c.y) + (padded_vector.w * vectors.d.y);
	float c = (padded_vector.x * vectors.a.z) + (padded_vector.y * vectors.b.z) + (padded_vector.z * vectors.c.z) + (padded_vector.w * vectors.d.z);
	float d = (padded_vector.x * vectors.a.w) + (padded_vector.y * vectors.b.w) + (padded_vector.z * vectors.c.w) + (padded_vector.w * vectors.d.w);

	return adlVec4(a, b, c, d);
}

adlMat3 adlMat4::to_mat3()
{
	return adlMat3(adlVec3(vectors.a.x, vectors.a.y, vectors.a.z), adlVec3(vectors.b.x, vectors.b.y, vectors.b.z), adlVec3(vectors.c.x, vectors.c.y, vectors.c.z));
}
