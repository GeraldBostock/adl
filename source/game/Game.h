#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

#include "Test_light.h"
#include "game/Physics_listener.h"
#include "game/Tetromino.h"
#include "game/Board.h"

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

	Tetromino* tetromino_;
	Board* board_;
	bool board_debug_draw_ =  false;
};

#endif // game_h__