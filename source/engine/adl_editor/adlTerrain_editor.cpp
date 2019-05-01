#include "adlTerrain_editor.h"

#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlTerrain.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adlInput.h"
#include "engine/adl_resource/adlTexture.h"

adlTerrain_editor::adlTerrain_editor()
	:	selection_state_(false),
		is_editor_open_(false),
		elevate_(false),
		lower_(false),
		smooth_(false),
		texture1_(false),
		texture2_(false),
		texture3_(false),
		texture4_(false)
{

}

adlTerrain_editor::~adlTerrain_editor()
{

}

void adlTerrain_editor::update()
{
	ImGui::Begin("Terrain Editor");
	ImGui::Text("Deform");
	ImGui::Indent();

	if (ImGui::Checkbox("Elevate", &elevate_))
	{
		lower_ = false;
		smooth_ = false;
		texture1_ = false;
		texture2_ = false;
		texture3_ = false;
		texture4_ = false;
	}
	if (ImGui::Checkbox("Lower", &lower_))
	{
		elevate_ = false;
		smooth_ = false;
		texture1_ = false;
		texture2_ = false;
		texture3_ = false;
		texture4_ = false;
	}
	if (ImGui::Checkbox("Smooth", &smooth_))
	{
		elevate_ = false;
		lower_ = false;
		texture1_ = false;
		texture2_ = false;
		texture3_ = false;
		texture4_ = false;
	}
	ImGui::Unindent();
	ImGui::Text("Textures");
	ImGui::Indent();

	if (ImGui::Checkbox("Grass", &texture1_))
	{
		elevate_ = false;
		lower_ = false;
		smooth_ = false;
		texture2_ = false;
		texture3_ = false;
		texture4_ = false;
	}
	if (ImGui::Checkbox("Stone", &texture2_))
	{
		elevate_ = false;
		lower_ = false;
		smooth_ = false;
		texture1_ = false;
		texture3_ = false;
		texture4_ = false;
	}
	if (ImGui::Checkbox("Dirt", &texture3_))
	{
		elevate_ = false;
		lower_ = false;
		smooth_ = false;
		texture1_ = false;
		texture2_ = false;
		texture4_ = false;
	}
	if (ImGui::Checkbox("Snow", &texture4_))
	{
		elevate_ = false;
		lower_ = false;
		smooth_ = false;
		texture1_ = false;
		texture2_ = false;
		texture3_ = false;
	}
	ImGui::Unindent();
	ImGui::End();
}

void adlTerrain_editor::set_open(bool open)
{
	is_editor_open_ = open;
}

void adlTerrain_editor::on_terrain_mouse_ray_collision(const adlVec3& collision_point)
{
	if (!is_editor_open_)
	{
		return;
	}

	adlScene_manager* scn_mngr = &adlScene_manager::get();
	adlTerrain_shared_ptr terrain = scn_mngr->get_terrain();
	adlInput* input = &adlInput::get();

	if (input->get_mouse_down(ADL_BUTTON_LEFT))
	{
		start_tile_selection_state(collision_point, terrain->get_width(), terrain->get_height());
	}

	update_selection_state(get_grid_index(collision_point, terrain->get_width(), terrain->get_height()), terrain);

	if (input->get_mouse_up(ADL_BUTTON_LEFT))
	{
		end_tile_selection_state(get_grid_index(collision_point, terrain->get_width(), terrain->get_height()), terrain);
	}

}

void adlTerrain_editor::start_tile_selection_state(const adlVec3& collision_point, int width, int height)
{
	selection_state_ = true;
	selection_start_index_ = get_grid_index(collision_point, width, height);
}

void adlTerrain_editor::update_selection_state(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain)
{
	if (selection_state_)
	{
		int x_min = current_tile_index.x;
		int x_max = selection_start_index_.x;
		if (selection_start_index_.x < current_tile_index.x)
		{
			x_min = selection_start_index_.x;
			x_max = current_tile_index.x;
		}

		int y_min = selection_start_index_.y;
		int y_max = current_tile_index.y;
		if (current_tile_index.y < selection_start_index_.y)
		{
			y_min = current_tile_index.y;
			y_max = selection_start_index_.y;
		}

		adlDebug_renderer* db_renderer = &adlDebug_renderer::get();

		for (int i = x_min; i <= x_max; i++)
		{
			for (int j = y_min; j <= y_max; j++)
			{
				Vertex vertex = terrain->get_vertex_at_index(i, j);
				Vertex vertex1 = terrain->get_vertex_at_index(i + 1, j);
				Vertex vertex2 = terrain->get_vertex_at_index(i, j + 1);
				Vertex vertex3 = terrain->get_vertex_at_index(i + 1, j + 1);

				db_renderer->render_line3D(vertex.position, vertex1.position, 1.0f, adlColor::WHITE);
				db_renderer->render_line3D(vertex1.position, vertex3.position, 1.0f, adlColor::WHITE);
				db_renderer->render_line3D(vertex3.position, vertex2.position, 1.0f, adlColor::WHITE);
				db_renderer->render_line3D(vertex2.position, vertex.position, 1.0f, adlColor::WHITE);
			}
		}
	}
}

void adlTerrain_editor::end_tile_selection_state(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain)
{
	if (!selection_state_)
	{
		return;
	}

	selection_state_ = false;
	const std::set<std::pair<int, int>> vertices = get_selected_vertices(current_tile_index, terrain);

	if (elevate_ || lower_ || smooth_)
	{
		const std::vector<Vertex>& terrain_vertices = terrain->get_vertices();
		std::vector<Vertex> edited_vertices;
		for (auto vertex : vertices)
		{
			Vertex new_vertex = terrain_vertices[vertex.first * terrain->get_width() + vertex.second];
			if (elevate_)
			{
				new_vertex.position.y++;
			}
			if (lower_)
			{
				new_vertex.position.y--;
			}
			if (smooth_)
			{
				new_vertex.position.y = terrain->get_vertex_at_index(selection_start_index_.x, selection_start_index_.y).position.y;
			}
			edited_vertices.push_back(new_vertex);
		}

		terrain->edit_vertices(vertices, edited_vertices);
	}

	if (texture1_ || texture2_ || texture3_ || texture4_)
	{
		const std::vector<unsigned char>& pixel_array = terrain->get_blend_map()->get_pixel_array();
		int width = terrain->get_width();
		int height = terrain->get_height();

		std::vector<unsigned char> edited_pixels = pixel_array;

		int x_min = current_tile_index.x;
		int x_max = selection_start_index_.x;
		if (selection_start_index_.x < current_tile_index.x)
		{
			x_min = selection_start_index_.x;
			x_max = current_tile_index.x;
		}

		int y_min = selection_start_index_.y;
		int y_max = current_tile_index.y;
		if (current_tile_index.y < selection_start_index_.y)
		{
			y_min = current_tile_index.y;
			y_max = selection_start_index_.y; 
		}

		int scale_rate = terrain->get_blend_map()->get_width() / terrain->get_width();

		for (unsigned int i = x_min * scale_rate * 4; i < x_max * scale_rate * 4 + scale_rate * 4; i += 4)
		{
			for (unsigned int j = y_min * scale_rate * 4; j < y_max * scale_rate * 4 + scale_rate * 4; j += 4)
			{
				int channel = 0;
				if (texture2_)
				{
					channel = 0;
				}
				if (texture3_)
				{
					channel = 1;
				}
				if (texture4_)
				{
					channel = 2;
				}
				edited_pixels[i * terrain->get_blend_map()->get_width() + j + channel] = 255;
				if (texture1_)
				{
					edited_pixels[i * terrain->get_blend_map()->get_width() + j] = 0;
					edited_pixels[i * terrain->get_blend_map()->get_width() + j + 1] = 0;
					edited_pixels[i * terrain->get_blend_map()->get_width() + j + 2] = 0;
				}
			}
		}

		terrain->get_blend_map()->set_pixel_array(edited_pixels);
		terrain->get_blend_map()->reload_texture();
	}
}

const std::set<std::pair<int, int>> adlTerrain_editor::get_selected_vertices(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain)
{
	int x_min = current_tile_index.x;
	int x_max = selection_start_index_.x;
	if (selection_start_index_.x < current_tile_index.x)
	{
		x_min = selection_start_index_.x;
		x_max = current_tile_index.x;
	}

	int y_min = selection_start_index_.y;
	int y_max = current_tile_index.y;
	if (current_tile_index.y < selection_start_index_.y)
	{
		y_min = current_tile_index.y;
		y_max = selection_start_index_.y;
	}

	std::set<std::pair<int, int>> vertices;
	for (int i = x_min; i <= x_max; i++)
	{
		for (int j = y_min; j <= y_max; j++)
		{
			vertices.insert(std::make_pair(i, j));
			if (i + 1 < terrain->get_width())
			{
				vertices.insert(std::make_pair(i + 1, j));
			}
			if (j + 1 < terrain->get_height())
			{
				vertices.insert(std::make_pair(i, j + 1));
			}
			if (i + 1 < terrain->get_width() && j + 1 < terrain->get_height())
			{
				vertices.insert(std::make_pair(i + 1, j + 1));
			}
		}
	}

	return vertices;
}

adlVec2_i32 adlTerrain_editor::get_grid_index(const adlVec3& collision_point, int terrain_width, int terrain_height)
{
	adlVec2_i32 indices(collision_point.x + 0.5 - terrain_width / 2, collision_point.z + 0.5 - terrain_height / 2);
	indices = -indices;
	indices = indices.swap();

	return indices;
}