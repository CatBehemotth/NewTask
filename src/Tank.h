#ifndef TANK_H_
#define TANK_H_

class TankListener;

class Tank
{
public:
	Tank(TankListener& _listener, const char& element, const int& health,
												 const COORD& startCoord,
												 const COORD& directionOfTank);
	~Tank();

	static const std::vector<COORD>localCoords;

	const int getHealth();
	void setHealth(int health = 1);
	bool isAlive(const Tank& unit);
	void setDirection(const COORD& newDirection);
	void setMoveDirection(const COORD& newDirection);	
	const COORD& getCoord() const;

	virtual void draw();
	virtual void update();


protected:

	int tankHealth_;
	char tankBody_;
	TankListener &listener;

	COORD coord = { 5, 5 };
	COORD moveDirection;
	COORD direction;

	void fire() const;

};

#endif // !TANK_H_
