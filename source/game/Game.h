#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"
#include <string>

class Game : public adlRoot
{
public:
	Game();
	~Game();

	bool init() override;
	bool update(double dt) override;
	inline void create_window(const std::string& title, int width, int height)
	{
		init_window(title, width, height);
	}
};

#endif // game_h__