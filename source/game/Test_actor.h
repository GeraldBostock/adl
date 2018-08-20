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

private:

};

#endif // test_actor_h__