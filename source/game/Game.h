#ifndef game_h__
#define game_h__

#include "engine/adlRoot.h"

class Game : public adlRoot
{
public:
	Game();
	~Game();

	bool init() override;
	bool update(int64 dt) override;

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
	adlEntity at_at_;
	adlEntity big_box_;
	adlLight* light_;

	std::vector<adlEntity> boxes_;

	float model_z = 0.0f;
	float model_x = 0.0f;
	float model_yaw = 0;
	float model_pitch = 0;

	adlTimer timer_;
};

#endif // game_h__