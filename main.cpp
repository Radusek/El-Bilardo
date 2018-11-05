#include <iostream>
#include <cmath>
#include <list>
#include "const.h"
#include "Ball.h"
#include "Game.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(W, H + Hfield), "El Bilardo!", Style::Titlebar | Style::Close);

	window.setFramerateLimit(FRAMERATE);
	//window.setMouseCursorVisible(false);
	Game game(&window);

	while (window.isOpen())
	{
		//listening for input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					game.leftMouseButtonPress();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game.leftMouseButtonRelease();
				}
			}
		}

		//computing
		game.gameUpdate();

		//drawing
		window.clear();
		game.gameDraw();
		window.display();
	}

	return 0;
}