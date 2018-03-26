#include "stdafx.h"
#include "Bullet.h"
#include "UpdateDisplay.h"

Bullet::Bullet(const COORD& startCoords, const COORD& direction, eSource source):
	position(startCoords), direction(direction), source_(source)
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

const Bullet::eSource Bullet::getESource()const
{
	return source_;
}

const COORD& Bullet::getPosition() const
{
	return position;
}
