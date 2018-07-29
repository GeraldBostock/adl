#include "engine/adl_math/adlMath.h"
#include "engine/adl_math/adlMatrix.cpp"
#include <gtest/gtest.h>

TEST(Matrix_tests, default_constructor)
{
	adlMat3 matrix;
	ASSERT_EQ(matrix[0], 0.0f);
	ASSERT_EQ(matrix[1], 0.0f);
	ASSERT_EQ(matrix[2], 0.0f);

	ASSERT_EQ(matrix[4], 0.0f);
	ASSERT_EQ(matrix[5], 0.0f);
	ASSERT_EQ(matrix[6], 0.0f);

	ASSERT_EQ(matrix[8], 0.0f);
	ASSERT_EQ(matrix[9], 0.0f);
	ASSERT_EQ(matrix[10], 0.0f);
}

TEST(Matrix_tests, all_values_constructor)
{
	adlMat3 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

	ASSERT_FLOAT_EQ(matrix[0], 1.0f);
	ASSERT_FLOAT_EQ(matrix(0, 0), 1.0f);

	ASSERT_FLOAT_EQ(matrix[1], 2.0f);
	ASSERT_FLOAT_EQ(matrix(0, 1), 2.0f);

	ASSERT_FLOAT_EQ(matrix[2], 3.0f);
	ASSERT_FLOAT_EQ(matrix(0, 2), 3.0f);

	ASSERT_FLOAT_EQ(matrix[4], 4.0f);
	ASSERT_FLOAT_EQ(matrix(1, 0), 4.0f);

	ASSERT_FLOAT_EQ(matrix[5], 5.0f);
	ASSERT_FLOAT_EQ(matrix(1, 1), 5.0f);

	ASSERT_FLOAT_EQ(matrix[6], 6.0f);
	ASSERT_FLOAT_EQ(matrix(1, 2), 6.0f);

	ASSERT_FLOAT_EQ(matrix[8], 7.0f);
	ASSERT_FLOAT_EQ(matrix(2, 0), 7.0f);

	ASSERT_FLOAT_EQ(matrix[9], 8.0f);
	ASSERT_FLOAT_EQ(matrix(2, 1), 8.0f);

	ASSERT_FLOAT_EQ(matrix[10], 9.0f);
	ASSERT_FLOAT_EQ(matrix(2, 2), 9.0f);
}

TEST(Matrix_tests, Vec3_constructor)
{
	adlMat3 matrix(adlVec3(0, 1, 0), adlVec3(1, 0, 1), adlVec3(2, 4, 8));

	ASSERT_FLOAT_EQ(matrix[0], 0.0f);
	ASSERT_FLOAT_EQ(matrix[1], 1.0f);
	ASSERT_FLOAT_EQ(matrix[2], 0.0f);

	ASSERT_FLOAT_EQ(matrix[4], 1.0f);
	ASSERT_FLOAT_EQ(matrix[5], 0.0f);
	ASSERT_FLOAT_EQ(matrix[6], 1.0f);

	ASSERT_FLOAT_EQ(matrix[8], 2.0f);
	ASSERT_FLOAT_EQ(matrix[9], 4.0f);
	ASSERT_FLOAT_EQ(matrix[10], 8.0f);
}

TEST(Matrix_tests, scalar_multiplication)
{
	adlVec3 a(1, 2, 3);
	adlVec3 b(4, 5, 6);
	adlVec3 c(7, 8, 9);

	adlMat3 mat(a, b, c);

	mat = mat * 2;

	ASSERT_FLOAT_EQ(mat[0], 2);
	ASSERT_FLOAT_EQ(mat[1], 4);
	ASSERT_FLOAT_EQ(mat[2], 6);

	ASSERT_FLOAT_EQ(mat[4], 8);
	ASSERT_FLOAT_EQ(mat[5], 10);
	ASSERT_FLOAT_EQ(mat[6], 12);

	ASSERT_FLOAT_EQ(mat[8], 14);
	ASSERT_FLOAT_EQ(mat[9], 16);
	ASSERT_FLOAT_EQ(mat[10], 18);
}

TEST(Matrix_tests, matrix_matrix_multiplication)
{
	adlVec3 a1(4, 2, 0);
	adlVec3 b1(0, 8, 1);
	adlVec3 c1(0, 1, 0);

	adlMat3 mat1(a1, b1, c1);

	adlVec3 a2(4, 2, 1);
	adlVec3 b2(2, 0, 4);
	adlVec3 c2(9, 4, 2);

	adlMat3 mat2(a2, b2, c2);

	adlVec3 result_a(20, 8, 12);
	adlVec3 result_b(25, 4, 34);
	adlVec3 result_c(2, 0, 4);

	adlMat3 result_matrix(result_a, result_b, result_c);

	adlMat3 multiplied = mat1 * mat2;

	ASSERT_FLOAT_EQ(multiplied.a.x, result_matrix.a.x);
	ASSERT_FLOAT_EQ(multiplied.a.y, result_matrix.a.y);
	ASSERT_FLOAT_EQ(multiplied.a.z, result_matrix.a.z);

	ASSERT_FLOAT_EQ(multiplied.b.x, result_matrix.b.x);
	ASSERT_FLOAT_EQ(multiplied.b.y, result_matrix.b.y);
	ASSERT_FLOAT_EQ(multiplied.b.z, result_matrix.b.z);

	ASSERT_FLOAT_EQ(multiplied.c.x, result_matrix.c.x);
	ASSERT_FLOAT_EQ(multiplied.c.y, result_matrix.c.y);
	ASSERT_FLOAT_EQ(multiplied.c.z, result_matrix.c.z);

}

TEST(Matrix_tests, identity_matrix)
{
	adlMat3 identity_matrix = adlMat3::identity();

	adlVec3 a(4, 2, 0);
	adlVec3 b(0, 8, 1);
	adlVec3 c(0, 1, 0);

	adlMat3 mat(a, b, c);

	adlMat3 multiplied_matrix = mat * identity_matrix;

	ASSERT_FLOAT_EQ(multiplied_matrix.a.x, mat.a.x);
	ASSERT_FLOAT_EQ(multiplied_matrix.a.y, mat.a.y);
	ASSERT_FLOAT_EQ(multiplied_matrix.a.z, mat.a.z);

	ASSERT_FLOAT_EQ(multiplied_matrix.b.x, mat.b.x);
	ASSERT_FLOAT_EQ(multiplied_matrix.b.y, mat.b.y);
	ASSERT_FLOAT_EQ(multiplied_matrix.b.z, mat.b.z);

	ASSERT_FLOAT_EQ(multiplied_matrix.c.x, mat.c.x);
	ASSERT_FLOAT_EQ(multiplied_matrix.c.y, mat.c.y);
	ASSERT_FLOAT_EQ(multiplied_matrix.c.z, mat.c.z);

	adlVec3 vector(8, 9, 11);

	adlVec3 result_vector = identity_matrix * vector;

	ASSERT_FLOAT_EQ(result_vector.x, vector.x);
	ASSERT_FLOAT_EQ(result_vector.y, vector.y);
	ASSERT_FLOAT_EQ(result_vector.z, vector.z);
}

TEST(Matrix_tests, Matrix_vector_multiplication)
{
	adlVec3 vec(2, 1, 3);

	adlVec3 a(1, 2, 3);
	adlVec3 b(4, 5, 6);
	adlVec3 c(7, 8, 9);

	adlMat3 mat(a, b, c);

	adlVec3 result_vector = mat * vec;

	adlVec3 actual_result(13, 31, 49);

	ASSERT_FLOAT_EQ(actual_result.x, result_vector.x);
	ASSERT_FLOAT_EQ(actual_result.y, result_vector.y);
	ASSERT_FLOAT_EQ(actual_result.z, result_vector.z);
}

TEST(Matrix_tests, Mat4_identity)
{
	adlMat4 mat = adlMat4::identity();
	adlVec4 vec(1, 2, 3, 1);

	adlVec4 multiplied_vector = mat * vec;

	ASSERT_FLOAT_EQ(vec.x, multiplied_vector.x);
	ASSERT_FLOAT_EQ(vec.y, multiplied_vector.y);
	ASSERT_FLOAT_EQ(vec.z, multiplied_vector.z);
	ASSERT_FLOAT_EQ(vec.w, multiplied_vector.w);
}

TEST(Matrix_tests, Matrix_frame)
{
	adlMatrix_frame frame;

	adlVec3 vec(1, 2, 3);
	adlVec3 transformed_position = frame.transform_to_parent(vec);

	ASSERT_FLOAT_EQ(vec.x, transformed_position.x);
	ASSERT_FLOAT_EQ(vec.y, transformed_position.y);
	ASSERT_FLOAT_EQ(vec.z, transformed_position.z);
}