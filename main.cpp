#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Track.h"

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 800), "Cars");
	window.setFramerateLimit(1);
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Num0) {
					system("cls");
					Track track0(0);
					track0.print();
				}
				else if (event.key.code == Keyboard::Num1) {
					system("cls");
					Track track1(1);
					track1.print();
				}
				else if (event.key.code == Keyboard::Num2) {
					system("cls");
					Track track2(2);
					track2.print();
				}
			}
		}

		window.display();
	}

	return 0;
}