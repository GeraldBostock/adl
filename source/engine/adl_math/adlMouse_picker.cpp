#include "adlMouse_picker.h"

#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlScene_manager.h"

adlMouse_picker::adlMouse_picker()
{
}


void adlMouse_picker::update(adlMat4 projection_matrix, adlMat4 view_matrix)
{
	projection_matrix_ = projection_matrix;
	view_matrix_ = view_matrix;

	mouse_ray_ = calculate_mouse_ray();
}

adlRay adlMouse_picker::calculate_mouse_ray()
{
	adlInput* input = &adlInput::get();

	adlVec2_i32 mouse_pos = input->get_mouse_pos();
	adlVec2 mouse_pos_float = mouse_pos.to_vec2();

	adlVec2 ndc = calculate_normalized_device_coords(mouse_pos_float.x, mouse_pos_float.y);
	adlVec4 clip_coordinates(ndc.x, ndc.y, -1.0f, 1.0f);
	adlVec4 eye_coords = to_eye_coordinates(clip_coordinates);

	adlVec4 world_coords = view_matrix_.transform_to_local(eye_coords);
	adlVec3 mouse_direction(world_coords.x, world_coords.y, world_coords.z);
	adlVec3 mouse_direction_normalized = mouse_direction.normalize();

	adlScene_manager* scn_manager = &adlScene_manager::get();

	return adlRay(scn_manager->get_camera()->get_position(), mouse_direction_normalized);
}

adlVec2 adlMouse_picker::calculate_normalized_device_coords(float mouse_x, float mouse_y)
{
	adlWindow* window = adlWindow::get();
	int width = window->get_width();
	int height = window->get_height();

	float x = (2.0f * mouse_x) / (float)width - 1;
	float y = (2.0f * mouse_y) / (float)height - 1;

	return adlVec2(x, -y);
}

adlVec4 adlMouse_picker::to_eye_coordinates(adlVec4 clip_coordinates)
{
	adlVec4 eye_coordinates = projection_matrix_.transform_to_local(clip_coordinates);

	return adlVec4(eye_coordinates.x, eye_coordinates.y, -1.0f, 0.0f);
}

adlRay adlMouse_picker::get_mouse_ray()
{
	return mouse_ray_;
}