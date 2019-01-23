#ifndef cube_actor_h__
#define cube_actor_h__

#include "engine/adl_entities/adlActor.h"

class Cube_actor : public adlActor
{
public:
	Cube_actor();
	~Cube_actor();

	void init() override;
	void update(float dt) override;
};

#endif // cube_actor_h__