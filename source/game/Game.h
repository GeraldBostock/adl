#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"
#include "engine/adlShared_types.h"
#include "engine/common.h"
#include "engine/adl_helper/adlTimer.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adlEntity.h"
#include "Camera.h"
#include "engine/adl_renderer/adlLight.h"
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
	adlEntity bison_entity_;
	adlEntity box1_;
	adlEntity box2_;
	adlEntity mount_;
	adlEntity teapot_entity_;
	adlLight* light_;

	std::vector<adlEntity> boxes_;

	float model_z = 0.0f;
	float model_x = 0.0f;
	float model_yaw = 0;
	float model_pitch = 0;

	adlTimer timer_;
};

#endif // game_h__