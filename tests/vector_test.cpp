#include "adl_math/adlMath.h"
#include "adl_debug/adlLogger.h"
#include <gtest/gtest.h>

TEST(Vector3f, Vector_vector_addition)
{
	adlVec3 vector1(5.0f, 6.0f, 8.0f);
	adlVec3 vector2(9.0f, 15.0f, 7.0f);

	adlVec3 new_vec = vector1 + vector2;
	adlVec3 result_vector(14.0f, 21.0f, 15.0f);

	ASSERT_TRUE(new_vec.x == result_vector.x);
	ASSERT_TRUE(new_vec.y == result_vector.y);
	ASSERT_TRUE(new_vec.z == result_vector.z);
}

TEST(Vector3f, Vector_vector_subtraction)
{
	adlVec3 vector1(10.0f, 25.0f, 46.0f);
	adlVec3 vector2(1.0f, 2.0f, 3.0f);

	adlVec3 new_vec = vector1 - vector2;
	adlVec3 result_vector(9.0f, 23.0f, 43.0f);

	ASSERT_TRUE(new_vec.x == result_vector.x);
	ASSERT_TRUE(new_vec.y == result_vector.y);
	ASSERT_TRUE(new_vec.z == result_vector.z);
}

TEST(Vector3f, Vector_vector_multiplication)
{
	adlVec3 vector1(23.0f, 21.0f, 10.0f);
	adlVec3 vector2(2.0f, 3.0f, 4.0f);

	adlVec3 new_vec = vector1 * vector2;
	adlVec3 result_vector(46.0f, 63.0f, 40.0f);

	ASSERT_TRUE(new_vec.x == result_vector.x);
	ASSERT_TRUE(new_vec.y == result_vector.y);
	ASSERT_TRUE(new_vec.z == result_vector.z);
}

TEST(Vector3f, Vector_vector_division)
{
	adlVec3 vector1(6.0f, 21.0f, 45.0f);
	adlVec3 vector2(3.0f, 7.0f, 15.0f);

	adlVec3 new_vec = vector1 / vector2;
	adlVec3 result_vector(2.0f, 3.0f, 3.0f);

	ASSERT_TRUE(new_vec.x == result_vector.x);
	ASSERT_TRUE(new_vec.y == result_vector.y);
	ASSERT_TRUE(new_vec.z == result_vector.z);
}

TEST(Vector3f, Vector_scalar_addition)
{
	adlVec3 vector(15.0f, 21.0f, 36.0f);
	float scalar = 5.0f;

	adlVec3 new_vec = vector + scalar;
	adlVec3 result_vector(20.0f, 26.0f, 41.0f);

	ASSERT_TRUE(new_vec.x == result_vector.x);
	ASSERT_TRUE(new_vec.y == result_vector.y);
	ASSERT_TRUE(new_vec.z == result_vector.z);
}

TEST(Vector3f, Vector_equals)
{
	adlVec3 vector1(5.0f, 1.0f, 15.0f);
	adlVec3 vector2(5.0f, 1.0f, 15.0f);

	ASSERT_TRUE(vector1 == vector2);
}