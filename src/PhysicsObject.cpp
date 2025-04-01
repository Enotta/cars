#include "PhysicObject.h"

bool PhysicsObject::IsBoundTouch(PhysicsObject* other)
{
	if (this->bBoxXR < other->bBoxXL || this->bBoxXL > other->bBoxXR) 
		return false;
	if (this->bBoxYU < other->bBoxYD || this->bBoxYD > other->bBoxYU) 
		return false;

	return true;
}

bool PhysicsObject::IsCollide(PhysicsObject* other) 
{
	return IsBoundTouch(other);
}