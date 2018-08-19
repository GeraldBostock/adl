#include "adlCamera.h"
#include "engine/adlInput.h"
#include "engine/adlRoot.h"

adlCamera::adlCamera()
{
	position_ = adlVec3(0.0f);
	pitch_ = 0;
	yaw_ = 0;
	roll_ = 0;

	mouse_sensitivity_ = 1.0f;
	movement_speed_ = start_movement_speed_ = 0.01f;

	camera_type_ = ct_fps;
}

adlCamera::~adlCamera()
{

}

void adlCamera::update(int64 dt)
{
	switch (camera_type_)
	{
	case ct_fps:
		update_fps_camera(dt);
		break;
	case ct_rts:
		update_rts_camera(dt);
		break;
	case ct_god_mode:
		update_god_mode_camera(dt);
		break;
	case ct_custom:
		update_custom_camera(dt);
		break;
	default:
		//You should not be here. Go away.
		break;
	}

}

void adlCamera::update_fps_camera(int64 dt)
{
	adlInput* input = &adlInput::get();

	int dx = input->get_mouse_x_rel();
	int dy = input->get_mouse_y_rel();

	if (dy < 0 && pitch_ <= 90)
	{
		pitch_ += -dy * mouse_sensitivity_;
	}
	if (dy > 0 && pitch_ >= -90)
	{
		pitch_ -= dy * mouse_sensitivity_;
	}
	if (dx < 0)
	{
		yaw_ += -dx * mouse_sensitivity_;
	}
	if (dx > 0)
	{
		yaw_ -= dx * mouse_sensitivity_;
	}

	if (input->get_key(adl_key_w))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	if (input->get_key(adl_key_s))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	if (input->get_key(adl_key_a))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}
	if (input->get_key(adl_key_d))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}

	view_matrix_ = view_matrix_.create_view_matrix(position_, adlVec3(adlMath::deg_to_rad(pitch_), adlMath::deg_to_rad(yaw_), adlMath::deg_to_rad(roll_)));
}

void adlCamera::look_at(adlVec3 target, adlVec3 up_vector)
{
	adlVec3 z_axis = adlMath::normalize(position_ - target);
	adlVec3 x_axis = adlMath::normalize(adlMath::crossp(up_vector, z_axis));
	adlVec3 y_axis = adlMath::crossp(z_axis, x_axis);

	view_matrix_.vectors.a = adlVec4(x_axis.x, y_axis.x, z_axis.x, 0);
	view_matrix_.vectors.b = adlVec4(x_axis.y, y_axis.y, z_axis.y, 0);
	view_matrix_.vectors.c = adlVec4(x_axis.z, y_axis.z, z_axis.z, 0);
	view_matrix_.vectors.d = adlVec4(-adlMath::dotp(x_axis, position_), -adlMath::dotp(y_axis, position_), -adlMath::dotp(z_axis, position_), 1);
}

void adlCamera::update_rts_camera(int64 dt)
{
	adlInput* input = &adlInput::get();
	adlWindow* window = adlWindow::get();
	int screen_width = window->get_width();
	int screen_height = window->get_height();

	adlVec2_i32 mousePos = input->get_mouse_pos();
	float tolerance = 25;

	if (input->get_key(adl_key_plus))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.y += movement_speed_ * std::sin(adlMath::deg_to_rad(pitch_)) * dt;
	}
	if (input->get_key(adl_key_minus))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.y -= movement_speed_ * std::sin(adlMath::deg_to_rad(pitch_)) * dt;
	}

	if (mousePos.x < tolerance)
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}
	else if (mousePos.x > screen_width - tolerance)
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}

	if (mousePos.y < tolerance)
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	else if (mousePos.y > screen_height - tolerance)
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	if (input->get_key(adl_key_w))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	if (input->get_key(adl_key_s))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt;
	}
	if (input->get_key(adl_key_a))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}
	if (input->get_key(adl_key_d))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}


	view_matrix_ = view_matrix_.create_view_matrix(position_, adlVec3(adlMath::deg_to_rad(pitch_), adlMath::deg_to_rad(yaw_), adlMath::deg_to_rad(roll_)));

}

void adlCamera::update_god_mode_camera(int64 dt)
{
	adlInput* input = &adlInput::get();

	int dx = input->get_mouse_x_rel();
	int dy = input->get_mouse_y_rel();

	if (input->get_key(adl_key_left_shift))
	{
		movement_speed_ *= 2;
	}


	if (dy < 0 && pitch_ < 90)
	{
		pitch_ += -dy * mouse_sensitivity_;
	}
	if (dy > 0 && pitch_ > -90)
	{
		pitch_ -= dy * mouse_sensitivity_;
	}
	if (dx < 0)
	{
		yaw_ += -dx * mouse_sensitivity_;
	}
	if (dx > 0)
	{
		yaw_ -= dx * mouse_sensitivity_;
	}

	if (input->get_key(adl_key_w))
	{
		//Multiply by sin(pitch) because if the pitch is 90 or -90 we don't want to change the x and the z values.
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.y += movement_speed_ * std::sin(adlMath::deg_to_rad(pitch_)) * dt;
	}
	if (input->get_key(adl_key_s))
	{
		//Multiply by sin(pitch) because if the pitch is 90 or -90 we don't want to change the x and the z values.
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_)) * dt * std::cos(adlMath::deg_to_rad(pitch_));
		position_.y -= movement_speed_ * std::sin(adlMath::deg_to_rad(pitch_)) * dt;
	}
	if (input->get_key(adl_key_a))
	{
		position_.z += movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x += movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}
	if (input->get_key(adl_key_d))
	{
		position_.z -= movement_speed_ * std::cos(adlMath::deg_to_rad(yaw_ - 90)) * dt;
		position_.x -= movement_speed_ * std::sin(adlMath::deg_to_rad(yaw_ - 90)) * dt;
	}
	if (input->get_key(adl_key_q))
	{
		position_.y -= movement_speed_ * dt;
	}
	if (input->get_key(adl_key_e))
	{
		position_.y += movement_speed_ * dt;
	}

	view_matrix_ = view_matrix_.create_view_matrix(position_, adlVec3(adlMath::deg_to_rad(pitch_), adlMath::deg_to_rad(yaw_), adlMath::deg_to_rad(roll_)));

	movement_speed_ = start_movement_speed_;
}

void adlCamera::update_custom_camera(int64 dt)
{
}

adlMat4 adlCamera::get_view_matrix()
{
	return view_matrix_;
}

adlVec3 adlCamera::get_position()
{
	return position_;
}

float adlCamera::get_pitch()
{
	return pitch_;
}

float adlCamera::get_yaw()
{
	return yaw_;
}

float adlCamera::get_roll()
{
	return roll_;
}

float adlCamera::get_mouse_sensitivity()
{
	return mouse_sensitivity_;
}

void adlCamera::set_movement_speed(float speed)
{
	movement_speed_ = speed;
}

float adlCamera::get_movement_speed()
{
	return movement_speed_;
}

void adlCamera::set_camera_type(Camera_type type)
{
	camera_type_ = type;
	if (camera_type_ == ct_rts)
	{
		position_ = adlVec3(2.0f, 5.0f, 2.5f);
		rts_camera_target_ = adlVec3(0.0, 0.0f, 0.0f);
		pitch_ = -45;
	}
}