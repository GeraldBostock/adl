#include "adlIPhysics.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class adlBullet_physics : public adlIPhysics
{
public:
	adlBullet_physics();
	virtual ~adlBullet_physics();

	virtual bool initialize() override;
	virtual void update(float dt) override;

	virtual void add_box(const adlVec3& dimensions, adlTransform initial_transform, adlActor_shared_ptr actor) override;
	virtual void add_sphere(float radius, adlTransform initial_transform, adlActor_shared_ptr actor) override;

	virtual void render_diagnostics() override;

private:
	btDynamicsWorld* dynamics_world_;
	btBroadphaseInterface* broadphase_;
	btCollisionDispatcher* dispatcher_;
	btConstraintSolver* solver_;
	btDefaultCollisionConfiguration* collision_configuration_;
};