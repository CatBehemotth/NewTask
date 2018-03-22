#include "stdafx.h"
#include "MyTank.h"
#include "GameController.h"

MyTank::MyTank(TankListener & listener, const int& score, const char& element,const int& health, 
	COORD startCoord, COORD direction):Tank(listener,element,health,startCoord,direction)
{
	score_ = score;
}

MyTank::~MyTank()
{
}

const int MyTank::getScore()const
{
	return score_;;
}

void MyTank::setScore(int& score)
{
	score_ =score;
}

void MyTank::update()
{
	if (GetAsyncKeyState(VK_UP) && coord.Y > 3)
	{
		if (coord.Y == 3)
		{
			--coord.Y;
		}
		else
			coord.Y -= 1;

		direction.Y = -1;
		moveDirection.Y = -1;
		direction.X = 0;
		moveDirection.X = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) && coord.X>3)
	{
		coord.X -= 1;

		direction.X = -1;
		moveDirection.X = -1;
		direction.Y = 0;
		moveDirection.Y = 0;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && coord.X<46)
	{
		if (coord.X == 46)
		{
			++coord.X;
		}
		else
			coord.X += 1;

		direction.X = 1;
		moveDirection.X = 1;

		direction.Y = 0;
		moveDirection.Y = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) && coord.Y<46)
	{
		coord.Y += 1;

		direction.Y = 1;
		moveDirection.Y = 1;
		direction.X = 0;
		moveDirection.X = 0;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		fire();
	}
}
