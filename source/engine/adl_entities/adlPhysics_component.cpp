#include "adlPhysics_component.h"

#include "../adlScene_manager.h"
#include "adlRender_component.h"
#include "adlTransform_component.h"
#include "../adl_debug/adlLogger.h"

#define MAX_VELOCITY 7.5f
#define MAX_ANGULAR_VELOCITY 1.2f

adlPhysics_component::adlPhysics_component()
	: physics_(nullptr)
{
	REGISTER_COMPONENT(adlPhysics_component)

	acceleration_ = 0.0f;
	anguler_acceleration_ = 0.0f;

	max_velocity_ = MAX_VELOCITY;
	max_angular_velocity_ = MAX_ANGULAR_VELOCITY;

	shape_ = "box";
}

bool adlPhysics_component::init(const rapidjson::Value& json_object)
{
	const rapidjson::Value& shape_object = json_object["shape"];
	shape_ = shape_object.GetString();

	return true;
}

void adlPhysics_component::post_init()
{
	adlScene_manager* scene_manager = &adlScene_manager::get();
	physics_ = scene_manager->get_physics();

	if (owner)
	{
		std::shared_ptr<adlTransform_component> trans_comp;
		std::shared_ptr<adlRender_component> render_comp;
		if (owner->has_component("adlTransform_component"))
		{
			trans_comp = std::shared_ptr<adlTransform_component>(owner->get_component<adlTransform_component>("adlTransform_component"));
		}
		if (owner->has_component("adlRender_component"))
		{
			render_comp = std::shared_ptr<adlRender_component>(owner->get_component<adlRender_component>("adlRender_component"));
		}

		adlModel_shared_ptr model = render_comp->get_model();
		adlMesh_shared_ptr mesh = model->get_all_meshes()[0];

		if (shape_ == "box")
		{
			adlVec3 dims = mesh->get_bb_dimensions();

			physics_->add_box(dims, trans_comp->get_transform(), owner);
		}
		else if (shape_ == "sphere")
		{
			physics_->add_box(1, trans_comp->get_transform(), owner);
		}
	}
}

void adlPhysics_component::update(float fps)
{
	std::shared_ptr<adlTransform_component> trans_comp;
	if (owner->has_component("adlTransform_component"))
	{
		trans_comp = std::shared_ptr<adlTransform_component>(owner->get_component<adlTransform_component>("adlTransform_component"));
		adlTransform transform = trans_comp->get_transform();

		if (acceleration_ != 0)
		{
			float acc_this_frame = acceleration_ / 1000.0f * fps;

			adlVec3 velocity = physics_->get_velocity(owner);
			//float velocity_scalar = velocity.length();

			adlVec3 direction = transform.rot;
			physics_->apply_force(direction, acc_this_frame, owner);
		}

		if (anguler_acceleration_ != 0)
		{
			float angular_acc_this_frame = anguler_acceleration_ / 1000.f * fps;
			physics_->apply_torque(adlVec3(0, 1, 0), angular_acc_this_frame, owner);
		}
	}
	else
	{
		adlLogger* logger = &adlLogger::get();
		logger->log_info("Physics entity does not have a transform component");

		return;
	}
}

void adlPhysics_component::destroy()
{
	physics_->remove_entity(owner);
}

void adlPhysics_component::set_position(const adlVec3& position)
{
	std::shared_ptr<adlTransform_component> trans_comp;
	if (owner->has_component("adlTransform_component"))
	{
		trans_comp = std::shared_ptr<adlTransform_component>(owner->get_component<adlTransform_component>("adlTransform_component"));
		adlTransform transform = trans_comp->get_transform();

		trans_comp->set_position(position);
		physics_->kinematic_move(trans_comp->get_transform(), owner);
	}
	else
	{
		adlLogger* logger = &adlLogger::get();
		logger->log_info("Physics entity does not have a transform component");

		return;
	}
}

void adlPhysics_component::apply_force(const adlVec3& direction, float newtons)
{
	physics_->apply_force(direction, newtons, owner);
}