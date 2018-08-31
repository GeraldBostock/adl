#ifndef material_new_test_h__
#define material_new_test_h__

#include "engine/adl_entities/adlActor.h"

class Material_new_test : public adlActor
{
public:

	Material_new_test();
	~Material_new_test();

	void init() override;
	void update(float dt) override;
private:

};

#endif // material_new_test_h__