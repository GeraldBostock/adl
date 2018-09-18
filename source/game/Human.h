#ifndef Human_h__
#define Human_h__

#include "engine/adl_entities/adlActor.h"

#include "game/Interfaces/IMovementBehaviour.h"

class IMovementBehaviour;

class Human : public adlActor { 

public:

	Human();
	~Human();

	void init() override;
	void update(float dt) override;

	void MoveTo();
	void SetMovementBehaviour(IMovementBehaviour* m);

	void deserialize(const rapidjson::Value& json_object) override;

private:

	IMovementBehaviour * _movement;

};

#endif //Human_h__
