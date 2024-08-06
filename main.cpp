#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 800), "Cars");
	window.setFramerateLimit(60);
	SoundBuffer buffer;
	Sound sound;
	if (!buffer.loadFromFile("music.mp3")) return -1;
	sound.setBuffer(buffer);
	sound.play();
	Event event;


	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}
	}

	return 0;
}