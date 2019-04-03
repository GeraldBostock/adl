#ifndef adl_physics_component_h__
#define adl_physics_component_h__

#include "adlEntity_component.h"
#include "../adl_physics/adlIPhysics.h"

class adlPhysics_component : public adlEntity_component
{
public:
	adlPhysics_component();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float fps) override;
	virtual void destroy() override;
	virtual void editor() override;

	void set_position(const adlVec3& position);
	const adlVec3& get_position();
	void set_velocity(const adlVec3& velocity);
	const adlVec3& get_velocity();

	void apply_force(const adlVec3& direction, float newtons);
	void apply_torque(const adlVec3& direction, float newtons);
	void stop();

	void set_static(bool is_static);

	virtual void on_mouse_hover_start() {}
	virtual void on_mouse_hover_end() {}
	virtual void under_mouse() {}

private:
	std::shared_ptr<adlIPhysics> physics_;

	std::string shape_;

	bool is_static_;

	float acceleration_, anguler_acceleration_;
	float max_velocity_, max_angular_velocity_;
};

#endif //adl_physics_component_h__