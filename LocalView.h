#include "SFML/Graphics.hpp"
#include "Car.h"
#include "Track.h"

#pragma once
class LocalView
{
private:
	Car* car;
	Track* track;
	RenderWindow* window;
	View* view;

public:
	LocalView(): car(nullptr), track(nullptr), window(nullptr), view(nullptr) {}
	LocalView(Car* c, Track* t, RenderWindow* w, View* v): car(c), track(t), window(w), view(v) {}

	void setCar(Car* c);
	void setTrack(Track* t);
	void setWindow(RenderWindow* w);
	void setView(View* );

	void display();
};

