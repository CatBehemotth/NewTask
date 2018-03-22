#ifndef WALL_H_
#define WALL_H_	

class Wall
{
public:
	Wall(const COORD& startCoords, const char& symbol);
	~Wall();

	static const std::vector<COORD>localCoords; 
	static const std::vector<COORD>localFortressCoords;
	
	void draw();
	void drawFortress();
	const COORD& getPosition() const;
	

private:
	char wallSymbol_;
	COORD startPosition_ ;
	COORD startFortPosition_ ;

};

#endif // !WALL_H_
