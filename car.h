#pragma once
#include "Track.h"
#include "PhysicObject.h"
#include <vector>

using namespace std;

class Car : PhysicsObject
{
private:
	double x = 0, y = 0, vel = 0, rot = 0, wheelRot = 0, speed = 10;

	vector<Car*>* cars = nullptr;
	Track* track = nullptr;

public:
	double GetPosX() { return x; };
	double GetPosY() { return y; };
	double GetRotation() { return rot; }

	Car();
	Car(double X, double Y, double Rotation, double Velocity = 0);

	void operator=(const Car& other);

	void setCars(vector<Car*>* others);
	void setTrack(Track* map);

	void Tick(double secs);
	void Tick(double secs, double rev, double steer);
};

