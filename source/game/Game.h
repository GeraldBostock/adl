#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

#include "game/Physics_listener.h"
#include "game/Voxel_manager.h"

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
	adlEntity_shared_ptr entity = nullptr;
	
	Voxel_manager voxel_manager_;
};

#endif // game_h__