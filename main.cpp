#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Track.h"

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 800), "Cars");

	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Num0) {
					Track track0(0);
					track0.draw(window);
				}
				else if (event.key.code == Keyboard::Num1) {
					Track track1(1);
					track1.draw(window);
				}
				else if (event.key.code == Keyboard::Num2) {
					Track track2(2);
					track2.draw(window);
				}

				window.display();
			}
		}
	}

	return 0;
}