#ifndef WALL_H_
#define WALL_H_	

class Wall
{
public:
	Wall(const COORD& startCoords, const char& symbol);
	~Wall();

	static const std::vector<COORD>LOKAL_COORDS; 
	static const std::vector<COORD>LOKAL_FORTRESS_COORD;
	
	void draw();
	void drawFortress();
	const COORD& getPosition() const;
	

private:
	char wallSymbol_;
	COORD startPosition_ ;
	static const COORD START_FORT_POSITION_ ;

};

#endif // !WALL_H_
