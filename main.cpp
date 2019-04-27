#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "config.h"
#include "Game.h"
#include "Pipe.h"
#include "Bird.h"

using namespace std;
using namespace sf;


int main() {

	srand(time(NULL));

	Game game;
	game.createWindow();
	game.initGame();

	float deltaTime = 0.0f;
	Clock clock;

	while (game.window.isOpen()) {

		deltaTime = clock.restart().asSeconds();
		game.deltaTime = deltaTime;

		game.window.clear(Color::Black);

		Event event;
		while (game.window.pollEvent(event)) {

			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				game.window.close();

			if (event.type == Event::Resized) {
				float aspectRatio = (float)game.window.getSize().x / (float)game.window.getSize().y;
				game.view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
			}

		}

		game.update();

		game.window.setTitle("Current speed: " + to_string(game.viewSpeed) + "        Fps: " + to_string(1.0f / deltaTime));

		game.display();

	}

	return 0;
}