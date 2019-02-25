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
	virtual void update(float dt) = 0;
	virtual void sync_scene() = 0;

	virtual void add_box(const adlVec3& dimensions, adlTransform initial_transform, adlActor_shared_ptr actor) = 0;
	virtual void add_sphere(float radius, adlTransform initial_transform, adlActor_shared_ptr actor) = 0;
	virtual void add_terrain(const std::vector<float>& heightfield) = 0;
	virtual void add_static_plane() = 0;

	virtual std::vector<adlActor_shared_ptr> get_all_raycast_hits(adlRay ray) = 0;
	virtual adlActor_shared_ptr get_first_raycast_hit(adlRay ray) = 0;

	virtual void render_diagnostics() = 0;
};

#endif //adl_iphysics_h__