#ifndef IMovementBehaviour_h__
#define IMovementBehaviour_h__

#include "engine/adl_math/adlMatrix.h"

#include "game/Human.h"

class Human;

class IMovementBehaviour { 

public:

	//IMovementBehaviour();
	//~IMovementBehaviour();

	virtual void Move(/*adlVec3* destination*/) = 0;

private:

};

class WalkMovement: public IMovementBehaviour {

public:

	virtual void Move(/*adlVec3* destination*/);

};

class RunMovement : public IMovementBehaviour {

public:

	virtual void Move(/*adlVec3* destination*/);

};




#endif //IMovementBehaviour_h__
