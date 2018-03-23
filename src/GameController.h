#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "Tank.h"
#include "Bullet.h"
#include "Wall.h"
#include "MyTank.h"

class TankListener
{
public:
	virtual void onFire(const COORD& startCoord, const COORD& direction) = 0;
};

class GameController : public TankListener
{
public:
	GameController();
	~GameController();

	void startCircle();

	void calculateBulletsCollision();
	void calculateTanksCollisions();
	void calculateBulletsFieldCollision();
	void calculateBulletsWallCollision();
	void calculateTankMyTankCollision();
	void calculateTankWallCollision();
	void addWall(const COORD& startCoord, const char& symbol);
	int randomTankDirection();
	size_t ramdom();

	COORD randomTankCoords();
	COORD randomWallCoord();

	bool isVictory();
	bool isFinish(const Bullet & bullet, const Wall & wall)const;
	bool isTankWallCollision(const Tank& tank, const Wall & Wall);
	bool isBulletTankCollision(const Bullet& bullet, const Tank& tank);
	bool isBulletWallCollision(const Bullet& bullet, const Wall & Wall);
	bool isBulletFieldCollision(const Bullet& bullet);
	bool isTankTankCollision(const Tank& enemyTank, const Tank & myTank);
	bool isFire(const Tank& enemyTank, const Tank& myTank);

	virtual void onFire(const COORD& startCoord, const COORD& direction) override;

private:
	std::vector<std::shared_ptr<Tank>> mTanks;
	std::vector<Bullet> mBullets;
	std::vector<Wall> mWall;
	//std::vector<Tank> mTanks;

};
#endif // !GAMECONTROLLER_H_

