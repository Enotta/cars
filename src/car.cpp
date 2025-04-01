#include "car.h"

Car::Car() {};

Car::Car(float X, float Y, float Rotation, float Velocity) : x(X), y(Y), rot(Rotation), vel(Velocity) {}

void Car::SetCars(vector<Car*>* others) 
{
	if (cars)
	{
		cars->erase(find(cars->begin(), cars->end(), this));
	}
	cars = others;
	cars->push_back(this);
}

void Car::SetTrack(Track* map)
{
	track = map;
}

void Car::Tick(float secs) 
{
	float drot = wheelRot * vel / 10 * secs / (vel * vel / 5000 + 1);
	rot += drot;
	vel *= cos(drot);
	float velsec = vel * secs;
	x += cos(rot) * velsec;
	y += sin(rot) * velsec;
}

void Car::Tick(float secs, float rev, float steer)
{
	float NextStep = 100; float sped = speed;
	if (vel > 90 || vel < -90) 
	{
		NextStep *= 2;
		sped *= 0.25;
	}
	if (vel > 190 || vel < -190) 
	{
		NextStep *= 2;
		sped *= 0.25;
	}

	vel += secs * (rev * (NextStep-abs(vel)) * sped - 0.5f * vel);
	wheelRot = steer;
	Tick(secs);
}
