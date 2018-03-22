#include "stdafx.h"
#include "GameController.h"
#include "UpdateDisplay.h"
#include "DisplayCreator.h"


GameController::GameController()
{
	//mWall.push_back((COORD{25,25} ));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '#', 1, { 12,35 }, { -1, 0 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '$', 1, { 35,12 }, { 0, 1 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '@', 1, { 28,39 }, { 1, 0 })));
	auto tank = std::shared_ptr<MyTank>(new MyTank(*this, 0, 'o', 3, { 24,46 }, {0,0}));
	tank->setDirection({ 0, -1 });
	tank->getScore();
	mTanks.push_back(tank);
	
	
	startCircle();
}

GameController::~GameController()
{
}

void GameController::startCircle()
{
	while (true)
	{

	
		UpdateDisplay::cleanDisplay(DisplayCreator::FIELD_SIZE, ' ');

		for (auto &bullet : mBullets)
		{
			bullet.update();

		}

		for (auto &wall : mWall)
		{
			wall.draw();
			wall.drawFortress();
		}

		//calculateBulletsBarrierCollision();
		//calculateBulletsFieldCollision();
		//randomBodyElement = rand() % 3;
		//calculateBulletsCollision();
		//calculateTanksCollisions();

		for (auto &bullet : mBullets)
		{
			bullet.draw();
		}

		for (auto &tank : mTanks)
		{
			tank->update();
			tank->draw();
		}
		
		DisplayCreator::drawScore({ 0,51 }, 0);
		DisplayCreator::drawTime({ 20,51 }, clock());

		Sleep(150);
	}
}

void GameController::onFire(const COORD& startCoord, const COORD& direction)
{
	mBullets.push_back({ startCoord, direction });
}
