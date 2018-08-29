#include "adlLight_editor.h"

#include "imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adl_entities/adlSun.h"

adlLight_editor::adlLight_editor()
	: window_open_(false)
{
}


adlLight_editor::~adlLight_editor()
{
}

void adlLight_editor::update(adlSun_shared_ptr sun, std::vector<adlPoint_light_shared_ptr>& point_lights)
{
	adlInput* input = &adlInput::get();

	if (input->get_key(adl_key_left_ctrl) && input->get_key_up(adl_key_l))
	{
		window_open_ = !window_open_;
	}

	if (window_open_)
	{
		float sun_x = sun->get_position().x;
		float sun_y = sun->get_position().y;
		float sun_z = sun->get_position().z;
		ImGui::Begin("Light Editor");
		ImGui::InputFloat("Position", &sun_x, 0.01f, 1.0f, "%.8f");
		ImGui::End();

		sun->set_position(adlVec3(sun_x, sun_y, sun_z));
	}
}