#include "stdafx.h"
#include "Wall.h"
#include "UpdateDisplay.h"

const std::vector<COORD>Wall::localCoords = { { -1, 0 },{ 0, 0 },{ 1, 0 } };
const std::vector<COORD>Wall::localFortressCoords = { {-1,0},{-1,1},{0,0},{1,1},{1,0} };

Wall::Wall(const COORD& startCoords, const char& symbol):
												startPosition_(startCoords),
												wallSymbol_(symbol)
{
}

Wall::~Wall()
{
}

void Wall::draw()
{
	for (auto &local_coord : localCoords)
	{
		COORD localCoord = { local_coord.X + startPosition_.X, local_coord.Y + startPosition_.Y };
		UpdateDisplay::drowElement(localCoord, wallSymbol_);
	}
}

void Wall::drawFortress()
{
	for (auto &local_coord : localFortressCoords)
	{
		COORD localCoord = { local_coord.X + startFortPosition_.X, local_coord.Y + startFortPosition_.Y };
		UpdateDisplay::drowElement(localCoord, wallSymbol_);
	}
}

const COORD& Wall::getPosition() const
{
	return startPosition_;
}
