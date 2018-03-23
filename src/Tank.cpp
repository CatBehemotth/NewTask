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
													coord(startCoord),
													tankBody_(element),
													listener(_listener)
{
	tankHealth_ = health;
	moveDirection = directionOfTank;
	direction = moveDirection;
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

bool Tank::isAlive(const Tank& unit)
{
	if (unit.tankHealth_  > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void Tank::setDirection(const COORD& newDirection)
{
	direction = newDirection;
}

void Tank::setMoveDirection(const COORD& newDirection)
{
	moveDirection = newDirection;

	if (newDirection.X != 0 && newDirection.Y !=0)
		direction = newDirection;
}

void Tank::changeMoveDirection(COORD newMoveDirection)
{
	moveDirection.X *= newMoveDirection.X;
	moveDirection.Y *= newMoveDirection.Y;
}

const COORD& Tank::getCoord() const
{
	return coord;
}

void Tank::draw()
{
	for (auto &local_coord : localCoords)
	{
		COORD localCoord = { local_coord.X + coord.X, local_coord.Y + coord.Y };
		UpdateDisplay::drowElement(localCoord, tankBody_);
	}
}

void Tank::update()
{
	coord.X += moveDirection.X;
	coord.Y += moveDirection.Y;

	if (coord.X <= 2 || coord.X >= 47)
	{
		moveDirection.X *= -1;
		direction = moveDirection;
	}
	else if (coord.Y <= 3 || coord.Y >=47)
	{
		moveDirection.Y *= -1;
		direction = moveDirection;
	}
}

void Tank::fire() const
{
	COORD startPos = { coord.X + direction.X * 2, coord.Y + direction.Y * 2 };
	listener.onFire(startPos, direction);
}

const int Tank::getScore()const
{
	return score_;;
}

void Tank::setScore(int score)
{
	score_ += score;
}
