#include "stdafx.h"
#include "GameController.h"
#include "UpdateDisplay.h"
#include "DisplayCreator.h"
#include "Wall.h"
#include "Constants.h"




GameController::GameController()
{	
	addWall({ FORTRESS_POSITION[0] }, WALL_SYMBOL);
	addWall({ FORTRESS_POSITION[1] }, WALL_SYMBOL);
	addWall({ FORTRESS_POSITION[2] }, WALL_SYMBOL);
	auto tank = std::shared_ptr<MyTank>(new MyTank(*this, 0, 'F', 3, { START_COORDINATES[0] }, { 0, -1 }));
	mTanks.push_back(tank);
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '#', ENEMY_HEALTH, { START_COORDINATES[1] }, { -1, 0 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '$', ENEMY_HEALTH, { START_COORDINATES[2] }, { 0, -1 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '@', ENEMY_HEALTH, { START_COORDINATES[3] }, { -1, 0 })));
	mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, '%', ENEMY_HEALTH, { START_COORDINATES[4] }, { 0, 1 })));
	
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

		for (auto &wall : mWall)
		{
			wall.draw();
			wall.drawFortress();
			if (mWall.size() <= MAXIMUM_WALLS)
			{
				addWall({ randomWallCoord() }, WALL_SYMBOL);
			}
		}

		enemyTankAttack();

		for (auto &bullet : mBullets)
		{
			bullet.update();
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
			tank->update();		
			tank->draw();
		}

		DisplayCreator::drawScore(SCORE_COORD,mTanks[0]->getScore());
		DisplayCreator::drawTime(TIME_COORD, clock());

		if (isVictory())
		{
			std::cout << std::endl << std::endl << "\t\tYOU WIN!!!" << std::endl << std::endl << std::endl << std::endl;
			break;
		}
		
		if (isFinish())
		{
			std::cout << std::endl << std::endl << "\t\tYOU LOSE" << std::endl << std::endl << std::endl << std::endl;
			break;
		}

		if (BulletsFortressCollision())
		{
			std::cout << std::endl << std::endl << "\t\tYOU LOSE" << std::endl << std::endl << std::endl << std::endl;
			break;
		}

		Sleep(250);
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
		
		if (bulletIndex != -1)
			break;
	}

	if (bulletIndex != -1)
	{
		if (tankIndex >myTankIndex && mBullets[bulletIndex].getESource() != Bullet::ENEMY_TANK)
		{
			mBullets.erase(mBullets.begin() + bulletIndex);
			mTanks.erase(mTanks.begin() + tankIndex);
			mTanks[0]->setScore(1);
		}
		else
		{
			mBullets.erase(mBullets.begin() + bulletIndex); 
		}
	}
	if ((mTanks.size() < MAXIMUM_NUMBER_OF_TANK) &&(
		((randomTankCoords().X != randomWallCoord().X+3)) &&
		(randomTankCoords().Y != randomWallCoord().Y+3)|| 
		(((randomTankCoords().X != randomWallCoord().X - 3)) &&
		(randomTankCoords().Y != randomWallCoord().Y - 3))))
	{
		mTanks.push_back(std::shared_ptr<Tank>(new Tank(*this, TANK_BODY[random()], 1,
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
		mTanks.at(otherTankIndex)->changeMoveDirection({ -1,1 });
		mTanks.at(otherTankIndex)->changeMoveDirection({ 1,-1 });
	}
}

void GameController::calculateBulletsFieldCollision()
{
	std::vector<size_t> nIndex;

	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		if (isBulletFieldCollision(mBullets[bullet]))
		{
			mBullets.erase(mBullets.begin() + bullet);
		}
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
}

void GameController::enemyTankAttack()
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
	if (tankIndex != -1 )
	{
		mTanks.at(tankIndex)->fire();		
	}
}

void GameController::calculateTankWallCollision()
{
	int tankIndex = -1;
	for (size_t tank = 0; tank < mTanks.size(); ++tank)
	{
		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isTankWallCollision(*mTanks[tank], mWall[wall]))
			{
				tankIndex = tank;				
				break;
			}
		}
		if (tankIndex != -1)			
			break;
	}
	if (tankIndex != -1)
	{
		mTanks.at(tankIndex)->changeMoveDirection({1,-1});
		mTanks.at(tankIndex)->changeMoveDirection({-1,1});
	}
}

void GameController::myTankWallColliion()
{
	int tankIndex = 0;

		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isTankWallCollision(*mTanks[tankIndex], mWall[wall]))
			{
				break;
			}
		}	
	mTanks.at(tankIndex)->changeMoveDirection({ 1,-1 });
	mTanks.at(tankIndex)->changeMoveDirection({ -1,1 });	
}

bool GameController::BulletsFortressCollision() 
{
	int bulletIndex = -1;
	int fortressIndex = -1;
	for (size_t bullet = 0; bullet < mBullets.size(); ++bullet)
	{
		for (size_t wall = 0; wall < mWall.size(); ++wall)
		{
			if (isBulletFortressCollision(mBullets[bullet], mWall[wall]))
			{
				bulletIndex = bullet;
				fortressIndex = wall;
				break;
			}
		}
		if (bulletIndex != -1)
			break;
	}
	if (bulletIndex != -1)
	{
		return true;
	}
	return false;

}

void GameController::addWall(const COORD & startCoord, const char& symbol)
{
	mWall.push_back({ startCoord, symbol });
}

size_t GameController::random()
{
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
	return rand() % 5;;
}

COORD GameController::randomWallCoord()
{
	COORD wallCoord;
	wallCoord.X = rand() % 45 + 2;
	wallCoord.Y = rand() % 45 + 2;
	return wallCoord;
}

void GameController::onFire(const COORD& startCoord, const COORD& direction, Bullet::eSource source)
{
	mBullets.push_back({ startCoord, direction ,source });
}

bool GameController::isVictory()
{
	if (mTanks.at(0)->getScore()>15)
	{
		return true;
	}
	return false;
}

bool GameController::isFinish() const
{
	if ((mTanks[0]->getHealth() == 0) ) 
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool GameController::isTankWallCollision(const Tank & tank, const Wall & wall)
{
	auto tankLocalCoord = tank.getCoord();
	auto wallCoord = wall.getPosition();

	for (auto &local_coord : Tank::localCoords)
	{
		COORD localCoord = { local_coord.X + tankLocalCoord.X, local_coord.Y + tankLocalCoord.Y };
		if (wallCoord.X == localCoord.X && wallCoord.Y == localCoord.Y + 4 ||
			(wallCoord.X == localCoord.X && wallCoord.Y == localCoord.Y - 4)||
			(wallCoord.X == localCoord.X+4 && wallCoord.Y == localCoord.Y ) ||
			(wallCoord.X == localCoord.X-4 && wallCoord.Y == localCoord.Y ))
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

bool GameController::isBulletFortressCollision(const Bullet & bullet, const Wall & fortress)
{
	auto wallLocalCoord = fortress.getFortressStartPosition();
	auto bulletCoord = bullet.getPosition();

	for (auto &local_coord : Wall::LOKAL_FORTRESS_COORD)
	{
		COORD localCoord = { local_coord.X + wallLocalCoord.X, local_coord.Y + wallLocalCoord.Y };

		if (bulletCoord.X == localCoord.X && bulletCoord.Y == localCoord.Y)
			return true;
	}
	return false;
}
