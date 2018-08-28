#include "adlScene_manager.h"

#include "adl_renderer/adlRender_manager.h"


adlScene_manager::adlScene_manager()
{
}

void adlScene_manager::update(float dt)
{
	for (auto entity : entities_)
	{
		entity.update(dt);
	}

	for (auto actor : actors_)
	{
		actor->update(dt);
	}

	for (auto sun : suns_)
	{
		sun->update(dt);
	}

	for (auto light : point_lights_)
	{
		light->update(dt);
	}
}

void adlScene_manager::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	for (auto actor : actors_)
	{
		renderer->render(actor);
	}

	for (auto sun : suns_)
	{
		renderer->render(sun);
	}

	for (auto light : point_lights_)
	{
		renderer->render(light);
	}
}

void adlScene_manager::add_to_scene(adlEntity entity)
{
	entity.init();
	entities_.push_back(entity);
}

void adlScene_manager::addToScene(adlEntity entity)
{
	add_to_scene(entity);
}

void adlScene_manager::add_to_scene(adlActor_shared_ptr actor)
{
	actor->init();
	actors_.push_back(actor);
}

void adlScene_manager::addToScene(adlActor_shared_ptr actor)
{
	add_to_scene(actor);
}

void adlScene_manager::add_sun_to_scene(adlSun_shared_ptr sun)
{
	sun->init();
	suns_.push_back(sun);
	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_light(sun);
}

void adlScene_manager::addSunToScene(adlSun_shared_ptr sun)
{
	add_sun_to_scene(sun);
}

void adlScene_manager::spawn_actor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	actor->init();
	actors_.push_back(actor);
	actor->set_position(position);
	actor->set_rotation(rotation);
	actor->set_scale(scale);
}

void adlScene_manager::spawnActor(adlActor_shared_ptr actor, adlVec3 position, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	spawn_actor(actor, position, rotation, scale);
}

void adlScene_manager::addPointLightToScene(adlPoint_light_shared_ptr point_light)
{
	add_point_light_scene(point_light);
}

void adlScene_manager::add_point_light_scene(adlPoint_light_shared_ptr point_light)
{
	point_light->init();
	point_lights_.push_back(point_light);

	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_point_light(point_light);
}