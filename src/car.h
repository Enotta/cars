#pragma once
#include "Track.h"
#include "PhysicObject.h"
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Car : PhysicsObject
{
private:
	float x = 0, y = 0, vel = 0, rot = 0, wheelRot = 0, speed = 10;

	vector<Car*>* cars = nullptr;
	Track* track = nullptr;

public:
	float GetPosX() { return x; };
	float GetPosY() { return y; };

	Car();
	Car(float X, float Y, float Rotation, float Velocity = 0);

	void SetCars(vector<Car*>* others);
	void SetTrack(Track* map);

	void Tick(float secs);
	void Tick(float secs, float rev, float steer);
};

