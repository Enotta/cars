#include "car.h"

Car::Car() {};

Car::Car(double X, double Y, double Rotation, double Velocity) : x(X), y(Y), rot(Rotation), vel(Velocity) {}

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

void Car::Tick(double secs) 
{
	double drot = wheelRot * vel / 10 * secs / (vel * vel / 5000 + 1);
	rot += drot;
	vel *= cos(drot);
	double velsec = vel * secs;
	x += cos(rot) * velsec;
	y += sin(rot) * velsec;
}

void Car::Tick(double secs, double rev, double steer)
{
	double NextStep = 100; double sped = speed;
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

	vel += secs * (rev * (NextStep-abs(vel)) * sped - 0.5 * vel);
	wheelRot = steer;
	Tick(secs);
}