#include "adlBullet_physics.h"
#include "../../adlMemory.h"

#include "../../adl_debug/adlLogger.h"
#include "../../adl_entities/adlActor.h"
#include "../../adl_math/adlMouse_picker.h"
#include "../../adl_renderer/adlDebug_renderer.h"
#include "../../adl_resource/adlResource_manager.h"

#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

struct Actor_motion_state : public btMotionState
{
	adlTransform world_to_position_transform;
	adlMat4 matrix;
	adlVec3 scale_;

	Actor_motion_state(const adlVec3& position, const adlVec3& rotation, const adlVec3& scale)
		: scale_(scale)
	{
		world_to_position_transform.o = position;
		world_to_position_transform.rot = rotation;
		world_to_position_transform.scale = scale;
		matrix = world_to_position_transform.get_transformation_matrix();
	}

	virtual void getWorldTransform(btTransform& worldTrans) const
	{
		worldTrans = adlTransform_to_btTransform(matrix);
	}

	virtual void setWorldTransform(const btTransform& worldTrans)
	{
		world_to_position_transform.o = btTransform_to_adlTransform(worldTrans, scale_).o;
		world_to_position_transform.rot = btTransform_to_adlTransform(worldTrans, scale_).rot;
		world_to_position_transform.scale = btTransform_to_adlTransform(worldTrans, scale_).scale;
		matrix = world_to_position_transform.get_transformation_matrix();
	}
};

adlBullet_physics::~adlBullet_physics()
{
	for (int i = dynamics_world_->getNumCollisionObjects() - 1; i >= 0; --i)
	{
		btCollisionObject* const obj = dynamics_world_->getCollisionObjectArray()[i];
		remove_collision_object(obj);
	}

	ADL_DELETE(debug_drawer_);
	ADL_DELETE(dynamics_world_);
	ADL_DELETE(solver_);
	ADL_DELETE(broadphase_);
	ADL_DELETE(dispatcher_);
	ADL_DELETE(collision_configuration_);
}

bool adlBullet_physics::initialize()
{
	collision_configuration_	= ADL_NEW(btDefaultCollisionConfiguration);
	dispatcher_					= ADL_NEW(btCollisionDispatcher, collision_configuration_);
	broadphase_					= ADL_NEW(btDbvtBroadphase);
	solver_						= ADL_NEW(btSequentialImpulseConstraintSolver);
	dynamics_world_				= ADL_NEW(btDiscreteDynamicsWorld, dispatcher_, broadphase_, solver_, collision_configuration_);
	debug_drawer_				= ADL_NEW(adlBullet_debug_drawer);
	debug_drawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

	adlLogger* logger = &adlLogger::get();

	if (!collision_configuration_ || !dispatcher_ || !broadphase_ || !solver_ || !dynamics_world_ || !debug_drawer_)
	{
		logger->log_error("Bullet Physics initialization failed!");
	}

	dynamics_world_->setDebugDrawer(debug_drawer_);
	dynamics_world_->setInternalTickCallback(bullet_internal_tick_callback);
	dynamics_world_->setWorldUserInfo(this);

	logger->log_info("Bullet Physics initialized successfully");

	return true;
}

void adlBullet_physics::sync_physics_to_rendering()
{
	for (Actor_to_body_map::const_iterator it = actor_to_body_map_.begin(); it != actor_to_body_map_.end(); ++it)
	{
		Actor_motion_state const * const actor_motion_state = static_cast<Actor_motion_state*>(it->second->getMotionState());
		adl_assert(actor_motion_state);

		adlTransform transform = it->first->get_transform();
		btTransform bt_transform = adlTransform_to_btTransform(transform.get_transformation_matrix());

		if (it->first && actor_motion_state)
		{
			it->second->setWorldTransform(bt_transform);
		}
	}
}

void adlBullet_physics::update(float dt)
{
	dynamics_world_->stepSimulation(dt / 1000.f, 4);

	adlMouse_picker* mouse_picker = &adlMouse_picker::get();
	adlRay mouse_ray = mouse_picker->get_mouse_ray();
	adlVec3 origin = mouse_ray.get_origin();
	adlVec3 direction = mouse_ray.get_direction();
	adlVec3 ray_limit = origin + (direction * 200);

	btVector3 from(origin.x, origin.y, origin.z);
	btVector3 to(ray_limit.x, ray_limit.y, ray_limit.z);

	btCollisionWorld::ClosestRayResultCallback closest_results(from, to);
	closest_results.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;

	dynamics_world_->rayTest(from, to, closest_results);

	if (closest_results.hasHit())
	{
		btRigidBody const * const hit_body = static_cast<btRigidBody const *>(closest_results.m_collisionObject);
		adlActor_shared_ptr actor = body_to_actor_map_[hit_body];

		if (actor == nullptr)
		{
			btVector3 hit_point = closest_results.m_hitPointWorld;
			adlVec3 adl_hit_point(hit_point.x(), hit_point.y(), hit_point.z());
			for (int i = 0; i < observers_.size(); i++)
			{
				observers_.at(i)->on_terrain_mouse_ray_collision(adl_hit_point);
			}
		}
	}
}

void adlBullet_physics::sync_scene()
{
	for (Actor_to_body_map::const_iterator it = actor_to_body_map_.begin(); it != actor_to_body_map_.end(); ++it)
	{
		Actor_motion_state const * const actor_motion_state = static_cast <Actor_motion_state*>(it->second->getMotionState());
		adl_assert(actor_motion_state);

		if (it->first && actor_motion_state)
		{
			it->first->set_transform(actor_motion_state->world_to_position_transform);
		}
	}
}

void adlBullet_physics::add_sphere(float radius, adlTransform initial_transform, adlActor_shared_ptr actor)
{
	btSphereShape* const collision_shape = ADL_NEW(btSphereShape, radius);
	
	add_shape(actor, collision_shape, 10, "naber");
}

void adlBullet_physics::add_static_plane()
{
	btStaticPlaneShape* const plane = ADL_NEW(btStaticPlaneShape, btVector3(0, 1, 0), btScalar(-10));
	adlTransform transform = adlTransform::identity();
	transform.o = adlVec3(0, -20, 0);
	transform.rot = adlVec3(0, 0, 0);
	transform.scale = adlVec3(1);
	Actor_motion_state* const new_motion_state = ADL_NEW(Actor_motion_state, transform.o, transform.rot, transform.scale);
	btRigidBody::btRigidBodyConstructionInfo rb_info(0, new_motion_state, plane);

	btRigidBody* const body = ADL_NEW(btRigidBody, rb_info);
	dynamics_world_->addRigidBody(body);
	body->setGravity(btVector3(0, 0, 0));
}

void adlBullet_physics::add_box(const adlVec3& dimensions, adlTransform initial_transform, adlActor_shared_ptr actor)
{
	btBoxShape* const collision_shape = ADL_NEW(btBoxShape, btVector3(dimensions.x, dimensions.y, dimensions.z));
	add_shape(actor, collision_shape, 10, "asd");
}

void adlBullet_physics::add_terrain(const std::vector<float>& heightfield)
{
	float min = -5000.0f;
	float max = 5000.0f;

	for (std::vector<float>::const_iterator it = heightfield.begin(); it != heightfield.end(); ++it)
	{
		if (min > *it)
		{
			min = *it;
		}

		if (max < *it)
		{
			max = *it;
		}
	}

	btHeightfieldTerrainShape* const terrain_shape = ADL_NEW(btHeightfieldTerrainShape, 128, 128, &heightfield[0], btScalar(1.0f), btScalar(min), btScalar(max), 1, PHY_FLOAT, true);

	adlTransform transform = adlTransform::identity();
	transform.o = adlVec3(0, 0, 0);
	transform.rot = adlVec3(0, 0, 0);
	transform.scale = adlVec3(1);
	Actor_motion_state* const new_motion_state = ADL_NEW(Actor_motion_state, transform.o, transform.rot, transform.scale);
	btRigidBody::btRigidBodyConstructionInfo rb_info(0, new_motion_state, terrain_shape);

	btRigidBody* const body = ADL_NEW(btRigidBody, rb_info);
	dynamics_world_->addRigidBody(body);
	body->setGravity(btVector3(0, 0, 0));
	terrain_body_ = body;
}

void adlBullet_physics::add_shape(adlActor_shared_ptr actor, btCollisionShape* shape, float mass, const std::string& material)
{
	adl_assert(actor);
	adl_assert(actor_to_body_map_.find(actor) == actor_to_body_map_.end());

	adlTransform transform = actor->get_transform();
	transform.o = actor->get_transform().o;

	btVector3 localInertia(0.f, 0.f, 0.f);
	if (mass > 0.f)
		shape->calculateLocalInertia(mass, localInertia);

	Actor_motion_state* const new_motion_state = ADL_NEW(Actor_motion_state, actor->get_position(), transform.rot, transform.scale);
	btRigidBody::btRigidBodyConstructionInfo rb_info(mass, new_motion_state, shape, localInertia);

	btRigidBody* const body = ADL_NEW(btRigidBody, rb_info);

	dynamics_world_->addRigidBody(body);

	if (!actor->get_gravity())
	{
		body->setGravity(btVector3(0, 0, 0));
	}

	actor_to_body_map_[actor] = body;
	body_to_actor_map_[body] = actor;
}

void adlBullet_physics::bullet_internal_tick_callback(btDynamicsWorld* const world, btScalar const time_step)
{
	adl_assert(world);
	adl_assert(world->getWorldUserInfo());

	adlBullet_physics * const bullet_physics = static_cast<adlBullet_physics*>(world->getWorldUserInfo());

	Collision_pairs current_tick_collision_pairs;
	btDispatcher* const dispatcher = world->getDispatcher();

	adlLogger* logger = &adlLogger::get();

	for (int manifold_index = 0; manifold_index < dispatcher->getNumManifolds(); ++manifold_index)
	{
		btPersistentManifold const * const manifold = dispatcher->getManifoldByIndexInternal(manifold_index);
		adl_assert(manifold);

		if (!manifold)
		{
			continue;
		}

		btRigidBody const * const body0 = static_cast<btRigidBody const *>(manifold->getBody0());
		btRigidBody const * const body1 = static_cast<btRigidBody const *>(manifold->getBody1());

		const bool swapped = body0 > body1;

		btRigidBody const * const sorted_body_a = swapped ? body1 : body0;
		btRigidBody const * const sorted_body_b = swapped ? body0 : body1;

		Collision_pair const current_pair = std::make_pair(sorted_body_a, sorted_body_b);

		//current_tick_collision_pairs.insert(current_pair);

		adlActor_shared_ptr actor0 = bullet_physics->get_actor(sorted_body_a);
		adlActor_shared_ptr actor1 = bullet_physics->get_actor(sorted_body_b);

		const int contact_count = manifold->getNumContacts();
		bool bodies_colliding = false;
		adlVec3 collision_point;
		for (int j = 0; j < contact_count; ++j)
		{
			btManifoldPoint const& pt = manifold->getContactPoint(j);
			if (pt.getDistance() < 0.0f)
			{
				bodies_colliding = true;
				btVector3 a = pt.getPositionWorldOnA();
				btVector3 b = pt.getPositionWorldOnB();

				btVector3 c = (a + b) / 2;
				collision_point.x = c.x();
				collision_point.y = c.y();
				collision_point.z = c.z();
			}
		}

		if (bodies_colliding)
		{
			current_tick_collision_pairs.insert(current_pair);
			if (bullet_physics->previous_tick_collision_pairs_.find(current_pair) == bullet_physics->previous_tick_collision_pairs_.end())
			{
				if (actor0 != nullptr && actor1 != nullptr)
				{
					for (int i = 0; i < bullet_physics->observers_.size(); i++)
					{
						bullet_physics->observers_.at(i)->on_collision_start(actor0, actor1);
					}
				}
				if (actor0 == nullptr || actor1 == nullptr)
				{
					
					adlActor_shared_ptr actor = actor0 == nullptr ? actor1 : actor0;
					for (int i = 0; i < bullet_physics->observers_.size(); i++)
					{
						bullet_physics->observers_.at(i)->on_terrain_collision_start(actor, collision_point);
					}
				}
			}
		}
	}

	Collision_pairs removed_collision_pairs;

	std::set_difference(bullet_physics->previous_tick_collision_pairs_.begin(),
		bullet_physics->previous_tick_collision_pairs_.end(),
		current_tick_collision_pairs.begin(), current_tick_collision_pairs.end(),
		std::inserter(removed_collision_pairs, removed_collision_pairs.begin()));

	for (Collision_pairs::const_iterator it = removed_collision_pairs.begin(), end = removed_collision_pairs.end(); it != end; ++it)
	{
		btRigidBody const * const body0 = it->first;
		btRigidBody const * const body1 = it->second;

		adlActor_shared_ptr actor0 = bullet_physics->get_actor(body0);
		adlActor_shared_ptr actor1 = bullet_physics->get_actor(body1);

		if (actor0 != nullptr && actor1 != nullptr)
		{
			for (int i = 0; i < bullet_physics->observers_.size(); i++)
			{
				bullet_physics->observers_.at(i)->on_collision_end(actor0, actor1);
			}
		}
		else
		{
			adlActor_shared_ptr actor = actor0 == nullptr ? actor1 : actor0;
			for (int i = 0; i < bullet_physics->observers_.size(); i++)
			{
				bullet_physics->observers_.at(i)->on_terrain_collision_end(actor);
			}
		}
	}

	bullet_physics->previous_tick_collision_pairs_ = current_tick_collision_pairs;
}

void adlBullet_physics::remove_collision_object(btCollisionObject* obj)
{

}

std::vector<adlActor_shared_ptr> adlBullet_physics::get_all_raycast_hits(adlRay ray)
{
	adlVec3 origin = ray.get_origin();
	adlVec3 direction = ray.get_direction();
	adlVec3 ray_limit = origin + (direction * 100);

	btVector3 from(origin.x, origin.y, origin.z);
	btVector3 to(ray_limit.x, ray_limit.y, ray_limit.z);

	btCollisionWorld::AllHitsRayResultCallback all_results(from, to);
	all_results.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

	adl_assert(dynamics_world_);

	std::vector<adlActor_shared_ptr> actors;

	if (dynamics_world_)
	{
		dynamics_world_->rayTest(from, to, all_results);
		adlDebug_renderer* db_renderer = &adlDebug_renderer::get();

		for (int i = 0; i < all_results.m_hitFractions.size(); i++)
		{
			btVector3 p = from.lerp(to, all_results.m_hitFractions[i]);
			btRigidBody const * const hit_body = static_cast<btRigidBody const *>(all_results.m_collisionObjects[i]);
			adlActor_shared_ptr hit_actor = body_to_actor_map_[hit_body];

			if (hit_actor)
			{
				actors.push_back(hit_actor);
				adlResource_manager* adl_rm = &adlResource_manager::get();
				hit_actor->set_material(adl_rm->get_material("gold"));
			}
		}
	}

	return actors;
}

adlActor_shared_ptr adlBullet_physics::get_first_raycast_hit(adlRay ray)
{
	adlVec3 origin = ray.get_origin();
	adlVec3 direction = ray.get_direction();
	adlVec3 ray_limit = origin + (direction * 100);

	btVector3 from(origin.x, origin.y, origin.z);
	btVector3 to(ray_limit.x, ray_limit.y, ray_limit.z);

	btCollisionWorld::ClosestRayResultCallback closest_results(from, to);
	closest_results.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;

	dynamics_world_->rayTest(from, to, closest_results);

	if (closest_results.hasHit())
	{
		btRigidBody const * const hit_body = static_cast<btRigidBody const *>(closest_results.m_collisionObject);
		adlActor_shared_ptr actor = body_to_actor_map_[hit_body];

		return actor;
	}

	return nullptr;
}

void adlBullet_physics::render_diagnostics()
{
	dynamics_world_->debugDrawWorld();
}