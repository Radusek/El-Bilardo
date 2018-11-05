#pragma once
struct Wall
{
	float sx, sy;
	float ex, ey;
	float radius;

	Wall(float s1, float s2, float e1, float e2, float r);
};