#ifndef MYTANK_H_
#define MYTANK_H_
#include "Tank.h"

class MyTank : public Tank
{
public:
	MyTank(TankListener &listener, const int& score, const char& element, const int& health,
													COORD startCoord, COORD directionOfTank);
	~MyTank();

	
	virtual void fire() const override;
	void update() override;	
};
#endif // !MYTANK_H_
