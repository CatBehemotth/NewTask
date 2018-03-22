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

	void Finish()const;

	void startCircle();

	void calculateBulletsCollision();

	void calculateTanksCollisions();
	void calculateBulletsFieldCollision();
	void calculateBulletsBarrierCollision();
	void calculateTankMyTankCollision();
	void calculateTankBarrierCollision();
	void addBarrier(const COORD& startCoord);
	
	COORD randomBarrierCoord();

	bool isTankBarrierCollision(const Tank& tank, const Wall & barrier);
	bool isBulletTankCollision(const Bullet& bullet, const Tank& tank);
	bool isBulletBarrierCollision(const Bullet& bullet, const Wall & barrier);
	bool isBulletFieldCollision(const Bullet& bullet);
	bool isTankTankCollision(const Tank& enemyTank, const Tank & myTank);
	bool isFire(const Tank& enemyTank, const MyTank& myTank);

	virtual void onFire(const COORD& startCoord, const COORD& direction) override;

private:
	std::vector<std::shared_ptr<Tank>> mTanks;
	std::vector<Bullet> mBullets;
	std::vector<Wall> mWall;

};
#endif // !GAMECONTROLLER_H_

