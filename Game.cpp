#include "Game.h"

Game::Game(RenderWindow* wnd, int* pS) : window(wnd), player1Turn((pS[PLAYER_1] + pS[PLAYER_2]) % 2 ? false : true), turnEnded(true), aiming(false), playersHaveColors(false), winningPlayer(0), gameIsEnded(false), playerScore(pS), gamePaused(false), ackWindowActive(false), ackWindowResult(UNSET),
hitBar{ 
		Vertex(Vector2f(W + Wfield / 2 - HIT_BAR_WIDTH / 2, HIT_BAR_Y), Color::Yellow),
		Vertex(Vector2f(W + Wfield / 2 + HIT_BAR_WIDTH / 2, HIT_BAR_Y), Color::Yellow),
		Vertex(Vector2f(W + Wfield / 2 + HIT_BAR_WIDTH / 2, HIT_BAR_Y + HIT_BAR_HEIGHT), Color::Red),
		Vertex(Vector2f(W + Wfield / 2 - HIT_BAR_WIDTH / 2, HIT_BAR_Y + HIT_BAR_HEIGHT), Color::Red)
	  }
{
	time = microseconds(TURN_DURATION);

	hitBarBackground.setSize(Vector2f(HIT_BAR_WIDTH + 2.f * HIT_BAR_OUTLINE, HIT_BAR_HEIGHT + 2.f * HIT_BAR_OUTLINE));
	hitBarBackground.setOrigin(Vector2f(HIT_BAR_WIDTH / 2 + HIT_BAR_OUTLINE, HIT_BAR_HEIGHT / 2 + HIT_BAR_OUTLINE));
	hitBarBackground.setPosition(Vector2f(W + Wfield / 2, HIT_BAR_Y + HIT_BAR_HEIGHT / 2));
	hitBarBackground.setFillColor(Color::Black);

	hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
	hitBarCover.setOrigin(Vector2f(HIT_BAR_WIDTH / 2, 0.f));
	hitBarCover.setPosition(Vector2f(W + Wfield / 2, HIT_BAR_Y));
	hitBarCover.setFillColor(LIGHT_GREY);

	for (int i = 0; i < 2; i++)
	{
		nBallsInThisTurn[i] = 0;
		nBallsLeft[i] = 7;
		nBlackHole[i] = UNSET;
	}

	font.loadFromFile("font/micross.ttf");
	for (auto &t : text) {
		t.setFont(font);
		t.setFillColor(Color::Black);
	}

	text[TurnInfo].setCharacterSize(TEXT_SIZE);

	buffer.loadFromFile("wav/hit.wav");
	sound.setBuffer(buffer);

	std::string fileName[] = { "stolik", "kij", "helper" };

	for (int i = 0; i < GRAPHICS; i++)
	{
		t[i].loadFromFile(std::string("img/") + fileName[i] + std::string(".png"));
		sprites[i].setTexture(t[i]);
	}

	sprites[STICK].setOrigin(STICK_ORIGIN_X + RADIUS, STICK_ORIGIN_Y);

	whiteBall = new Ball();
	balls.push_back(whiteBall);
	for (int i = 0; i < BALLS; i++)
	{
		Ball* b = new Ball(i, order[i % 15] - 1, clr);
		balls.push_back(b);
	}

	bottomField.setPosition(Vector2f(0.f, 0.f));
	bottomField.setSize(Vector2f(float(W), float(H + Hfield)));

	rightFieldOutline.setFillColor(Color::Black);
	rightFieldOutline.setPosition(Vector2f(float(W), 0.f));
	rightFieldOutline.setSize(Vector2f(R_FIELD_OUTLINE, float(H + Hfield)));

	rightField.setFillColor(LIGHT_GREEN);
	rightField.setPosition(Vector2f(float(W) + R_FIELD_OUTLINE, 0.f));
	rightField.setSize(Vector2f(float(Wfield - R_FIELD_OUTLINE), float(H + Hfield)));

	pauseScreen.setSize(Vector2f(float(W), float(H)));
	pauseScreen.setFillColor(Color(0, 0, 0, 215));

	pauseText.setFont(font);
	pauseText.setString("PAUSED");
	pauseText.setFillColor(Color(255, 255, 255, 215));
	pauseText.setPosition(Vector2f(float(W / 2), float(H / 2)));
	pauseText.setOrigin(float(int(pauseText.getLocalBounds().width / 2)), float(int(pauseText.getLocalBounds().height / 2 + 10.f)));


	//Creating walls
	{
		float radius = 1.f;

		std::pair<Vector2f, Vector2f> wallPosition[WALLS] = {
			{ Vector2f(P1_1_X, P1_1_Y), Vector2f(P1_2_X, P1_2_Y) },
			{ Vector2f(P1_2_X, P1_2_Y), Vector2f(P1_3_X, P1_3_Y) },
			{ Vector2f(P1_3_X, P1_3_Y), Vector2f(P1_4_X, P1_4_Y) },
			{ Vector2f(P2_1_X, P2_1_Y), Vector2f(P2_2_X, P2_2_Y) },
			{ Vector2f(P2_2_X, P2_2_Y), Vector2f(P2_3_X, P2_3_Y) },
			{ Vector2f(P2_3_X, P2_3_Y), Vector2f(P2_4_X, P2_4_Y) },
			{ Vector2f(P3_1_X, P3_1_Y), Vector2f(P3_2_X, P3_2_Y) },
			{ Vector2f(P3_2_X, P3_2_Y), Vector2f(P3_3_X, P3_3_Y) },
			{ Vector2f(P3_3_X, P3_3_Y), Vector2f(P3_4_X, P3_4_Y) },
			{ Vector2f(P4_1_X, P4_1_Y), Vector2f(P4_2_X, P4_2_Y) },
			{ Vector2f(P4_2_X, P4_2_Y), Vector2f(P4_3_X, P4_3_Y) },
			{ Vector2f(P4_3_X, P4_3_Y), Vector2f(P4_4_X, P4_4_Y) },
			{ Vector2f(P5_1_X, P5_1_Y), Vector2f(P5_2_X, P5_2_Y) },
			{ Vector2f(P5_2_X, P5_2_Y), Vector2f(P5_3_X, P5_3_Y) },
			{ Vector2f(P5_3_X, P5_3_Y), Vector2f(P5_4_X, P5_4_Y) },
			{ Vector2f(P6_1_X, P6_1_Y), Vector2f(P6_2_X, P6_2_Y) },
			{ Vector2f(P6_2_X, P6_2_Y), Vector2f(P6_3_X, P6_3_Y) },
			{ Vector2f(P6_3_X, P6_3_Y), Vector2f(P6_4_X, P6_4_Y) },
		};

		for (auto pos : wallPosition)
		{
			Wall* wall = new Wall(pos.first.x, pos.first.y, pos.second.x, pos.second.y, radius);
			walls.push_back(wall);
		}
	}

	clock.restart();
}

void Game::cursorPosRelatedComputing(bool buttonRelease)
{
	if (aiming) {
		Vector2i p1 = Mouse::getPosition(*window);
		Vector2f p2 = getWhiteBallPosition();

		float fCurrentDist = sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
		float maxDist = MAX_AIMING_DISTANCE;
		hitPower = 0.f;
		hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
		if (fCurrentDist > fDist) {

			hitPower = (fCurrentDist - fDist) / maxDist;

			if (hitPower > 1.f)
				hitPower = 1.f;
			hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, (1.f - hitPower) * HIT_BAR_HEIGHT));

			hitPower *= MAX_BALL_SPEED;

			//getting moving direction
			Vector2f speed = getWhiteBallPosition();
			speed.x -= p1.x; speed.y -= p1.y;

			//normalizing direction vector
			float length = sqrtf(speed.x*speed.x + speed.y*speed.y);

			dirVect.x = speed.x / length; dirVect.y = speed.y / length;
			speed.x *= hitPower / length; speed.y *= hitPower / length;

			if (buttonRelease) {
				setWhiteBallSpeed(speed);
				turnEnded = false;
				for (auto &n : nBallsInThisTurn) n = 0;
			}
		}
		if (buttonRelease) aiming = false;
	}
}

void Game::leftMouseButtonPress()
{
	if (turnEnded && aiming == false) {
		Vector2i p1 = Mouse::getPosition(*window);
		Vector2f p2 = getWhiteBallPosition();
		fDist = (sqrtf((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
		aiming = true;
	}
}

void Game::leftMouseButtonRelease()
{
	if (aiming) cursorPosRelatedComputing(true);
}

bool Game::isColliding(Ball* a, Ball* b) {
	return ((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y)) < ((a->R + b->R) * (a->R + b->R));
}

void Game::staticCollision() {
	for (auto a : balls) {
		for (auto w : walls) {
			float fLineX1 = w->ex - w->sx;
			float fLineY1 = w->ey - w->sy;

			float fLineX2 = a->x - w->sx;
			float fLineY2 = a->y - w->sy;

			float fWallLength = fLineX1 * fLineX1 + fLineY1 * fLineY1;

			float t = std::max(0.f, std::min(fWallLength, (fLineX1*fLineX2 + fLineY1 * fLineY2))) / fWallLength;

			float fClosestPointX = w->sx + t * fLineX1;
			float fClosestPointY = w->sy + t * fLineY1;

			float fDistance = sqrtf((a->x - fClosestPointX)*(a->x - fClosestPointX) + (a->y - fClosestPointY)*(a->y - fClosestPointY));

			if (fDistance <= (a->R + w->radius)) {
				Ball* fakeball = new Ball();
				fakeball->isFake = true;
				fakeball->R = w->radius;
				fakeball->x = fClosestPointX;
				fakeball->y = fClosestPointY;
				fakeball->dx = -a->dx;
				fakeball->dy = -a->dy;

				collidingPairs.push_back({ a, fakeball });
				fakeBalls.push_back(fakeball);

				float fOverlap = 1.f * (fDistance - a->R - fakeball->R);

				a->x -= fOverlap * (a->x - fakeball->x) / fDistance;
				a->y -= fOverlap * (a->y - fakeball->y) / fDistance;

			}
		}

		for (auto b : balls) {
			if (a != b)
				if (a->life && b->life)
					if (isColliding(a, b)) {
						float distance = sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
						float overlap = 0.5f * (distance - a->R - b->R);
						a->x -= overlap * (a->x - b->x) / distance;
						a->y -= overlap * (a->y - b->y) / distance;

						b->x -= overlap * (b->x - a->x) / distance;
						b->y -= overlap * (b->y - a->y) / distance;

						collidingPairs.push_back({ a, b });
					}
		}
	}
}

void Game::dynamicCollision() {

	for (auto c : collidingPairs)
	{
		Ball* a = c.first;
		Ball* b = c.second;
		float dx0 = a->dx, dy0 = a->dy;

		float fDistance = sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		float nx = (b->x - a->x) / fDistance;
		float ny = (b->y - a->y) / fDistance;

		float kx = a->dx - b->dx;
		float ky = a->dy - b->dy;

		float p = nx * kx + ny * ky;

		a->dx = a->dx - p * nx;		a->dy = a->dy - p * ny;
		b->dx = b->dx + p * nx;		b->dy = b->dy + p * ny;

		if (a->isFake == false && b->isFake == false)
			if (dx0 != a->dx || dy0 != a->dy)
			{
				float fVolume = MAX_HIT_SOUND_VOLUME * (BASE_VOLUME_FACTOR + SPEED_VOLUME_FACTOR * sqrtf((dx0 - a->dx) * (dx0 - a->dx) + (dy0 - a->dy) * (dy0 - a->dy)) / MAX_BALL_SPEED);
				sound.setVolume(fVolume);
				sound.play();
			}
	}
	collidingPairs.clear();
	for (auto b : fakeBalls) delete b;
	fakeBalls.clear();
}

void Game::friction() {
	for (auto a : balls)
	{
		float vel = sqrtf(a->dx*a->dx + a->dy*a->dy);
		if (vel < MIN_BALL_SPEED) {
			a->dx = 0;
			a->dy = 0;
		}
		else {
			a->dx -= (a->dx / vel) / LINEAR_FRICTION;
			a->dy -= (a->dy / vel) / LINEAR_FRICTION;
			a->dx *= FRICTION;
			a->dy *= FRICTION;
		}
		
	}
}

void Game::holeCheck() {
	float xoffset = (W - 2.f * OFFSET_X) / 2;
	for (auto a : balls)
		for (int i = 0; i <= 2; i++)
			for (int j = 0; j <= 1; j++) {
				float hx = OFFSET_X + i * xoffset;
				float hy = OFFSET_Y + j * (H - 2 * OFFSET_Y);

				if (i == 1) {
					hy -= CENTRAL_HOLE_OFFSET;
					if (j) hy += 2 * CENTRAL_HOLE_OFFSET;
				}

				if (sqrtf((a->x - hx) * (a->x - hx) + (a->y - hy) * (a->y - hy)) < HOLE_SIZE)
				{
					a->life = false;

					if (a->circle->getFillColor() == Color::Black)
					{
						if (nBlackHole[!player1Turn] == 3 * j + i) winningPlayer = !player1Turn + 1;
						else
						{
							winningPlayer = player1Turn + 1;
							gameIsEnded = true;
							playerScore[winningPlayer - 1]++;
						}
					}
					else if (a->circle->getFillColor() != Color::White)
					{
						if (playersHaveColors == false)
						{
							player1HasHalfs = a->half == player1Turn;
							playersHaveColors = true;
						}

						nBallsInThisTurn[a->half]++;
						if (--nBallsLeft[a->half] == 0)
						{
							bool player = !(player1HasHalfs == a->half);
							int thisHole = 3 * j + i;
							int oppositeHole = N_HOLES - 1 - thisHole;
							nBlackHole[player] = nBlackHole[!player] != oppositeHole ? oppositeHole : thisHole;
						}
					}
				}
			}

	for (unsigned int i = 0; i < balls.size();)
	{
		if (balls[i]->life == false && balls[i] != whiteBall) {
			balls.erase(balls.begin() + i);
		}
		else i++;
	}

	if (whiteBall->life == false) {
		whiteBall->dx = 0.f; whiteBall->dy = 0.f;
		whiteBall->x = 0.f; whiteBall->y = 0.f;
	}
}

void Game::gameUpdate() {
	if (gameIsEnded == false && gamePaused == false) {
		for (auto a : balls) {
			a->x += a->dx;
			a->y += a->dy;
			a->circle->setPosition(a->x, a->y);
		}
		friction();
		holeCheck();
		staticCollision();
		dynamicCollision();
		cursorPosRelatedComputing(false);
		positionTheStick();
		if (turnEnded && timeIsOut())
		{
			aiming = false;
			hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
			player1Turn = !player1Turn;
		}
		if (turnEnded == false && isTurnEnded() == true)
			endTurn();
		showText();
	}
}

void Game::showText()
{
	#pragma region turnInfo

		if (gameIsEnded) {
			text[TurnInfo].setString("Player " + std::to_string(winningPlayer) + " wins! (space)");
		}
		else if (turnEnded) {
			String playerText;
			String color = "";
			String holes[N_HOLES] = { L" (left upper hole)", L" (upper hole)", L" (right upper hole)",
								L" (left lower hole)", L" (lower hole)", L" (right lower hole)", };

			playerText = player1Turn ? "1" : "2";

			if (playersHaveColors)
			{
				bool bColor = player1HasHalfs == player1Turn;

				if (nBallsLeft[bColor] > 0)
					color = bColor ? L" (half)" : L" (full)";
				else
					color = holes[nBlackHole[!player1Turn]];
			}

			text[TurnInfo].setString("Player's " + playerText + " turn" + color);
		}
		else
		{
			text[TurnInfo].setString("Turn in progress");
		}

	#pragma endregion

	//tekst po prawej
		std::string s = "SCORE";
		text[Score].setString(s);

		s = std::to_string(playerScore[PLAYER_1]);
		text[P1Score].setString(s);

		s = ":";
		text[Colon].setString(s);

		s = std::to_string(playerScore[PLAYER_2]);
		text[P2Score].setString(s);

		s = "HALF: " + std::to_string(nBallsInThisTurn[HALF]) + "\nFULL: " + std::to_string(nBallsInThisTurn[FULL]);		
		text[BallsThisTurn].setString(s);

		s = "half left: " + std::to_string(nBallsLeft[HALF]) + "\nfull left: " + std::to_string(nBallsLeft[FULL]);
		text[BallsLeft].setString(s);

		s = std::to_string(int(time.asSeconds())) + "." + std::to_string(int((time.asSeconds() - int(time.asSeconds())) * 10.f)) + "s";
		text[TimeLeft].setString(s);

		text[TurnInfo].setPosition(W / 2, H + Hfield / 2);
		text[Score].setPosition(W + Wfield / 2, 50.f);
		text[P1Score].setPosition(W + Wfield / 2 - 5.f, 85.f);
		text[Colon].setPosition(W + Wfield / 2, 85.f);
		text[P2Score].setPosition(W + Wfield / 2 + 10.f, 85.f);
		text[BallsThisTurn].setPosition(W + Wfield / 2, 150.f);
		text[BallsLeft].setPosition(W + Wfield / 2, 640.f);
		text[TimeLeft].setPosition(W + Wfield / 2, 590);

		for (auto &t : text)
			t.setOrigin(float(int(t.getLocalBounds().width / 2)), float(int(t.getLocalBounds().height / 2 + TEXT_SIZE / 4)));

		text[P1Score].setOrigin(float(int(text[P1Score].getLocalBounds().width)), float(int(text[P1Score].getLocalBounds().height / 2 + 10.f)));
		text[P2Score].setOrigin(0.f, float(int(text[P2Score].getLocalBounds().height / 2 + 10.f)));
}

bool Game::isTurnEnded() {
	for (auto a : balls)
		if (a->dx || a->dy) return false;
	return true;
}

void Game::endTurn()
{
	bool tc = true; //turn change

	bool bColor = player1Turn == player1HasHalfs;
	if (nBallsInThisTurn[bColor] > 0 && nBallsInThisTurn[!bColor] == 0) {
		if (whiteBall->life) 
			tc = false;
	}

	if (tc) player1Turn = !player1Turn;

	if (winningPlayer && whiteBall->life == false) {
		winningPlayer %= 2;
		winningPlayer++;
	}

	if (winningPlayer) gameIsEnded = true;

	if (gameIsEnded) playerScore[winningPlayer - 1]++;

	if (whiteBall->life == false) {
		whiteBall->x = WHITEBALL_START_X * W;
		whiteBall->y = H / 2.f;
		whiteBall->life = true;
	}

	hitBarCover.setSize(Vector2f(HIT_BAR_WIDTH, HIT_BAR_HEIGHT));
	turnEnded = true;
	time = microseconds(TURN_DURATION);
	clock.restart();
}

void Game::positionTheStick() {
	Vector2i cursor = Mouse::getPosition(*window);
	Vector2f whiteBallPos = getWhiteBallPosition();
	Vector2f result(0.f, 0.f);
	result.x = cursor.x - whiteBallPos.x;
	result.y = cursor.y - whiteBallPos.y;

	for (int i = 1; i < 3; i++) {
		sprites[i].setPosition(getWhiteBallPosition());
		sprites[i].setRotation((-atan2(result.x, result.y) * 180.f / M_PI) - 90.f);
	}

	if (aiming) {
		Vector2f vec(STICK_MOVEMENT_MULTIPLIER, STICK_MOVEMENT_MULTIPLIER);
		vec.x *= dirVect.x * hitPower * -1.f;
		vec.y *= dirVect.y * hitPower * -1.f;

		for (int i = 1; i < 3; i++) {
			sprites[i].move(vec);
		}
	}
}

bool Game::timeIsOut()
{
	Time t = clock.getElapsedTime();
	Int64 us = time.asMicroseconds() - t.asMicroseconds();

	clock.restart();
	if (us <= 0) {
		time = microseconds(TURN_DURATION);
		return true;
	}
	else {
		time = microseconds(us);
		return false;
	}
}

void Game::gameDraw() {
	bottomField.setFillColor(player1Turn ? P1_TURN_COLOR : P2_TURN_COLOR);

	if (gameIsEnded)
		bottomField.setFillColor(winningPlayer % 2 ? P1_WIN_COLOR : P2_WIN_COLOR);

	window->draw(bottomField);
	window->draw(rightFieldOutline);
	window->draw(rightField);
	
	window->draw(sprites[0]); // drawing background
	for (auto a : balls)
		if (a->life) window->draw(*(a->circle)); // drawing balls
	
	for (auto t : text)
		window->draw(t);

	window->draw(hitBarBackground);
	window->draw(hitBar, 4, Quads);
	window->draw(hitBarCover);

	for (int i = 1; i < GRAPHICS; i++)
		if (turnEnded && gamePaused == false)
			window->draw(sprites[i]); // drawing stick and white lines


	//Drawing holes for debugging purposes
	/*
	float xoffset = (W - 2.f*OFFSET_X) / 2;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++) {
			float hx = OFFSET_X + i * xoffset;
			float hy = OFFSET_Y + j * (H - 2 * OFFSET_Y);
			if (i == 1) {
				hy -= 20.f;
				if (j) hy += 40.f;
			}
			CircleShape hole;
			hole.setRadius(HOLE_SIZE);
			hole.setOrigin(HOLE_SIZE, HOLE_SIZE);
			hole.setPosition(Vector2f(hx, hy));
			hole.setFillColor(Color::Yellow);
			window->draw(hole);
		}*/

	//Drawing walls for debug purposes

	//for (auto w : walls)
		//{
		//	CircleShape c1(w->radius), c2(w->radius);
		//	c1.setOrigin(w->radius, w->radius);
		//	c2.setOrigin(w->radius, w->radius);
		//	c1.setFillColor(Color::Blue);
		//	c2.setFillColor(Color::Red);
		//	c1.setPosition(Vector2f(w->sx, w->sy));
		//	c2.setPosition(Vector2f(w->ex, w->ey));
		//	window->draw(c1);
		//	window->draw(c2);
		//}

	if (gamePaused) {
		window->draw(pauseScreen);
		window->draw(pauseText);
	}

	if (ackWindowActive)
		window->draw(ackWindow);
}

void Game::setWhiteBallSpeed(Vector2f vec) {
	whiteBall->dx = vec.x;
	whiteBall->dy = vec.y;
}

Vector2f Game::getWhiteBallPosition() {
	Vector2f pos(whiteBall->x, whiteBall->y);
	return pos;
}

Game::~Game() {
	for (auto b : balls) delete b;
	balls.clear();
	for (auto w : walls) delete w;
	walls.clear();
}