#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Track.h"
#include "car.h"
#include "LocalView.h"

using namespace std;
using namespace sf;

int main() {
	LocalView localView;

	RenderWindow window(VideoMode(800, 800), "Cars");
	window.setFramerateLimit(60);
	localView.setWindow(&window);

	View view;
	view.setSize(Vector2f(200.0, 200.0));
	localView.setView(&view);

	Car car;
	Track track;

	Event event;
	bool pairCreated = false;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Num0 && !pairCreated) {
					track = Track(0);
					car = Car((double)track.getStart()[0] * 40 + 20, (double)track.getStart()[1] * 40 + 20, 0.0, 0.0);
				}
				else if (event.key.code == Keyboard::Num1 && !pairCreated) {
					track = Track(1);
					car = Car((double)track.getStart()[0] * 40 + 20, (double)track.getStart()[1] * 40 + 20, 0.0, 0.0);
				}
				else if (event.key.code == Keyboard::Num2 && !pairCreated) {
					track = Track(2);
					car = Car((double)track.getStart()[0] * 40 + 20, (double)track.getStart()[1] * 40 + 20, 0.0, 0.0);
				}

				if (!pairCreated) {
					view.setCenter(car.GetPosX(), car.GetPosY());
					localView.setCar(&car);
					localView.setTrack(&track);
					pairCreated = true;
				}
			}
		}

		double rev = 0;
		double steer = 0;

		if (Keyboard::isKeyPressed(Keyboard::W) && pairCreated)
		{
			rev += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && pairCreated)
		{
			rev -= 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && pairCreated)
		{
			steer += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && pairCreated)
		{
			steer -= 1;
		}

		if (pairCreated) {
			car.Tick(1 / 60.0, rev, steer);
			localView.display();
		}
	}

	return 0;
}