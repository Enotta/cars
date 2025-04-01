#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/car.h"

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode({800, 800}), "Cars");
	window.setFramerateLimit(60);

	Music music;
	music.openFromFile("resources/music/music.mp3");
	music.setVolume(4.0f);
	music.play();

	float rev, steer;

	Car car;

	CircleShape circle(5);

	while (window.isOpen())
	{
		window.clear();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		rev = 0;
		steer = 0;

		if (Keyboard::isKeyPressed(Keyboard::Key::W))
		{
			rev += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
		{
			rev -= 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			steer += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			steer -= 1;
		}

		car.Tick(1 / 144.0f, rev, steer);

		circle.setPosition({car.GetPosX(), car.GetPosY()});

		window.draw(circle);
		window.display();
	}

	return 0;
}
