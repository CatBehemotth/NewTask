#include "stdafx.h"
#include "Tank.h"
#include "UpdateDisplay.h"
#include "GameController.h"

const std::vector<COORD> Tank::localCoords = { { -1, -1 },{ 0, -1 },{ 1, -1 },
											 { -1, 0 },{ 0, 0 },{ 1, 0 },
											 { -1, 1 },{ 0, 1 },{ 1, 1 } };

Tank::Tank(TankListener & _listener, const char & element, const int & health, 
									const COORD& startCoord, 
									const COORD& directionOfTank):
													coord_(startCoord),
													tankBody_(element),
													listener(_listener),
													tankHealth_(health),
													moveDirection_(directionOfTank),
													direction_(moveDirection_)
{
}	

Tank::~Tank()
{
}

const int Tank::getHealth()
{
	return tankHealth_;
}

void Tank::setHealth(int health)
{
	tankHealth_ -= health;
}

void Tank::setDirection(const COORD& newDirection)
{
	direction_ = newDirection;
}

void Tank::setMoveDirection(const COORD& newDirection)
{
	moveDirection_ = newDirection;

	if (newDirection.X != 0 && newDirection.Y !=0)
		direction_ = newDirection;
}

void Tank::changeMoveDirection(COORD newmoveDirection_)
{
	moveDirection_.X *= newmoveDirection_.X;
	moveDirection_.Y *= newmoveDirection_.Y;
}

const COORD Tank::getMoveDirection() const
{
	return moveDirection_;
}

const COORD& Tank::getCoord() const
{
	return coord_;
}

void Tank::draw()
{
	for (auto &local_coord : localCoords)
	{
		COORD localCoord = { local_coord.X + coord_.X, local_coord.Y + coord_.Y };
		UpdateDisplay::drowElement(localCoord, tankBody_);
	}
}

void Tank::update()
{
	coord_.X += moveDirection_.X;
	coord_.Y += moveDirection_.Y;

	if (coord_.X <= 2 || coord_.X >= 47)
	{
		moveDirection_.X *= -1;
		direction_ = moveDirection_;
	}
	else if (coord_.Y <= 3 || coord_.Y >=47)
	{
		moveDirection_.Y *= -1;
		direction_ = moveDirection_;
	}
}

void Tank::fire() const
{
	COORD startPos = { coord_.X + direction_.X * 2, coord_.Y + direction_.Y * 2 };
	listener.onFire(startPos, direction_, Bullet::ENEMY_TANK);
}

const int Tank::getScore()const
{
	return score_;;
}

void Tank::setScore(int score)
{
	score_ += score;
}
