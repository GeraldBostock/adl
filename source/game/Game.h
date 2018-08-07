#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"
#include "engine/adlShared_types.h"
#include "engine/common.h"
#include "engine/adl_helper/adlTimer.h"
#include "engine/adl_resource/adlModel.h"
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
	adlModel_shared_ptr box2;
	adlShader_shared_ptr shader;
	adlModel plank_model_;

	float model_z = 0.0f;
	float model_x = 0.0f;

	adlTimer timer_;
};

#endif // game_h__