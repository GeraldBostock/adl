#ifndef vector_h__
#define vector_h__

class adlVec3
{
public:
	adlVec3() {}
	adlVec3(float x, float y, float z);

	float x;
	float y;
	float z;
};

class adlVec2
{
public:
	adlVec2() {}
	adlVec2(float x, float y);

	float x;
	float y;
};

class adlVec2_i32
{
public:
	adlVec2_i32() {}
	adlVec2_i32(__int32 x, __int32 y);

	__int32 x;
	__int32 y;
};


#endif // vector_h__