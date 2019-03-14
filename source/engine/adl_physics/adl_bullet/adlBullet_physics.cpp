#include "adlBullet_physics.h"
#include "../../adlMemory.h"

#include "../../adl_debug/adlLogger.h"
#include "../../adl_entities/adlActor.h"
#include "../../adl_math/adlMouse_picker.h"
#include "../../adl_renderer/adlDebug_renderer.h"
#include "../../adl_resource/adlResource_manager.h"
#include "../../adl_entities/adlTransform_component.h"

#pragma warning(push, 0)
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#pragma warning(pop)

static adlTransform btTransform_to_adlTransform(btTransform const & bttransform, adlVec3 scale)
{
	adlMat4 matrix = adlMat4::identity();

	btMatrix3x3 const & bulletRotation = bttransform.getBasis();
	btVector3 const & bulletPosition = bttransform.getOrigin();
	btQuaternion q = bttransform.getRotation();

	adlVec3 rot;

	double sinr_cosp = 2.0 * (q.w() * q.x() + q.y() * q.z());
	double cosr_cosp = 1.0 - 2.0 * (q.x() * q.x() + q.y() * q.y());
	rot.x = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w() * q.y() - q.z() * q.x());
	if (fabs(sinp) >= 1)
		rot.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		rot.y = asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = +2.0 * (q.w() * q.z() + q.x() * q.y());
	double cosy_cosp = +1.0 - 2.0 * (q.y() * q.y() + q.z() * q.z());
	rot.z = atan2(siny_cosp, cosy_cosp);


	matrix.vectors.a.x = bulletRotation[0][0];
	matrix.vectors.a.y = bulletRotation[1][0];
	matrix.vectors.a.z = bulletRotation[2][0];

	matrix.vectors.b.x = bulletRotation[0][1];
	matrix.vectors.b.y = bulletRotation[1][1];
	matrix.vectors.b.z = bulletRotation[2][1];

	matrix.vectors.c.x = bulletRotation[0][2];
	matrix.vectors.c.y = bulletRotation[1][2];
	matrix.vectors.c.z = bulletRotation[2][2];

	adlVec3 o(bulletPosition.x(), bulletPosition.y(), bulletPosition.z());
	adlTransform transform(o, rot, scale);

	return transform;
}

static btTransform adlTransform_to_btTransform(adlMat4 const & matrix)
{
	btMatrix3x3 bulletRotation;

	bulletRotation[0][0] = matrix.vectors.a.x;
	bulletRotation[1][0] = matrix.vectors.a.y;
	bulletRotation[2][0] = matrix.vectors.a.z;

	bulletRotation[0][1] = matrix.vectors.b.x;
	bulletRotation[1][1] = matrix.vectors.b.y;
	bulletRotation[2][1] = matrix.vectors.b.z;

	bulletRotation[0][2] = matrix.vectors.c.x;
	bulletRotation[1][2] = matrix.vectors.c.y;
	bulletRotation[2][2] = matrix.vectors.c.z;

	btVector3 bulletPosition(matrix.vectors.d.x, matrix.vectors.d.y, matrix.vectors.d.z);

	return btTransform(bulletRotation, bulletPosition);
}

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
	for (Entity_to_body_map::const_iterator it = entity_to_body_map_.begin(); it != entity_to_body_map_.end(); ++it)
	{
		Actor_motion_state const * const actor_motion_state = static_cast<Actor_motion_state*>(it->second->getMotionState());
		adl_assert(actor_motion_state);

		adlEntity_shared_ptr entity = it->first;
		std::shared_ptr<adlTransform_component> trans_comp;
		if (entity->has_component("adlTransform_component"))
		{
			trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
		}
		else
		{
			continue;
		}

		adlTransform transform = trans_comp->get_transform();
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
		adlEntity_shared_ptr entity = body_to_entity_map_[hit_body];

		if (entity == nullptr)
		{
			btVector3 hit_point = closest_results.m_hitPointWorld;
			adlVec3 adl_hit_point(hit_point.x(), hit_point.y(), hit_point.z());
			for (unsigned int i = 0; i < observers_.size(); i++)
			{
				observers_.at(i)->on_terrain_mouse_ray_collision(adl_hit_point);
			}
		}
	}
}

void adlBullet_physics::sync_scene()
{
	for (Entity_to_body_map::const_iterator it = entity_to_body_map_.begin(); it != entity_to_body_map_.end(); ++it)
	{
		Actor_motion_state const * const actor_motion_state = static_cast <Actor_motion_state*>(it->second->getMotionState());
		adl_assert(actor_motion_state);

		if (it->first && actor_motion_state)
		{
			adlEntity_shared_ptr entity = it->first;
			std::shared_ptr<adlTransform_component> trans_comp;
			if (entity->has_component("adlTransform_component"))
			{
				trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
				trans_comp->set_transform(actor_motion_state->world_to_position_transform);
			}
			else
			{
				continue;
			}
		}
	}
}

void adlBullet_physics::add_sphere(float radius, adlTransform initial_transform, adlEntity_shared_ptr entity)
{
	btSphereShape* const collision_shape = ADL_NEW(btSphereShape, radius);
	
	add_shape(entity, collision_shape, 10, "naber");
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

void adlBullet_physics::add_box(const adlVec3& dimensions, adlTransform initial_transform, adlEntity_shared_ptr entity)
{
	btBoxShape* const collision_shape = ADL_NEW(btBoxShape, btVector3(dimensions.x, dimensions.y, dimensions.z));
	add_shape(entity, collision_shape, 10, "asd");
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

void adlBullet_physics::add_shape(adlEntity_shared_ptr entity, btCollisionShape* shape, float mass, const std::string& material)
{
	adl_assert(entity);
	adl_assert(entity_to_body_map_.find(entity) == entity_to_body_map_.end());

	std::shared_ptr<adlTransform_component> trans_comp;
	if (entity->has_component("adlTransform_component"))
	{
		trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
	}
	else
	{
		return;
	}

	adlTransform transform = trans_comp->get_transform();
	transform.o = trans_comp->get_transform().o;

	btVector3 localInertia(0.f, 0.f, 0.f);
	if (mass > 0.f)
		shape->calculateLocalInertia(mass, localInertia);

	Actor_motion_state* const new_motion_state = ADL_NEW(Actor_motion_state, trans_comp->get_position(), transform.rot, transform.scale);
	btRigidBody::btRigidBodyConstructionInfo rb_info(mass, new_motion_state, shape, localInertia);

	btRigidBody* const body = ADL_NEW(btRigidBody, rb_info);

	dynamics_world_->addRigidBody(body);

	entity_to_body_map_[entity] = body;
	body_to_entity_map_[body] = entity;
}

void adlBullet_physics::bullet_internal_tick_callback(btDynamicsWorld* const world, btScalar const time_step)
{
	adl_assert(world);
	adl_assert(world->getWorldUserInfo());

	adlBullet_physics * const bullet_physics = static_cast<adlBullet_physics*>(world->getWorldUserInfo());

	Collision_pairs current_tick_collision_pairs;
	btDispatcher* const dispatcher = world->getDispatcher();

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

		adlEntity_shared_ptr entity0 = bullet_physics->get_entity(sorted_body_a);
		adlEntity_shared_ptr entity1 = bullet_physics->get_entity(sorted_body_b);

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
				if (entity0 != nullptr && entity1 != nullptr)
				{
					for (unsigned int i = 0; i < bullet_physics->observers_.size(); i++)
					{
						bullet_physics->observers_.at(i)->on_collision_start(entity0, entity1);
					}
				}
				if (entity0 == nullptr || entity1 == nullptr)
				{
					
					adlEntity_shared_ptr entity = entity0 == nullptr ? entity1 : entity0;
					for (unsigned int i = 0; i < bullet_physics->observers_.size(); i++)
					{
						bullet_physics->observers_.at(i)->on_terrain_collision_start(entity, collision_point);
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

		adlEntity_shared_ptr entity0 = bullet_physics->get_entity(body0);
		adlEntity_shared_ptr entity1 = bullet_physics->get_entity(body1);

		if (entity0 != nullptr && entity1 != nullptr)
		{
			for (unsigned int i = 0; i < bullet_physics->observers_.size(); i++)
			{
				bullet_physics->observers_.at(i)->on_collision_end(entity0, entity1);
			}
		}
		else
		{
			adlEntity_shared_ptr entity = entity0 == nullptr ? entity1 : entity0;
			for (unsigned int i = 0; i < bullet_physics->observers_.size(); i++)
			{
				bullet_physics->observers_.at(i)->on_terrain_collision_end(entity);
			}
		}
	}

	bullet_physics->previous_tick_collision_pairs_ = current_tick_collision_pairs;
}

void adlBullet_physics::remove_entity(adlEntity_shared_ptr entity)
{
	if (btRigidBody * const body = get_body(entity))
	{
		// destroy the body and all its components
		remove_collision_object(body);
		entity_to_body_map_.erase(entity);
		body_to_entity_map_.erase(body);
	}
}

void adlBullet_physics::remove_collision_object(btCollisionObject* obj)
{
	// first remove the object from the physics sim
	dynamics_world_->removeCollisionObject(obj);

	// then remove the pointer from the ongoing contacts list
	for (Collision_pairs::iterator it = previous_tick_collision_pairs_.begin(); it != previous_tick_collision_pairs_.end(); )
	{
		Collision_pairs::iterator next = it;
		++next;

		if (it->first == obj || it->second == obj)
		{
			//SendCollisionPairRemoveEvent(it->first, it->second);
			previous_tick_collision_pairs_.erase(it);
		}

		it = next;
	}

	// if the object is a RigidBody (all of ours are RigidBodies, but it's good to be safe)
	if (btRigidBody * const body = btRigidBody::upcast(obj))
	{
		// delete the components of the object
		delete body->getMotionState();
		delete body->getCollisionShape();
		delete body->getUserPointer();
		delete body->getUserPointer();

		for (int ii = body->getNumConstraintRefs() - 1; ii >= 0; --ii)
		{
			btTypedConstraint * const constraint = body->getConstraintRef(ii);
			dynamics_world_->removeConstraint(constraint);
			delete constraint;
		}
	}

	delete obj;
}

void adlBullet_physics::apply_force(const adlVec3& direction, float newtons, adlEntity_shared_ptr entity)
{
	if (btRigidBody * const body = get_body(entity))
	{
		body->setActivationState(DISABLE_DEACTIVATION);

		btVector3 const force(direction.x * newtons, direction.y * newtons, direction.z * newtons);

		body->applyCentralImpulse(force);
	}
}

void adlBullet_physics::apply_torque(const adlVec3& direction, float magnitude, adlEntity_shared_ptr entity)
{
	if (btRigidBody * const body = get_body(entity))
	{
		body->setActivationState(DISABLE_DEACTIVATION);

		btVector3 const torque(direction.x * magnitude, direction.y * magnitude, direction.z * magnitude);

		body->applyTorqueImpulse(torque);
	}
}

void adlBullet_physics::kinematic_move(adlTransform transform, adlEntity_shared_ptr entity)
{
	if (btRigidBody * const body = get_body(entity))
	{
		body->setActivationState(DISABLE_DEACTIVATION);

		// warp the body to the new position
		body->setWorldTransform(adlTransform_to_btTransform(transform.get_transformation_matrix()));
	}
}

std::vector<adlEntity_shared_ptr> adlBullet_physics::get_all_raycast_hits(adlRay ray)
{
	adlVec3 origin = ray.get_origin();
	adlVec3 direction = ray.get_direction();
	adlVec3 ray_limit = origin + (direction * 100);

	btVector3 from(origin.x, origin.y, origin.z);
	btVector3 to(ray_limit.x, ray_limit.y, ray_limit.z);

	btCollisionWorld::AllHitsRayResultCallback all_results(from, to);
	all_results.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

	adl_assert(dynamics_world_);

	std::vector<adlEntity_shared_ptr> actors;

	if (dynamics_world_)
	{
		dynamics_world_->rayTest(from, to, all_results);

		for (int i = 0; i < all_results.m_hitFractions.size(); i++)
		{
			btVector3 p = from.lerp(to, all_results.m_hitFractions[i]);
			btRigidBody const * const hit_body = static_cast<btRigidBody const *>(all_results.m_collisionObjects[i]);
			adlEntity_shared_ptr hit_actor = body_to_entity_map_[hit_body];
		}
	}

	return actors;
}

adlEntity_shared_ptr adlBullet_physics::get_first_raycast_hit(adlRay ray)
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
		adlEntity_shared_ptr actor = body_to_entity_map_[hit_body];

		return actor;
	}

	return nullptr;
}

adlVec3 adlBullet_physics::get_velocity(adlEntity_shared_ptr entity)
{
	btRigidBody* body = get_body(entity);
	adl_assert(body);

	if (!body)
	{
		return adlVec3();
	}

	btVector3 bt_velocity = body->getLinearVelocity();

	return adlVec3(bt_velocity.x(), bt_velocity.y(), bt_velocity.z());
}
void adlBullet_physics::set_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity)
{
	btRigidBody * body = get_body(entity);

	adl_assert(body);

	if (!body)
	{
		return;
	}
	btVector3 bt_velocity(velocity.x, velocity.y, velocity.z);
	body->setLinearVelocity(bt_velocity);
}

adlVec3 adlBullet_physics::get_angular_velocity(adlEntity_shared_ptr entity)
{
	btRigidBody* body = get_body(entity);
	adl_assert(body);

	if (!body)
	{
		return adlVec3();
	}

	btVector3 bt_velocity = body->getAngularVelocity();

	return adlVec3(bt_velocity.x(), bt_velocity.y(), bt_velocity.z());
}

void adlBullet_physics::set_angular_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity)
{
	btRigidBody * body = get_body(entity);

	adl_assert(body);

	if (!body)
	{
		return;
	}
	btVector3 bt_velocity(velocity.x, velocity.y, velocity.z);
	body->setAngularVelocity(bt_velocity);
}

void adlBullet_physics::render_diagnostics()
{
	dynamics_world_->debugDrawWorld();
}