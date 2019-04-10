#ifndef adl_bullet_physics_h__
#define adl_bullet_physics_h__


#pragma warning(push, 0)			
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"	
#pragma warning(pop)

#include "../adlIPhysics.h"
#include "adlBullet_debug_drawer.h"

#include <map>
#include <set>

class adlBullet_physics : public adlIPhysics
{
public:
	adlBullet_physics();
	virtual ~adlBullet_physics();

	virtual bool initialize() override;
	virtual void sync_physics_to_rendering() override;
	virtual void update(float dt) override;
	virtual void sync_scene() override;

	virtual void add_box(const adlVec3& dimensions, adlTransform initial_transform, adlEntity_shared_ptr entity) override;
	virtual void add_sphere(float radius, adlTransform initial_transform, adlEntity_shared_ptr entity) override;
	virtual void add_terrain(const std::vector<float>& heightfield, int width, int height) override;
	virtual void add_static_plane() override;
	virtual void remove_collision_object(btCollisionObject* obj);

	virtual void remove_entity(adlEntity_shared_ptr entity) override;

	virtual void apply_force(const adlVec3& direction, float newtons, adlEntity_shared_ptr entity) override;
	virtual void apply_torque(const adlVec3& direction, float magnitude, adlEntity_shared_ptr entity) override;
	virtual void kinematic_move(adlTransform transform, adlEntity_shared_ptr entity) override;
	virtual void stop(adlEntity_shared_ptr entity) override;

	virtual void set_static(adlEntity_shared_ptr entity, bool is_static) override;

	virtual const adlTransform& get_transform(adlEntity_shared_ptr entity) override;

	virtual adlVec3 get_velocity(adlEntity_shared_ptr entity) override;
	virtual void set_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity) override;
	virtual adlVec3 get_angular_velocity(adlEntity_shared_ptr entity) override;
	virtual void set_angular_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity) override;

	//Do not call these functions multiple times for the same ray.
	virtual std::vector<adlEntity_shared_ptr> get_all_raycast_hits(adlRay ray) override;
	virtual adlEntity_shared_ptr get_first_raycast_hit(adlRay ray) override;

	virtual void render_diagnostics() override;

protected:
	static void bullet_internal_tick_callback(btDynamicsWorld* const world, btScalar const time_step);

private:
	btDynamicsWorld* dynamics_world_;
	btBroadphaseInterface* broadphase_;
	btCollisionDispatcher* dispatcher_;
	btConstraintSolver* solver_;
	btDefaultCollisionConfiguration* collision_configuration_;
	btIDebugDraw* debug_drawer_;
	btRigidBody* terrain_body_;

	//Entity to body map
	typedef std::map<adlEntity_shared_ptr, btRigidBody*> Entity_to_body_map;
	Entity_to_body_map entity_to_body_map_;
	btRigidBody* get_body(adlEntity_shared_ptr entity)
	{
		return entity_to_body_map_[entity];
	}

	//Body to entity map
	typedef std::map<btRigidBody const*, adlEntity_shared_ptr> Body_to_entity_map;
	Body_to_entity_map body_to_entity_map_;
	adlEntity_shared_ptr get_entity(btRigidBody const* body)
	{
		return body_to_entity_map_[body];
	}

	typedef std::pair<btRigidBody const*, btRigidBody const*> Collision_pair;
	typedef std::set<Collision_pair> Collision_pairs;
	Collision_pairs previous_tick_collision_pairs_;

	std::vector<adlEntity_shared_ptr> previous_mouse_ray_collisions_;

	void add_shape(adlEntity_shared_ptr actor, btCollisionShape* shape, float mass, const std::string& material);
};

#endif //adl_bullet_physics_h__