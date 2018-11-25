#include "YesNoWindow.h"

YesNoWindow::YesNoWindow()
{
	float width = 600.f, height = 40.f;

	font.loadFromFile("font/micross.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setCharacterSize(24);

	windowBase.setSize(Vector2f(width, height));
	windowBase.setFillColor(Color(20, 200, 20, 255));
	windowBase.setOrigin(width / 2, height / 2);
	windowBase.setPosition(W / 2, H / 2);

	windowBase.setOutlineThickness(3.f);
	windowBase.setOutlineColor(Color::Black);

	text.setString("Y - Round restart\tX - Match restart\tN - Cancel");
	text.setOrigin(float(int(text.getLocalBounds().width / 2)), float(int(text.getLocalBounds().height / 2)) + 4.f);
	text.setPosition(W / 2, H / 2);
}

void YesNoWindow::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(windowBase);
	target.draw(text);
}

YesNoWindow::~YesNoWindow()
{
}
