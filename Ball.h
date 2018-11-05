#pragma once
#include <SFML/Graphics.hpp>
#include "const.h"
using namespace sf;

struct Ball
{
	CircleShape* circle;
	float R;
	const bool half;
	bool life;
	bool isFake;
	float x, y, dx, dy;

	Ball();
	Ball(int i, int no, sf::Color clr[8]);

	int column(int n);
	int row(int n);
	
	~Ball();
};