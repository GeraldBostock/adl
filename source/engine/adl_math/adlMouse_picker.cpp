#include "adlMouse_picker.h"

#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adl_debug/adlLogger.h"


adlMouse_picker::adlMouse_picker()
{
}


void adlMouse_picker::update(adlMat4 projection_matrix, adlMat4 view_matrix)
{
	projection_matrix_ = projection_matrix;
	view_matrix_ = view_matrix;
	view_matrix_.vectors.d = adlVec4(0, 0, 0, 1);

	mouse_ray_ = calculate_mouse_ray();

	adlVec3 plane_normal(0, 1, 0);
	adlVec3 ray_origin = mouse_ray_.get_origin();
	adlVec3 ray_direction = mouse_ray_.get_direction();


	//Ray-Plane intersection
	/*float denom = plane_normal.dotp(ray_direction);
	if (std::abs(denom) > 0.0001f)
	{
		float t = -ray_origin.dotp(plane_normal) / denom;
		if (t >= 0)
		{
			adlVec3 location;
			location = ray_origin + (ray_direction * t);
			adlDebug_renderer* debug_renderer = &adlDebug_renderer::get();
			debug_renderer->render_sphere(location, adlColor::BLUE, 0.25f);
		}
	}*/
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

	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlVec3 mouse_direction(world_coords.x, world_coords.y, world_coords.z);
	adlVec3 mouse_direction_normalized = mouse_direction.normalize();

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
	return adlVec4(clip_coordinates.x / projection_matrix_.vectors.a.x, clip_coordinates.y / projection_matrix_.vectors.b.y, -1.0f, 0.0f);
}

adlRay adlMouse_picker::get_mouse_ray()
{
	return mouse_ray_;
}