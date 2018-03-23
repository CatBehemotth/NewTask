#include "stdafx.h"
#include "GameController.h"
#include "UpdateDisplay.h"
#include "DisplayCreator.h"
#include "Wall.h"
#include "Constants.h"



GameController::GameController()
{	
	addWall({ 20,45 }, WALL_SYMBOL);
	auto tank = std::shared_ptr<MyTank>(new MyTank(*this, 0, 'o', 3, { START_COORDINATES[0] }, { 0, -1 }));
	tank->getHealth();
	//tank->setDirection({ -1,0 });
	mTanks.push_back(tank);
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '#', ENEMY_HEALTH, { START_COORDINATES[1] }, { -1, 0 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '$', ENEMY_HEALTH, { START_COORDINATES[2] }, { 0, -1 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '@', ENEMY_HEALTH, { START_COORDINATES[3] }, { -1, 0 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '%', ENEMY_HEALTH, { START_COORDINATES[4] }, { 1, 0 })));
	
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

		calculateTankMyTankCollision();

		for (auto &bullet : mBullets)
		{
			bullet.update();

		}

		for (auto &wall : mWall)
		{
			wall.draw();
			wall.drawFortress();
			if (mWall.size() <= MAXIMUM_WALLS)
			{
				addWall({ randomWallCoord() }, WALL_SYMBOL);
			}
		}

		calculateBulletsWallCollision();
		calculateTankWallCollision();
		calculateBulletsFieldCollision();
		calculateBulletsCollision();
		calculateTanksCollisions();		

		for (auto &bullet : mBullets)
		{
			bullet.draw();
		}

		for (auto &tank : mTanks)
		{
			if (mTanks[0]->getHealth()>0)
			{
				tank->update();
				tank->draw();
			}	
			//tank->update();		
			//tank->draw();
		}

		DisplayCreator::drawScore({ 0,51 },mTanks[0]->getScore());
		DisplayCreator::drawTime({ 20,51 }, clock());

		if (isVictory())
		{
			std::cout << "YOU WIN!";
			break;
		}
		
		Sleep(150);
		

	}
}

void GameController::calculateBulletsCollision()  //
{
	int bulletIndex = -1;
	int tankIndex = -1;
	int myTankIndex = 0;
	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		for (size_t tank = 0; tank < mTanks.size(); ++tank)
		{
			if (isBulletTankCollision(mBullets[bullet], *mTanks[tank]))
			{
				bulletIndex = bullet;
				tankIndex = tank;
				break;
			}
		}
		if (tankIndex == myTankIndex)
		{
			mTanks[0]->setHealth(1);
		}
		
		if (mTanks[0]->getHealth()==0)
		{
			exit(1);
			
		}

		if (bulletIndex != -1)
			break;
	}

	if (bulletIndex != -1)
	{
		mBullets.erase(mBullets.begin() + bulletIndex);

		if (tankIndex >0 )
		{
			mTanks.erase(mTanks.begin() + tankIndex);
			mTanks[0]->setScore(1);
		}

	}
	if ((mTanks.size() < MAXIMUM_NUMBER_OF_ENEMIES) &&
		((randomTankCoords().X != randomWallCoord().X)) &&
		(randomTankCoords().Y != randomWallCoord().Y))
	{
		mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, TANK_BODY[ramdom()], 1,
			{ randomTankCoords() }, { VARIANTS_OF_DIRECTIONS[randomTankDirection()] })));
	}
}

void GameController::calculateTanksCollisions()
{
	int tankIndex = -1;
	int otherTankIndex = -1;
	for (size_t tank = 0; tank < mTanks.size(); ++tank)
	{
		for (size_t otherTank = 0; otherTank < mTanks.size(); ++otherTank)
		{
			if (isTankTankCollision(*mTanks[tank], *mTanks[otherTank]))
			{
				tankIndex = tank;
				otherTankIndex = otherTank;
				break;
			}
		}
		if (tankIndex != -1)
			break;
	}
	if (tankIndex != -1)
	{
		mTanks.at(tankIndex)->changeMoveDirection({ 1,-1 });
		mTanks.at(tankIndex)->changeMoveDirection({ -1,1 });		
	}
	if (otherTankIndex !=-1)
	{
		mTanks.at(otherTankIndex)->changeMoveDirection({ 1,-1 });
		mTanks.at(otherTankIndex)->changeMoveDirection({ -1,1 });
	}
}

void GameController::calculateBulletsFieldCollision()
{
	int bulletIndex = -1;

	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		if (isBulletFieldCollision(mBullets[bullet]))
		{
			bulletIndex = bullet;
			break;
		}
	}
	if (bulletIndex != -1)
	{
		mBullets.erase(mBullets.begin() + bulletIndex);
	}
}

void GameController::calculateBulletsWallCollision()
{
	int bulletIndex = -1;
	int wallIndex = -1;
	int fortressIndex = -1;
	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isBulletWallCollision(mBullets[bullet], mWall[wall]))
			{
				
				bulletIndex = bullet;
				wallIndex = wall;
				break;
			}
		}
		if (bulletIndex != -1)
			break;
	}
	if (bulletIndex != -1)
	{
		mBullets.erase(mBullets.begin() + bulletIndex);
	}
	if (wallIndex != -1)
	{
		mWall.erase(mWall.begin() + wallIndex);
	}

	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isFinish(mBullets[bullet], mWall[wall]))
			{

				bulletIndex = bullet;
				//wallIndex = wall;
				break;
			}
		}
		if (bulletIndex != -1)
			break;
	}
	
	if (fortressIndex != -1)
	{
		
		exit(1);
	}
}

void GameController::calculateTankMyTankCollision()
{
	int tankIndex = -1;
	int myTankIndex = 0;
	for (size_t tank = 1; tank < mTanks.size(); ++tank)
	{
			if (isFire(*mTanks[tank], *mTanks[myTankIndex]))
			{
				tankIndex = tank;
				break;
			}
		if (tankIndex != -1)
			break;
	}
	if (tankIndex != -1)
	{
		mTanks.at(tankIndex)->fire();
		
	}
}

void GameController::calculateTankWallCollision()
{
	int tankIndex = -1;
	int wallIndex = -1;
	for (size_t tank = 0; tank < mTanks.size(); ++tank)
	{
		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isTankWallCollision(*mTanks[tank], mWall[wall]))
			{
				tankIndex = tank;
				wallIndex = wall;
				
				break;
			}
		}
		if (tankIndex != -1)			
			//mTanks.at(tankIndex)->changeMoveDirection({1,-1});
			//mTanks[0]->getHealth();
			break;
	}
	if (tankIndex != -1)
	{
		mTanks.at(tankIndex)->changeMoveDirection({1,-1});
		mTanks.at(tankIndex)->changeMoveDirection({-1,1});
	}
}

void GameController::addWall(const COORD & startCoord, const char& symbol)
{
	mWall.push_back({ startCoord, symbol });
}

size_t GameController::ramdom()
{
	srand(time(0));

	return rand() % 4;
}

COORD GameController::randomTankCoords()
{
	COORD coord;
	srand(time(0));
	coord.X = rand() % 44 + 3;
	coord.Y = rand() % 44 + 3;
	return coord;
}

int GameController::randomTankDirection()
{
	int tankDirection =0;
	srand(time(NULL));
	tankDirection = rand() % 5;
	return tankDirection;
}

COORD GameController::randomWallCoord()
{
	COORD wallCoord;
	srand(time(0));
	wallCoord.X = rand() % 45 + 2;
	wallCoord.Y = rand() % 45 + 2;
	return wallCoord;
}

void GameController::onFire(const COORD& startCoord, const COORD& direction)
{
	mBullets.push_back({ startCoord, direction });
}

bool GameController::isVictory()
{
	if (mTanks.at(0)->getScore()>15)
	{
		return true;
	}
	return false;
}

bool GameController::isFinish(const Bullet & bullet, const Wall & wall) const
{
	auto wallLocalCoord = COORD	{20,48};
	auto bulletCoord = bullet.getPosition();

	for (auto &local_coord : Wall::LOKAL_COORDS)
	{
		COORD localCoord = { local_coord.X + bulletCoord.X, local_coord.Y + bulletCoord.Y };

		if (wallLocalCoord.X == localCoord.X && wallLocalCoord.Y == localCoord.Y)
			return true;
	}
	return false;
}

bool GameController::isTankWallCollision(const Tank & tank, const Wall & wall)
{
	auto tankLocalCoord = tank.getCoord();
	auto wallCoord = wall.getPosition();

	for (auto &local_coord : Tank::localCoords)
	{
		COORD localCoord = { local_coord.X + tankLocalCoord.X, local_coord.Y + tankLocalCoord.Y };
		if (wallCoord.X == localCoord.X && wallCoord.Y == localCoord.Y + 2 ||
			(wallCoord.X == localCoord.X && wallCoord.Y == localCoord.Y - 2)||
			(wallCoord.X == localCoord.X+2 && wallCoord.Y == localCoord.Y ) ||
			(wallCoord.X == localCoord.X-2 && wallCoord.Y == localCoord.Y ))
				return true;			
	}
	return false;
}

bool GameController::isBulletTankCollision(const Bullet & bullet, const Tank & tank)
{
	auto tankLocalCoord = tank.getCoord();
	auto bulletCoord = bullet.getPosition();

	for (auto &local_coord : Tank::localCoords)
	{
		COORD localCoord = { local_coord.X + tankLocalCoord.X, local_coord.Y + tankLocalCoord.Y };
		if (bulletCoord.X == localCoord.X && bulletCoord.Y == localCoord.Y)
			return true;
	}
	return false;
}

bool GameController::isBulletWallCollision(const Bullet & bullet, const Wall & wall)
{
	auto wallLocalCoord = wall.getPosition();
	auto bulletCoord = bullet.getPosition();

	for (auto &local_coord : Wall::LOKAL_COORDS)
	{
		COORD localCoord = { local_coord.X + wallLocalCoord.X, local_coord.Y + wallLocalCoord.Y };

		if (bulletCoord.X == localCoord.X && bulletCoord.Y == localCoord.Y)
			return true;
	}
	return false;
}

bool GameController::isBulletFieldCollision(const Bullet & bullet)
{
	auto bulletCoord = bullet.getPosition();
	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		if (bulletCoord.Y > 48 || bulletCoord.Y < 2 || bulletCoord.X > 48 || bulletCoord.X < 2)
		{
			return true;
		}
	}
	return false;
}

bool GameController::isTankTankCollision(const Tank & enemyTank, const Tank & otherEnemyTank)
{
	auto enemyTankLocalCoord = enemyTank.getCoord();
	auto otherEnemyTankCoord = otherEnemyTank.getCoord();

	for (auto &local_coord : Tank::localCoords)
	{
		COORD localCoord = { local_coord.X + enemyTankLocalCoord.X, local_coord.Y + enemyTankLocalCoord.Y };
		if (otherEnemyTankCoord.X == localCoord.X && otherEnemyTankCoord.Y == localCoord.Y+4 || 
			(otherEnemyTankCoord.X == localCoord.X && otherEnemyTankCoord.Y == localCoord.Y - 4)|| 
			(otherEnemyTankCoord.X == localCoord.X+4 && otherEnemyTankCoord.Y == localCoord.Y ) ||
			(otherEnemyTankCoord.X == localCoord.X-4 && otherEnemyTankCoord.Y == localCoord.Y ))
			
			return true;
	}
	return false;
}

bool GameController::isFire(const Tank & enemyTank, const Tank & myTank)
{
	auto enemyTankLocalCoord = enemyTank.getCoord();
	auto myTankLocalCoord = myTank.getCoord();

	for (auto &local_coord : Tank::localCoords)
	{
		COORD localCoord = { local_coord.X + enemyTankLocalCoord.X, local_coord.Y + enemyTankLocalCoord.Y };
		if ((myTankLocalCoord.X == localCoord.X || myTankLocalCoord.Y == localCoord.Y ))
		   
			return true;
	}
	return false;
}
