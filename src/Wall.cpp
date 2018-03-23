#include "stdafx.h"
#include "Wall.h"
#include "UpdateDisplay.h"

const std::vector<COORD>Wall::LOKAL_COORDS = { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };
const std::vector<COORD>Wall::LOKAL_FORTRESS_COORD = { {-1,0},{-1,1},{0,0},{1,1},{1,0} };
const COORD Wall::START_FORT_POSITION_ = {20,47};

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
	for (auto &local_coord : LOKAL_COORDS)
	{
		COORD localCoord = { local_coord.X + startPosition_.X, local_coord.Y + startPosition_.Y };
		UpdateDisplay::drowElement(localCoord, wallSymbol_);
	}
}

void Wall::drawFortress()
{
	for (auto &local_coord : LOKAL_FORTRESS_COORD)
	{
		COORD localCoord = { local_coord.X + START_FORT_POSITION_.X, local_coord.Y + START_FORT_POSITION_.Y };
		UpdateDisplay::drowElement(localCoord, wallSymbol_);
		UpdateDisplay::drowElement({20,48}, '$');
	}
}

const COORD& Wall::getPosition() const
{
	return startPosition_;
}
