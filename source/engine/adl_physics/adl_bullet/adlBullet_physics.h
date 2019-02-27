#ifndef adl_bullet_physics_h__
#define adl_bullet_physics_h__

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#include "../adlIPhysics.h"
#include "adlBullet_debug_drawer.h"

#include <map>
#include <set>

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

class adlBullet_physics : public adlIPhysics
{
public:
	adlBullet_physics() {};
	virtual ~adlBullet_physics();

	virtual bool initialize() override;
	virtual void sync_physics_to_rendering() override;
	virtual void update(float dt) override;
	virtual void sync_scene() override;

	virtual void add_box(const adlVec3& dimensions, adlTransform initial_transform, adlActor_shared_ptr actor) override;
	virtual void add_sphere(float radius, adlTransform initial_transform, adlActor_shared_ptr actor) override;
	virtual void add_terrain(const std::vector<float>& heightfield) override;
	virtual void add_static_plane() override;
	virtual void remove_collision_object(btCollisionObject* obj);

	//Do not call these functions multiple times for the same ray.
	virtual std::vector<adlActor_shared_ptr> get_all_raycast_hits(adlRay ray) override;
	virtual adlActor_shared_ptr get_first_raycast_hit(adlRay ray) override;

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

	typedef std::map<adlActor_shared_ptr, btRigidBody*> Actor_to_body_map;
	Actor_to_body_map actor_to_body_map_;
	btRigidBody* get_body(adlActor_shared_ptr actor);

	typedef std::map<btRigidBody const*, adlActor_shared_ptr> Body_to_actor_map;
	Body_to_actor_map body_to_actor_map_;
	adlActor_shared_ptr get_actor(btRigidBody const* body)
	{
		return body_to_actor_map_[body];
	}

	typedef std::pair<btRigidBody const*, btRigidBody const*> Collision_pair;
	typedef std::set<Collision_pair> Collision_pairs;
	Collision_pairs previous_tick_collision_pairs_;

	std::vector<btRigidBody const*> previous_mouse_ray_collisions_;

	void add_shape(adlActor_shared_ptr actor, btCollisionShape* shape, float mass, const std::string& material);
};

#endif //adl_bullet_physics_h__