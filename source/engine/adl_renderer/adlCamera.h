#ifndef adl_camera_h__
#define adl_camera_h__

#include "engine/adl_math/adlMath.h"
#include "engine/common.h"

enum Camera_type
{
	ct_fps_camera,
	ct_rts_camera,
	ct_custom_camera
};

class adlCamera
{
public:
	adlCamera();
	~adlCamera();

	void update(int64 dt);
	void look_at(adlVec3 target, adlVec3 up_vector);

	adlMat4 get_view_matrix();

	adlVec3 get_position();
	float get_pitch();
	float get_yaw();
	float get_roll();
	float get_mouse_sensitivity();
	float get_movement_speed();

	void set_camera_type(Camera_type type);
	
protected:
	virtual void update_custom_camera(int64 dt);
private:
	adlVec3 position_;
	float pitch_;
	float yaw_;
	float roll_;

	float mouse_sensitivity_;
	float movement_speed_;

	adlVec3 rts_camera_target_;

	adlMat4 view_matrix_;

	Camera_type camera_type_;

	void update_fps_camera(int64 dt);
	void update_rts_camera(int64 dt);
};

#endif // adl_camera_h__