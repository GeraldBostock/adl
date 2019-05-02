#ifndef adl_scene_manager_h__
#define adl_scene_manager_h__

#include "adl_entities/adlEntity.h"
#include "adl_renderer/adlCamera.h"
#include "engine/adl_resource/adlScene.h"
#include "adlShared_types.h"
#include "adl_physics/adl_bullet/adlBullet_physics.h"
#include <vector>

class adlScene_manager
{
public:

	friend class adlEntity_factory;

	static adlScene_manager& get()
	{
		static adlScene_manager instance;
		return instance;
	}

	void update(float dt);
	void render();

	adlScene_shared_ptr create_empty_scene(const std::string& scene_name);
	void set_active_scene(adlScene_shared_ptr scene);

	void add_plane();

	void set_physics(adlIPhysics* physics);

	void add_to_scene(adlEntity_shared_ptr entity);
	void addToScene(adlEntity_shared_ptr entity);

	void set_sun(adlEntity_shared_ptr sun);

	void set_camera(adlCamera* camera);

	adlTerrain_shared_ptr get_terrain();
	void set_terrain(adlTerrain_shared_ptr terrain);
	void set_terrain(const std::vector<float>& heightfield);
	void add_physics_observer(adlPhysics_observer* observer)
	{
		physics_->addObserver(observer);
	}

	std::shared_ptr<adlIPhysics> get_physics()
	{
		return physics_;
	}
	
	adlEntity_shared_ptr add_entity_to_scene(const std::string& entity_name);

	std::vector<adlEntity_shared_ptr>& get_all_entities();
	adlScene_shared_ptr get_active_scene();

	adlCamera* getCamera();
	adlCamera* get_camera();

private:

	void light_component_added(adlEntity_shared_ptr entity, const std::string& component_name);
	void light_component_removed(adlEntity_shared_ptr entity, const std::string& component_name);

	std::vector<adlEntity_shared_ptr> entities_;

	std::vector<adlEntity_shared_ptr> point_light_components_;
	std::vector<adlEntity_shared_ptr> sun_components_;

	adlCamera* camera_;
	std::shared_ptr<adlIPhysics> physics_;

	adlScene_shared_ptr active_scene_ = nullptr;

	adlScene_manager();
};

#endif // adl_scene_manager_h_