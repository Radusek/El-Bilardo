#pragma once
#include <SFML/Graphics.hpp>
#include "const.h"

using namespace sf;

struct YesNoWindow : public Drawable
{
public:
	RectangleShape windowBase;
	Font font;
	Text text;

public:
	YesNoWindow();

	void draw(RenderTarget& target, RenderStates states) const;

	~YesNoWindow();
};

