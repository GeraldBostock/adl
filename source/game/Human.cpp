#include "Human.h"

#include "engine/adl_entities/adlEntity_factory.h"

#include "engine/adlInput.h"

#include "game/Interfaces/IMovementBehaviour.h"

Human::Human() 
	: _movement(0)
{
	REGISTER_ACTOR(Human)
}

Human::~Human()
{

}

void Human::init() {

}
void Human::update(float dt) {

}


void Human::MoveTo()
{
	if (this->_movement)
	{
		this->_movement->Move();
	}
}

void Human::SetMovementBehaviour(IMovementBehaviour* m) {
	this->_movement = m;
}

void Human::deserialize(const rapidjson::Value& json_object)
{

}

