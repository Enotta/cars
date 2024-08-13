#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "car.h"

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 800), "Cars");
	window.setFramerateLimit(144);
	Event event;

	double rev, steer;

	Car car;

	CircleShape circle(5);

	while (window.isOpen())
	{
		window.clear();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		rev = 0;
		steer = 0;

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			rev += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) 
		{
			rev -= 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			steer += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			steer -= 1;
		}

		car.Tick(1 / 144.0, rev, steer);

		circle.setPosition(car.GetPosX(), car.GetPosY());

		window.draw(circle);
		window.display();
	}

	return 0;
}