#ifndef MYTANK_H_
#define MYTANK_H_
#include "Tank.h"

class MyTank : public Tank
{
public:
	MyTank(TankListener &listener, const int& score, const char& element, const int& health,
		COORD startCoord, COORD directionOfTank);
	~MyTank();

	const int getScore() const;
	void setScore(int& score);
	void update() override;

private:
	int score_;
};
#endif // !MYTANK_H_
