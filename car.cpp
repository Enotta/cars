#include "car.h"

Car::Car() {};

Car::Car(double X, double Y, double Rotation, double VelocityX = 0, double VelocityY = 0) : x(X), y(Y), rot(Rotation), velX(VelocityX), velY(VelocityY) {}

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
	if (track) 
	{
		
	}
	else 
	{
		throw new exception("There is no track!");
	}
}