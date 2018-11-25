#include "App.h"



App::App() : window(VideoMode(W + Wfield, H + Hfield), "El Bilardo!", Style::Titlebar | Style::Close), playerScore{}
{
	window.setFramerateLimit(FRAMERATE);
	game = new Game(&window, playerScore);
	window.setKeyRepeatEnabled(false);
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
					if (game->gameIsEnded == false && game->gamePaused == false)
						game->leftMouseButtonPress();
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (game->gameIsEnded == false && game->gamePaused == false)
						game->leftMouseButtonRelease();
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == Keyboard::Space) {
					if (game->gameIsEnded) {
						delete game;
						game = new Game(&window, playerScore);
					}
					else
					{
						game->gamePaused = !(game->gamePaused);
						game->aiming = false;
						if(game->turnEnded)
							game->hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
						game->clock.restart();
					}
				}
				if (event.key.code == Keyboard::Escape) {
					if (game->ackWindowActive)
					{
						closeAckWindow();
						continue;
					}

					window.close();
				}
				if (event.key.code == Keyboard::R)
				{
					game->ackWindowActive = true;

					game->gamePaused = true;
					game->aiming = false;
				}
				if (event.key.code == Keyboard::Y)
				{
					if (game->ackWindowActive) 
						gameRestart(ROUND);
				}
				if (event.key.code == Keyboard::X)
				{
					if (game->ackWindowActive)
						gameRestart(MATCH);
				}
				if (event.key.code == Keyboard::N)
				{
					closeAckWindow();
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

void App::gameRestart(bool resetAll)
{
	game->ackWindowActive = false;
	delete game;
	game = new Game(&window, playerScore);

	if (resetAll) 
	{
		playerScore[PLAYER_1] = 0;
		playerScore[PLAYER_2] = 0;
	}
}

void App::closeAckWindow()
{
	game->ackWindowActive = false;

	game->gamePaused = false;
	if (game->turnEnded)
		game->hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
	game->clock.restart();
}


App::~App()
{
	delete game;
}