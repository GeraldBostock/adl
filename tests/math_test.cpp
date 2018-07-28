#include "engine/adl_math/adlMath.h"
#include <gtest/gtest.h>

TEST(Math, min3_int)
{
	ASSERT_EQ(adlMath::min3(3, 4, 5), 3);
	ASSERT_EQ(adlMath::min3(8, 12, 2), 2);
	ASSERT_EQ(adlMath::min3(5, 1, 9), 1);
	ASSERT_EQ(adlMath::min3(10, 5, 4), 4);
	ASSERT_EQ(adlMath::min3(11, 6, 7), 6);
	ASSERT_EQ(adlMath::min3(3, 5, 4), 3);
}

TEST(Math, min3_float)
{
	ASSERT_EQ(adlMath::min3(1.2f, 4.5f, 17.0f), 1.2f);
	ASSERT_EQ(adlMath::min3(7.8f, 14.5f, 2.0f), 2.0f);
	ASSERT_EQ(adlMath::min3(7.2f, 1.5f, 17.0f), 1.5f);
	ASSERT_EQ(adlMath::min3(12.2f, 8.5f, 4.0f), 4.0f);
	ASSERT_EQ(adlMath::min3(20.2f, 4.5f, 17.0f), 4.5f);
	ASSERT_EQ(adlMath::min3(1.2f, 4.5f, 3.7f), 1.2f);
}

TEST(Math, max3_int)
{
	ASSERT_EQ(adlMath::max3(11, 10, 9), 11);
	ASSERT_EQ(adlMath::max3(11, 9, 10), 11);
	ASSERT_EQ(adlMath::max3(10, 9, 11), 11);
	ASSERT_EQ(adlMath::max3(10, 11, 9), 11);
	ASSERT_EQ(adlMath::max3(9, 10, 11), 11);
	ASSERT_EQ(adlMath::max3(9, 11, 10), 11);
}