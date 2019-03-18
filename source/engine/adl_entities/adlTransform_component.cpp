#include "adlTransform_component.h"

#include "engine/adl_math/adlMath.h"

adlTransform_component::adlTransform_component()
	:	transform_(adlTransform::identity())
{
	REGISTER_COMPONENT(adlTransform_component)
}

bool adlTransform_component::init(const rapidjson::Value& json_object)
{
	const rapidjson::Value& position_array = json_object["position"];
	const rapidjson::Value& rotation_array = json_object["rotation"];
	const rapidjson::Value& scale_array = json_object["scale"];

	rapidjson::Value::ConstValueIterator itr = position_array.Begin();

	const rapidjson::Value& position_x = *itr;
	const rapidjson::Value& position_y = *++itr;
	const rapidjson::Value& position_z = *++itr;
	transform_.o = adlVec3(position_x.GetFloat(), position_y.GetFloat(), position_z.GetFloat());

	itr = rotation_array.Begin();

	const rapidjson::Value& rotation_x = *itr;
	const rapidjson::Value& rotation_y = *++itr;
	const rapidjson::Value& rotation_z = *++itr;
	transform_.rot = adlVec3(rotation_x.GetFloat(), rotation_y.GetFloat(), rotation_z.GetFloat());

	itr = scale_array.Begin();

	const rapidjson::Value& scale_x = *itr;
	const rapidjson::Value& scale_y = *++itr;
	const rapidjson::Value& scale_z = *++itr;
	transform_.scale = adlVec3(scale_x.GetFloat(), scale_y.GetFloat(), scale_z.GetFloat());

	return true;
}

void adlTransform_component::destroy()
{

}

void adlTransform_component::editor()
{
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Position"))
	{
		ImGui::Text("Position(x,y,z)");

		std::string label = "##Position";

		float actorPos[3] = { transform_.o.x, transform_.o.y, transform_.o.z };
		ImGui::InputFloat3(label.data(), &actorPos[0], 2);
		transform_.o = adlVec3(actorPos[0], actorPos[1], actorPos[2]);
	}

	if (ImGui::CollapsingHeader("Rotation"))
	{
		ImGui::Text("Rotation(x,y,z)");

		std::string label = "##Rotation";

		float actorRot[3] = { adlMath::rad_to_deg(transform_.rot.x), adlMath::rad_to_deg(transform_.rot.y), adlMath::rad_to_deg(transform_.rot.z) };
		ImGui::InputFloat3(label.data(), &actorRot[0], 2);
		transform_.rot = adlVec3(adlMath::deg_to_rad(actorRot[0]), adlMath::deg_to_rad(actorRot[1]), adlMath::deg_to_rad(actorRot[2]));
	}

	if (ImGui::CollapsingHeader("Scale"))
	{
		ImGui::Text("Scale(x,y,z)");

		std::string label = "##ActorScale";

		float actorScale[3] = { transform_.scale.x, transform_.scale.y, transform_.scale.z };
		ImGui::InputFloat3(label.data(), &actorScale[0], 2);
		transform_.scale = adlVec3(actorScale[0], actorScale[1], actorScale[2]);
	}

	ImGui::Unindent();
}

void adlTransform_component::set_position(const adlVec3& position)
{
	transform_.o = position;
}

const adlVec3& adlTransform_component::get_position()
{
	return transform_.o;
}

const adlVec3& adlTransform_component::get_rotation()
{
	return transform_.rot;
}

void adlTransform_component::set_rotation(const adlVec3& rotation)
{
	transform_.rot = rotation;
}

const adlVec3& adlTransform_component::get_scale()
{
	return transform_.scale;
}

void adlTransform_component::set_scale(const adlVec3& scale)
{
	transform_.scale = scale;
}

adlTransform adlTransform_component::get_transform()
{
	return transform_;
}

void adlTransform_component::set_transform(const adlTransform& transform)
{
	transform_.o = transform.o;
	transform_.rot = transform.rot;
	transform_.scale = transform.scale;
}