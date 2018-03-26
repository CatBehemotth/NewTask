#ifndef BULLET_H_
#define BULLET_H_

class Bullet
{
public:
	enum eSource
	{
		ENEMY_TANK, MYTANK
	};
	Bullet(const COORD& startCoords, const COORD& direction, eSource source);
	~Bullet();

	void draw();
	void update();
	const eSource getESource()const;
	const COORD& getPosition() const;

	bool operator==(const Bullet& first)
	{
		bool result = this == &first;
		return result;
	}
	

private:
	COORD position;
	COORD direction;
	eSource source_;
};
#endif // !BULLET_H_
