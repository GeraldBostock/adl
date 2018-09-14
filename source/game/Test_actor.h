#ifndef test_actor_h__
#define test_actor_h__

#include "engine/adl_entities/adlActor.h"

class Test_actor : public adlActor
{
public:
	Test_actor();
	~Test_actor();

	void init() override;
	void update(float dt) override;

	void deserialize(const rapidjson::Value& json_object) override;
	
	float get_test_data()
	{
		return test_data;
	}

private:
	float test_data;
};

#endif // test_actor_h__