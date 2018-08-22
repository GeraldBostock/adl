#ifndef material_test_h__
#define material_test_h__

#include "engine/adl_entities/adlActor.h"

class Material_test : public adlActor
{
public:
	Material_test();
	~Material_test();

	void init() override;
	void update(float dt) override;

private:

};

#endif // material_test_h__