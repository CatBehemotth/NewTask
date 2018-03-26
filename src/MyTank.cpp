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


void MyTank::fire() const
{
		COORD startPos = { coord_.X + direction_.X * 2, coord_.Y + direction_.Y * 2 };
		listener.onFire(startPos, direction_, Bullet::MYTANK);
}

void MyTank::update()
{
	if (GetAsyncKeyState(VK_UP) && coord_.Y > 3)
	{
		if (coord_.Y == 3)
		{
			--coord_.Y;
		}
		else
			coord_.Y -= 1;

		direction_.Y = -1;
		moveDirection_.Y = -1;
		direction_.X = 0;
		moveDirection_.X = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) && coord_.X>3)
	{
		coord_.X -= 1;

		direction_.X = -1;
		moveDirection_.X = -1;
		direction_.Y = 0;
		moveDirection_.Y = 0;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && coord_.X<47)
	{
		if (coord_.X == 46)
		{
			++coord_.X;
		}
		else
			coord_.X += 1;

		direction_.X = 1;
		moveDirection_.X = 1;

		direction_.Y = 0;
		moveDirection_.Y = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) && coord_.Y<47)
	{
		coord_.Y += 1;

		direction_.Y = 1;
		moveDirection_.Y = 1;
		direction_.X = 0;
		moveDirection_.X = 0;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		fire();
	}
}

