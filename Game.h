#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "const.h"
#include "Ball.h"
#include "Wall.h"
using namespace sf;

class Game {
public:
	sf::RenderWindow* window;

	sf::Font font;
	sf::Text text[TEXTS];

	Ball* whiteBall;
	std::vector<Ball*> balls;
	std::vector<Wall*> walls;
	std::vector<Ball*> fakeBalls;
	std::vector<std::pair<Ball*, Ball*>> collidingPairs;

	Color clr[8] = { YELLOW, BLUE, RED,	MAGENTA, ORANGE, GREEN, BROWN, BLACK };
	int order[BALLS] = { 9, 7, 12, 15, 8, 1, 6, 10, 3, 14, 11, 2, 13, 4, 5 };

	Texture t[GRAPHICS];
	Sprite sprites[GRAPHICS];

	RectangleShape bottomField;
	RectangleShape rightField;

	SoundBuffer buffer;
	Sound sound;

	bool player1Turn;
	bool player1HasHalfs;
	bool playersHaveColors;
	bool turnEnded;
	bool aiming;
	bool gameIsEnded;

	float fDist;
	float hitPower;
	Vector2f dirVect;

	int nBallsInThisTurn[2];
	int nBallsLeft[2];
	int nBlackHole[2];

	int winningPlayer;
	int* playerScore;

public:
	Game(sf::RenderWindow* wnd, int* pS);

	void cursorPosRelatedComputing(bool buttonRelease);
	void leftMouseButtonPress();
	void leftMouseButtonRelease();
	bool isColliding(Ball* a, Ball* b);
	void staticCollision();
	void dynamicCollision();
	void friction();
	void holeCheck();
	void gameUpdate();
	void showText();
	bool isTurnEnded();
	void endTurn();
	void positionTheStick();
	void gameDraw();
	void setWhiteBallSpeed(Vector2f vec);
	Vector2f getWhiteBallPosition();

	~Game();
};