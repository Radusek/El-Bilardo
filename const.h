#pragma once
#define M_PI 3.14159265358979323846f

#define PLAYER_1 0
#define PLAYER_2 1

#define FULL 0
#define HALF 1

#define FRAMERATE 240
#define OFFSET_X 59.f
#define OFFSET_Y 59.f
#define CENTRAL_HOLE_OFFSET 20.f
#define BALLS 15
#define WALLS 18
#define RADIUS 14.f
#define FRICTION 0.9976f
#define LINEAR_FRICTION 2000.f
#define HOLE_SIZE 20.f

#define HIT_BAR_WIDTH 40.f
#define HIT_BAR_HEIGHT 300.f
#define HIT_BAR_Y 250.f
#define HIT_BAR_OUTLINE 2.f

#define R_FIELD_OUTLINE 3.f

#define GRAPHICS 3

#define BACKGROUND 0
#define STICK 1
#define HELPER 2

#define WHITEBALL_START_X 0.275f
#define MIN_BALL_SPEED 0.00275f
#define MAX_BALL_SPEED 5.7f

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
#define BLUE Color(70, 70, 240, 255)
#define RED Color::Red
#define MAGENTA Color::Magenta
#define ORANGE Color(0xFF, 0x80, 0x00, 0xFF)
#define GREEN Color::Green
#define BROWN Color(0xA0, 0x20, 0x00, 0xFF)
#define BLACK Color::Black

#define LIGHT_GREY Color(200, 200, 200, 255)
#define LIGHT_GREEN Color(100, 175, 100, 255)

#define P1_TURN_COLOR Color(255, 150, 150, 255)
#define P2_TURN_COLOR Color(150, 150, 255, 255)

#define P1_WIN_COLOR Color(255, 100, 100, 255)
#define P2_WIN_COLOR Color(100, 100, 255, 255)

#define TURN_DURATION int(30e6)

#define ROUND false
#define MATCH true

enum TxtEnum{
	TurnInfo,
	Score,
	P1Score,
	Colon,
	P2Score,
	BallsThisTurn,
	BallsLeft,
	TimeLeft,
	EnumSize
};
#define TEXTS EnumSize

const unsigned int W = 1085, Wfield = 150, H = 600, Hfield = 80;


#define P1_1_X 66.f
#define P1_1_Y 28.f

#define P1_2_X 96.f
#define P1_2_Y 58.f

#define P1_3_X 515.f
#define P1_3_Y 58.f

#define P1_4_X 525.f
#define P1_4_Y 28.f


#define P2_1_X W - P1_1_X
#define P2_1_Y P1_1_Y

#define P2_2_X W - P1_2_X
#define P2_2_Y P1_2_Y

#define P2_3_X W - P1_3_X
#define P2_3_Y P1_3_Y

#define P2_4_X W - P1_4_X
#define P2_4_Y P1_4_Y


#define P3_1_X P1_1_X
#define P3_1_Y H - P1_1_Y

#define P3_2_X P1_2_X
#define P3_2_Y H - P1_2_Y

#define P3_3_X P1_3_X
#define P3_3_Y H - P1_3_Y

#define P3_4_X P1_4_X
#define P3_4_Y H - P1_4_Y


#define P4_1_X W - P1_1_X
#define P4_1_Y H - P1_1_Y

#define P4_2_X W - P1_2_X
#define P4_2_Y H - P1_2_Y

#define P4_3_X W - P1_3_X
#define P4_3_Y H - P1_3_Y

#define P4_4_X W - P1_4_X
#define P4_4_Y H - P1_4_Y




#define P5_1_X 28.f
#define P5_1_Y 65.f

#define P5_2_X 58.f
#define P5_2_Y 95.f

#define P5_3_X 58.f
#define P5_3_Y 505.f

#define P5_4_X 28.f
#define P5_4_Y 535.f


#define P6_1_X W - P5_1_X
#define P6_1_Y P5_1_Y

#define P6_2_X W - P5_2_X
#define P6_2_Y P5_2_Y

#define P6_3_X W - P5_3_X
#define P6_3_Y P5_3_Y

#define P6_4_X W - P5_4_X
#define P6_4_Y P5_4_Y