#include "adlScene.h"

#include "engine/adl_entities/adlActor.h"
#include "engine/adl_entities/adlPoint_light.h"
#include "engine/adl_entities/adlSun.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_entities/adlEntity.h"
#include "engine/adl_resource/adlTerrain.h"
#include "engine/adl_math/adlMouse_picker.h"
#include "engine/adl_math/adlRay_cast_callback.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

adlScene::adlScene(const std::string& scene_name)
	:	scene_name_(scene_name),
		sun_(nullptr),
		camera_(nullptr),
		terrain_(nullptr),
		cube_map_(nullptr)
{
	//boxShape = new rp3d::SphereShape(1.0f);

	/*adlPhysics* physics = &adlPhysics::get();
	collision_world_ = physics->create_new_world();*/
}

adlScene::adlScene(const std::string& scene_name, std::vector<adlEntity_shared_ptr> entities, std::vector<adlActor_shared_ptr> actors, std::vector<adlPoint_light_shared_ptr> point_lights)
	:	entities_(entities),
		actors_(actors),
		point_lights_(point_lights),
		scene_name_(scene_name),
		sun_(nullptr),
		camera_(nullptr),
		terrain_(nullptr),
		cube_map_(nullptr)
{
	//boxShape = new rp3d::SphereShape(1.0f);

	/*adlPhysics* physics = &adlPhysics::get();
	collision_world_ = physics->create_new_world();*/
}


adlScene::~adlScene()
{
}

void adlScene::update(float dt)
{
	//adlMouse_picker* mp = &adlMouse_picker::get();
	//adlRay ray = mp->get_mouse_ray();
	//adlVec3 origin = ray.get_origin();

	//float x = origin.x + (ray.get_direction().x * 500);
	//float y = origin.y + (ray.get_direction().y * 500);
	//float z = origin.z + (ray.get_direction().z * 500);

	//rp3d::Vector3 startPoint(origin.x, origin.y, origin.z);
	//rp3d::Vector3 endPoint(x, y, z);

	//// Create the ray 
	//rp3d::Ray rpdRay(startPoint, endPoint);

	for (auto entity : entities_)
	{
		entity->update(dt);
	}

	/*for (auto actor : actors_)
	{
		adlResource_manager* rm = &adlResource_manager::get();
		actor->set_material(rm->get_material("bronze"));

		actor->update(dt);
	}*/

	camera_->update(dt);
	sun_->update(dt);

	for (auto light : point_lights_)
	{
		light->update(dt);
	}

	//RaycastCallback callbackObject;

	//// Raycast test 
	//world_.raycast(rpdRay, &callbackObject);
	//rp3d::CollisionBody* body = callbackObject.get_body();
	//if (body != nullptr)
	//{
	//	adlResource_manager* rm = &adlResource_manager::get();
	//	adlActor_shared_ptr actor = bodies_[body];
	//	actor->set_material(rm->get_material("copper"));
	//}
}

void adlScene::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	renderer->set_lights(point_lights_);
	renderer->set_camera(camera_);

	if (cube_map_ != nullptr)
	{
		renderer->render(cube_map_);
	}

	for (auto actor : actors_)
	{
		renderer->render(actor);
	}

	renderer->render(sun_);

	for (auto light : point_lights_)
	{
		renderer->render(light);
	}

	renderer->render(terrain_);
}

void adlScene::spawn_entity(adlEntity_shared_ptr entity)
{
	entity->init();
	entities_.push_back(entity);
}

void adlScene::spawn_actor(adlActor_shared_ptr actor, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	actor->init();
	actor->set_position(position);
	actor->set_rotation(rotation);
	actor->set_scale(scale);
	actors_.push_back(actor);

	//if (actor->get_model() != nullptr)
	//{
	//	rp3d::Vector3 initPosition(position.x, position.y, position.z);
	//	rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
	//	rp3d::Transform transform(initPosition, initOrientation);

	//	// Create a collision body in the world 
	//	rp3d::CollisionBody* body;
	//	body = world_.createCollisionBody(transform);

	//	std::vector<adlMesh_shared_ptr> meshes = actor->get_model()->get_all_meshes();

	//	for (auto mesh : meshes)
	//	{
	//		adlBounding_box bb = mesh->get_bounding_box();
	//		float x = std::abs(bb.up_left_back().x - bb.up_right_back().x);
	//		if (x == 0.0f)
	//		{
	//			x = 0.1f;
	//		}
	//		float y = std::abs(bb.bottom_left_back().y - bb.up_left_back().y);
	//		if (y == 0.0f)
	//		{
	//			y = 0.1f;
	//		}
	//		float z = std::abs(bb.bottom_left_front().z - bb.bottom_left_back().z);
	//		if (z == 0.0f)
	//		{
	//			z = 0.1f;
	//		}

	//		const rp3d::Vector3 halfExtents(x / 2.0f, y / 2.0f, z / 2.0f);
	//		rp3d::ProxyShape* proxyShape;
	//		rp3d::Transform identity;
	//		proxyShape = body->addCollisionShape(boxShape, identity);
	//		proxy_array_.push_back(proxyShape);
	//	}

	//	bodies_[body] = actor;
	//	bodies_array_.push_back(body);
	//}
}

void adlScene::spawn_point_light(adlPoint_light_shared_ptr point_light, adlVec3 position/* = adlVec3(0.0f)*/, adlVec3 rotation/* = adlVec3(0.0f)*/, adlVec3 scale/* = adlVec3(1.0f)*/)
{
	point_light->init();
	point_light->set_position(position);
	point_light->set_rotation(rotation);
	point_light->set_scale(scale);
	point_lights_.push_back(point_light);
}

void adlScene::set_sun(adlSun_shared_ptr sun)
{
	sun_ = sun;
}

void adlScene::set_camera(adlCamera* camera)
{
	camera_ = camera;
}

void adlScene::set_terrain(adlTerrain_shared_ptr terrain)
{
	terrain_ = terrain;
}

void adlScene::set_cube_map(adlCube_map_shared_ptr cube_map)
{
	cube_map_ = cube_map;
}

adlCamera* adlScene::get_camera()
{
	return camera_;
}

adlSun_shared_ptr adlScene::get_sun()
{
	return sun_;
}

adlCube_map_shared_ptr adlScene::get_cube_map()
{
	return cube_map_;
}

std::vector<adlEntity_shared_ptr>& adlScene::get_all_entities()
{
	return entities_;
}

std::vector<adlActor_shared_ptr>& adlScene::get_all_actors()
{
	return actors_;
}

std::vector<adlPoint_light_shared_ptr>& adlScene::get_all_point_lights()
{
	return point_lights_;
}

const std::string& adlScene::get_name()
{
	return scene_name_;
}

adlTerrain_shared_ptr adlScene::get_terrain()
{
	return terrain_;
}
