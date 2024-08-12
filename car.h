#pragma once
#include "Track.h"
#include "PhysicObject.h"
#include <vector>

using namespace std;

class Car : PhysicsObject
{
private:
	double x = 0, y = 0, velX = 0, velY = 0, rot = 0;

	vector<Car*>* cars = nullptr;
	Track* track;

public:
	Car();
	Car(double X, double Y, double Rotation, double VelocityX = 0, double VelocityY = 0);

	void SetCars(vector<Car*>* others);
	void SetTrack(Track* map);

	void Tick(double secs);
	void Tick(double secs, double rev, double steer);
};

