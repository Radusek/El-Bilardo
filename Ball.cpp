#include "Ball.h"

//Konstruktor dla bialej bili
Ball::Ball() : R(RADIUS), half(false), dx(0.f), dy(0.f), life(true), isFake(false)
{
	circle = new CircleShape(R);
	circle->setOrigin(R, R);
	x = WHITEBALL_START_X * float(W);
	y = float(H) / 2.f;
	circle->setFillColor(Color::White);
}

//Konstruktor dla pozostalych bil
Ball::Ball(int i, int no, sf::Color clr[8]) : R(RADIUS), half(no < 7 ? false : true), dx(0.f), dy(0.f), life(true), isFake(false)
{
	circle = new CircleShape(R);
	circle->setOrigin(R, R);
	x = (1.f - WHITEBALL_START_X)*float(W) + (column(i) - 2)*float(sqrt(3))*R;
	y = float(H) / 2.f + column(i)*R - row(i)*2.f*R;
	circle->setFillColor(clr[no % 8]);

	if (half) {
		circle->setOutlineColor(Color::Black);
		circle->setOutlineThickness(R);
		const Vector2f scale(0.5f, 0.5f);
		circle->setScale(scale);
	}
}

int Ball::column(int n) {
	float i = 0; int x = 2;
	while (n > 0) {
		n -= x;
		x++; i++;
	}
	return int(i);
}

int Ball::row(int n) {
	int n0 = n;
	for (int i = 1; i <= column(n0); i++)
		n -= i;
	return n;
}

Ball::~Ball() {
	delete circle;
}