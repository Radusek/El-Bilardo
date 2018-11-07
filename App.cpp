#include "App.h"



App::App() : window(VideoMode(W + Wfield, H + Hfield), "El Bilardo!", Style::Titlebar | Style::Close), playerScore{}
{
	window.setFramerateLimit(FRAMERATE);
	game = new Game(&window, playerScore);
}

void App::run()
{
	while (window.isOpen())
	{
		//listening for input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					game->leftMouseButtonPress();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game->leftMouseButtonRelease();
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					if (game->gameIsEnded) {
						delete game;
						game = new Game(&window, playerScore);
					}
				}
			}
		}

		//computing
		game->gameUpdate();

		//drawing
		window.clear();
		game->gameDraw();
		window.display();
	}
}


App::~App()
{
	delete game;
}