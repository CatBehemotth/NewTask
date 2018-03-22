#ifndef BULLET_H_
#define BULLET_H_

class Bullet
{
public:
	Bullet(const COORD& startCoords, const COORD& direction);
	~Bullet();

	void draw();
	void update();
	const COORD& getPosition() const;

private:
	COORD position;
	COORD direction;
};

#endif // !BULLET_H_
