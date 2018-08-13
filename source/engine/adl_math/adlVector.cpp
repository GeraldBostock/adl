#include "adlVector.h"

adlVec3 adlVec3::crossp(const adlVec3& vector)
{
	adlVec3 result_vector;
	result_vector.x = y * vector.z - z * vector.y;
	result_vector.y = z * vector.x - x * vector.y;
	result_vector.z = x * vector.y - y * vector.x;

	return result_vector;
}

adlVec3 adlVec3::normalize()
{
	float vector_length = length();
	adlVec3 normalized_vector;

	normalized_vector.x = x / vector_length;
	normalized_vector.y = y / vector_length;
	normalized_vector.z = z / vector_length;

	return normalized_vector;
}