#ifndef physics_listener_h__
#define physics_listener_h__

#include "../engine/adlPhysics_observer.h" 
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlTerrain.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adlInput.h"

class Physics_listener : public adlPhysics_observer
{
public:
	Physics_listener() {};
	~Physics_listener() {};

	virtual void on_collision_start(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) override
	{
		std::cout << "collision start" << std::endl;
	}

	virtual void on_collision_end(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2)
	{
	}

	virtual void on_terrain_collision_start(adlEntity_shared_ptr entity, const adlVec3& collision_point)
	{
	}

	virtual void on_terrain_collision_end(adlEntity_shared_ptr entity)
	{
	}

	virtual void on_terrain_mouse_ray_collision(const adlVec3& collision_point) 
	{
		//adlScene_manager* scn_mngr = &adlScene_manager::get();
		//adlTerrain_shared_ptr terrain = scn_mngr->get_terrain();
		//adlDebug_renderer* db_renderer = &adlDebug_renderer::get();
		//adlInput* input = &adlInput::get();

		//int width = terrain->get_width();
		//int height = terrain->get_height();
		//selection_current_ = collision_point;
		//adlVec2_i32 quad_index1(selection_current_.x + 0.5 - width / 2, selection_current_.z + 0.5 - height / 2);
		//quad_index1 = -quad_index1;
		//quad_index1 = quad_index1.swap();

		//adlVec2_i32 quad_index2(selection_start_.x + 0.5 - width / 2, selection_start_.z + 0.5 - height / 2);
		//quad_index2 = -quad_index2;
		//quad_index2 = quad_index2.swap();

		//adlVec2_i32 quad_index(collision_point.x + 0.5 - width / 2, collision_point.z + 0.5 - height / 2);
		//quad_index = -quad_index;
		//quad_index = quad_index.swap();

		//if (input->get_mouse_down(ADL_BUTTON_LEFT))
		//{
		//	selection_state_ = true;
		//	selection_start_ = collision_point;
		//}

		//if (input->get_mouse_up(ADL_BUTTON_LEFT))
		//{
		//	selection_state_ = false;
		//	//terrain->edit_vertex(quad_index.x, quad_index.y);
		//	int x_min = quad_index1.x;
		//	int x_max = quad_index2.x;
		//	if (quad_index2.x < quad_index1.x)
		//	{
		//		x_min = quad_index2.x;
		//		x_max = quad_index1.x;
		//	}
		//	int y_min = quad_index1.y;
		//	int y_max = quad_index2.y;
		//	if (quad_index2.y < quad_index1.y)
		//	{
		//		y_min = quad_index2.y;
		//		y_max = quad_index1.y;
		//	}

		//	std::vector<std::pair<int, int>> vertices;
		//	for (int i = x_min; i <= x_max; i++)
		//	{
		//		for (int j = y_min; j <= y_max; j++)
		//		{
		//			vertices.push_back(std::make_pair(i, j));
		//		}
		//	}
		//	terrain->edit_vertices(vertices);
		//}

		//if (selection_state_)
		//{
		//	int x_min = quad_index1.x;
		//	int x_max = quad_index2.x;
		//	if (quad_index2.x < quad_index1.x)
		//	{
		//		x_min = quad_index2.x;
		//		x_max = quad_index1.x;
		//	}
		//	int y_min = quad_index1.y;
		//	int y_max = quad_index2.y;
		//	if (quad_index2.y < quad_index1.y)
		//	{
		//		y_min = quad_index2.y;
		//		y_max = quad_index1.y;
		//	}

		//	for (int i = x_min; i <= x_max; i++)
		//	{
		//		for (int j = y_min; j <= y_max; j++)
		//		{
		//			Vertex vertex = terrain->get_vertex_at_index(i, j);
		//			Vertex vertex1 = terrain->get_vertex_at_index(i + 1, j);
		//			Vertex vertex2 = terrain->get_vertex_at_index(i, j + 1);
		//			Vertex vertex3 = terrain->get_vertex_at_index(i + 1, j + 1);

		//			db_renderer->render_line3D(vertex.position, vertex1.position, 1.0f, adlColor::WHITE);
		//			db_renderer->render_line3D(vertex1.position, vertex3.position, 1.0f, adlColor::WHITE);
		//			db_renderer->render_line3D(vertex3.position, vertex2.position, 1.0f, adlColor::WHITE);
		//			db_renderer->render_line3D(vertex2.position, vertex.position, 1.0f, adlColor::WHITE);
		//		}
		//	}
		//}

		//Vertex vertex = terrain->get_vertex_at_index(quad_index.x, quad_index.y);
		//Vertex vertex1 = terrain->get_vertex_at_index(quad_index.x + 1, quad_index.y);
		//Vertex vertex2 = terrain->get_vertex_at_index(quad_index.x, quad_index.y + 1);
		//Vertex vertex3 = terrain->get_vertex_at_index(quad_index.x + 1, quad_index.y + 1);

		//db_renderer->render_line3D(vertex.position, vertex1.position, 1.0f, adlColor::WHITE);
		//db_renderer->render_line3D(vertex1.position, vertex3.position, 1.0f, adlColor::WHITE);
		//db_renderer->render_line3D(vertex3.position, vertex2.position, 1.0f, adlColor::WHITE);
		//db_renderer->render_line3D(vertex2.position, vertex.position, 1.0f, adlColor::WHITE);
	}

	virtual void on_mouse_collision_start(adlEntity_shared_ptr  entity)
	{
	}

private:
	bool selection_state_ = false;
	adlVec3 selection_start_;
	adlVec3 selection_current_;
};

#endif //physics_listener_h__