#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"
#include "engine/adlShared_types.h"
#include "engine/common.h"
#include <string>

class Game : public adlRoot
{
public:
	Game();
	~Game();

	bool init() override;
	bool update(int64 dt) override;
	inline void create_window(const std::string& title, int width, int height)
	{
		init_window(title, width, height);
	}
private:
	adlModel_shared_ptr model;
	adlModel_shared_ptr box;
	adlShader_shared_ptr shader;
};

#endif // game_h__