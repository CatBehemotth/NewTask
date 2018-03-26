#ifndef DISPLAYCREATOR_H_
#define DISPLAYCREATOR_H_


class DisplayCreator
{
public:
	DisplayCreator();
	~DisplayCreator();

	static const COORD WINDOW_SIZE ;
	static const COORD FIELD_SIZE ;

	static void drawScore(const COORD& elementPos, int currentScore);
	static void drawTime(const COORD& elementPos, clock_t currentTime);
};
#endif // !DISPLAYCREATOR_H_
