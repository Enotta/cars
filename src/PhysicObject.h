#pragma once
class PhysicsObject
{
protected:
	double bBoxXL = 0, bBoxXR = 0, bBoxYD = 0, bBoxYU = 0;
	bool IsBoundTouch(PhysicsObject* other);

public:
	virtual bool IsCollide(PhysicsObject* other);
};

