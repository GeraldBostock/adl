#ifndef adl_camera_h__
#define adl_camera_h__

#include "engine/adl_math/adlMath.h"
#include "engine/common.h"

enum Camera_type
{
	ct_fps,
	ct_rts,
	ct_god_mode,
	ct_custom
};

class adlCamera
{
public:
	adlCamera();
	~adlCamera();

	void init();
	void update(float dt);
	void look_at(adlVec3 target, adlVec3 up_vector);

	void toggle_active();

	adlMat4 get_view_matrix();

	adlVec3 get_position();
	float get_pitch();
	float get_yaw();
	float get_roll();
	float get_mouse_sensitivity();

	void set_movement_speed(float speed);
	float get_movement_speed();

	void set_camera_type(Camera_type type);
	
protected:
	virtual void update_custom_camera(float dt);
private:
	bool is_paused_;

	adlVec3 position_;
	float pitch_;
	float yaw_;
	float roll_;

	float mouse_sensitivity_;
	float movement_speed_;
	float start_movement_speed_;

	adlVec3 rts_camera_target_;

	adlMat4 view_matrix_;

	Camera_type camera_type_;

	void update_fps_camera(float dt);
	void update_rts_camera(float dt);
	void update_god_mode_camera(float dt);
};

#endif // adl_camera_h__