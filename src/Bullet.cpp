#include "stdafx.h"
#include "Bullet.h"
#include "UpdateDisplay.h"

Bullet::Bullet(const COORD& startCoords, const COORD& direction):
	position(startCoords), direction(direction)
{
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	UpdateDisplay::drowElement(position, '*');
}

void Bullet::update()
{
	position.X += direction.X;
	position.Y += direction.Y;
}

const COORD& Bullet::getPosition() const
{
	return position;
}
