#include "YesNoWindow.h"

YesNoWindow::YesNoWindow()
{
	float width = 400.f, height = 300.f;

	font.loadFromFile("font/micross.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setCharacterSize(24);

	windowBase.setSize(Vector2f(width, height));
	windowBase.setFillColor(Color::Green);
	windowBase.setOrigin(width / 2, height / 2);
	windowBase.setPosition(W, H);

	windowBase.setOutlineThickness(3.f);
	windowBase.setOutlineColor(Color::Black);
}

YesNoWindow::~YesNoWindow()
{
}
