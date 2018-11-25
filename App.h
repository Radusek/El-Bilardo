#pragma once
#include "Game.h"

class App
{
private:
	RenderWindow window;
	Game* game;

	int playerScore[2];

public:
	App();
	
	void run();
	void gameRestart(bool resetAll);
	void closeAckWindow();

	~App();
};