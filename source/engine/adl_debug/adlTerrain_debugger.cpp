#include "adlTerrain_debugger.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlTerrain.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

adlTerrain_debugger::adlTerrain_debugger()
	:	debugger_open_(false),
		draw_normals_(false),
		draw_face_normals_(false),
		normal_drawing_radius_(15.0f),
		face_normal_radius_(15.0f)
{

}

adlTerrain_debugger::~adlTerrain_debugger()
{

}

void adlTerrain_debugger::update()
{
	adlInput* input = &adlInput::get();

	if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_t))
	{
		debugger_open_ = !debugger_open_;
	}

	if (debugger_open_)
	{
		adlScene_manager* scn_mgr = &adlScene_manager::get();
		adlScene_shared_ptr scene = scn_mgr->get_active_scene();

		adlTerrain_shared_ptr terrain = scene->get_terrain();

		ImGui::Begin("Terrain debugger");

		if (terrain == nullptr)
		{
			ImGui::Text("Terrain is null");
		}
		else
		{
			ImGui::Text(terrain->get_name().c_str());

			if (ImGui::Checkbox("Draw normals", &draw_normals_))
			{

			}

			if (draw_normals_)
			{
				if (ImGui::SliderFloat("Draw radius", &normal_drawing_radius_, 1.0f, 100.0f))
				{

				}
			}

			if (ImGui::Checkbox("Draw face normals", &draw_face_normals_))
			{
				if (ImGui::SliderFloat("Draw radius", &face_normal_radius_, 1.0f, 100.0f))
				{

				}
			}
		}

		ImGui::End();

		if (draw_normals_)
		{
			adlDebug_renderer* dbg_renderer = &adlDebug_renderer::get();
			const std::vector<Vertex>& vertices = terrain->get_vertices();
			adlCamera* camera = scene->get_camera();
			adlVec3 camera_position = camera->get_position();

			for (auto vertex : vertices)
			{
				adlVec3 position = vertex.position;
				if (adlMath::distance_between(camera_position, position) < normal_drawing_radius_)
				{
					dbg_renderer->render_line3D(position, position + vertex.normal / 4.0f, 1.0f, adlColor::YELLOW);
				}
			}
		}

		if (draw_face_normals_)
		{
			
			adlDebug_renderer* dbg_renderer = &adlDebug_renderer::get();
			const std::vector<adlVec3>& face_normals = terrain->get_face_normals();
			for (unsigned int i = 0; i < face_normals.size(); i = i+2)
			{
				dbg_renderer->render_line3D(face_normals[i + 1], face_normals[i + 1] + face_normals[i] / 4.0f, 1.0f, adlColor::YELLOW);
			}
		}
	}
}