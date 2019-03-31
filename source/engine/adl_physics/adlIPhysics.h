#ifndef adl_iphysics_h__
#define adl_iphysics_h__

#include "../adl_math/adlMath.h"
#include "../adl_math/adlRay.h"
#include "../adlShared_types.h"
#include "../adlPhysics_subject.h"

#include <vector>

class adlIPhysics : public adlPhysics_subject
{
public:
	virtual bool initialize() = 0;
	virtual void sync_physics_to_rendering() = 0;
	virtual void update(float dt) = 0;
	virtual void sync_scene() = 0;

	virtual void add_box(const adlVec3& dimensions, adlTransform initial_transform, adlEntity_shared_ptr entity) = 0;
	virtual void add_sphere(float radius, adlTransform initial_transform, adlEntity_shared_ptr entity) = 0;
	virtual void add_terrain(const std::vector<float>& heightfield) = 0;
	virtual void add_static_plane() = 0;

	virtual void remove_entity(adlEntity_shared_ptr entity) = 0;

	virtual void apply_force(const adlVec3& direction, float newtons, adlEntity_shared_ptr entity) = 0;
	virtual void apply_torque(const adlVec3& direction, float magnitude, adlEntity_shared_ptr entity) = 0;
	virtual void kinematic_move(adlTransform transform, adlEntity_shared_ptr entity) = 0;
	virtual void stop(adlEntity_shared_ptr entity) = 0;

	virtual void set_static(adlEntity_shared_ptr entity, bool is_static) = 0;

	virtual const adlTransform& get_transform(adlEntity_shared_ptr entity) = 0;

	virtual adlVec3 get_velocity(adlEntity_shared_ptr entity) = 0;
	virtual void set_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity) = 0;
	virtual adlVec3 get_angular_velocity(adlEntity_shared_ptr entity) = 0;
	virtual void set_angular_velocity(adlEntity_shared_ptr entity, const adlVec3& velocity) = 0;

	virtual std::vector<adlEntity_shared_ptr> get_all_raycast_hits(adlRay ray) = 0;
	virtual adlEntity_shared_ptr get_first_raycast_hit(adlRay ray) = 0;

	virtual void render_diagnostics() = 0;
};

#endif //adl_iphysics_h__