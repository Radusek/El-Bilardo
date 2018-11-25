#pragma once
#include <SFML/Graphics.hpp>
#include "const.h"

using namespace sf;

struct YesNoWindow
{
public:
	RectangleShape windowBase;
	Font font;
	Text text;

public:
	YesNoWindow();
	~YesNoWindow();
};

