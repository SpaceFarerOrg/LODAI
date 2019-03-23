#include "ActorControllerSystem/Public/Controller.h"

//------------------------------------------------------------

CController::CController()
	: MoveFunction()
{
}

//------------------------------------------------------------

void CController::SetMovementSpeed(float InMovementSpeed)
{
	MovementSpeed = InMovementSpeed;
}

//------------------------------------------------------------

void CController::AttachMoveFunction(MoveFunc InMoveFunction)
{
	MoveFunction = InMoveFunction;
}

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
