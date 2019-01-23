#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

#include "Test_actor.h"
#include "Test_light.h"
#include "Material_test.h"
#include "Material_new_test.h"
#include "Cube_actor.h"

class Game : public adlRoot
{
public:
	Game();
	~Game();

	bool init() override;
	bool update(float dt) override;

private:
	adlTimer timer_;
};

#endif // game_h__