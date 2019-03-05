#include "adlTransform_component.h"

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