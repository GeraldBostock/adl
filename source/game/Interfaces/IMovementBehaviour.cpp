#include "IMovementBehaviour.h"

#include <iostream>


// IMovementBehaviour
/*IMovementBehaviour::IMovementBehaviour()
{

}

IMovementBehaviour::~IMovementBehaviour()
{

}*/

/*void IMovementBehaviour::Move(adlVec3 * destination)
{
	std::cout << "IMovementBehaviour::Move" << std::endl;

}*/


// WalkMovement
void WalkMovement::Move()
{
	std::cout << "WalkMovement::Move" << std::endl;
}

// RunMovement
void RunMovement::Move()
{
	std::cout << "RunMovement::Move" << std::endl;

}
