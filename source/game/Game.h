#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

#include "Test_light.h"
#include "game/Physics_listener.h"

class Game : public adlRoot
{
public:
	Game();
	~Game();

	bool init() override;
	bool update(float dt) override;

private:
	adlTimer timer_;
	Physics_listener* listener_;
};

#endif // game_h__