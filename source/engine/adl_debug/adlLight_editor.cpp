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
		adlVec3 sun_position = sun->get_position();
		ImGui::Begin("Light Editor");
		ImGui::InputFloat("", &sun_position.x);
		ImGui::SameLine();
		ImGui::InputFloat("", &sun_position.y);
		ImGui::SameLine();
		ImGui::InputFloat("Position", &sun_position.z);
		ImGui::End();

		sun->set_position(sun_position);
	}
}