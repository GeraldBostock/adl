#ifndef adl_terrain_editor_h__
#define adl_terrain_editor_h__

#include "engine/adlPhysics_observer.h"

#include <vector>
#include <utility>
#include <set>

class adlTerrain_editor : public adlPhysics_observer
{
public:
	adlTerrain_editor();
	~adlTerrain_editor();

	void update();
	void set_open(bool open);

	void on_collision_start(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) override {}
	void on_collision_end(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) override {}
	void on_terrain_collision_start(adlEntity_shared_ptr entity, const adlVec3& collision_point) override {}
	void on_terrain_collision_end(adlEntity_shared_ptr entity) override {}
	void on_terrain_mouse_ray_collision(const adlVec3& collision_point) override;
	void on_mouse_collision_start(adlEntity_shared_ptr  entity) override {}

private:
	adlVec2_i32 get_grid_index(const adlVec3& collision_point, int terrain_width, int terrain_height);
	void start_tile_selection_state(const adlVec3& collision_point, int width, int height);
	void update_selection_state(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain);
	void end_tile_selection_state(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain);
	const std::set<std::pair<int, int>> get_selected_vertices(const adlVec2_i32& current_tile_index, adlTerrain_shared_ptr terrain);
	
	adlVec2_i32 selection_start_index_;
	bool selection_state_;

	bool is_editor_open_;

	bool elevate_;
	bool lower_;
	bool smooth_;

	bool texture1_;
	bool texture2_;
	bool texture3_;
	bool texture4_;
};

#endif //adl_terrain_h__