#pragma once
#define M_PI 3.14159265358979323846f

#define PLAYER_1 0
#define PLAYER_2 1

#define FULL 0
#define HALF 1

#define FRAMERATE 300
#define OFFSET_X 59.f
#define OFFSET_Y 59.f
#define CENTRAL_HOLE_OFFSET 20.f
#define BALLS 15
#define RADIUS 14.f
#define FRICTION 0.9975f
#define HOLE_SIZE 20.f

#define GRAPHICS 3

#define BACKGROUND 0
#define STICK 1
#define HELPER 2

#define WHITEBALL_START_X 0.275f
#define MIN_BALL_SPEED 0.04f
#define MAX_BALL_SPEED 5.5f

#define MAX_AIMING_DISTANCE 100.f

#define STICK_ORIGIN_X 640.f
#define STICK_ORIGIN_Y 16.f
#define STICK_MOVEMENT_MULTIPLIER (MAX_AIMING_DISTANCE / MAX_BALL_SPEED)

#define MAX_HIT_SOUND_VOLUME 30.f
#define SPEED_VOLUME_FACTOR 0.875f
#define BASE_VOLUME_FACTOR (1.f - SPEED_VOLUME_FACTOR)

#define UNSET -1
#define TEXT_SIZE 60
#define N_HOLES 6

#define YELLOW Color::Yellow
#define BLUE Color::Blue
#define RED Color::Red
#define MAGENTA Color::Magenta
#define ORANGE Color(0xFF, 0x80, 0x00, 0xFF)
#define GREEN Color::Green
#define BROWN Color(0x80, 0x10, 0x00, 0xFF)
#define BLACK Color::Black

#define P1_TURN_COLOR Color(255, 150, 150, 255)
#define P2_TURN_COLOR Color(150, 150, 255, 255)

#define P1_WIN_COLOR Color(255, 100, 100, 255)
#define P2_WIN_COLOR Color(100, 100, 255, 255)

enum TxtEnum{
	TurnInfo,
	Score,
	P1Score,
	Colon,
	P2Score,
	BallsThisTurn,
	BallsLeft,
	EnumSize
};
#define TEXTS EnumSize

const unsigned int W = 1085, Wfield = 150, H = 600, Hfield = 80;