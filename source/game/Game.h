#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

#include "game/Physics_listener.h"

struct Voxel
{
	adlVec3 position;
	int size;

	Voxel(const adlVec3& position, int size)
		: position(position),
		size(size)
	{

	}
};

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

	void create_randomized_voxels();
	std::vector<Voxel> voxels_;
};

#endif // game_h__