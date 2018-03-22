#ifndef UPDATEDISPLAY_H_
#define UPDATEDISPLAY_H_

class UpdateDisplay
{
public:
	UpdateDisplay();
	~UpdateDisplay();

	static void drowElement(const COORD& elementPos, char element);
	static void cleanDisplay(const COORD& boardSize, char element);
};

#endif // !UPDATEDISPLAY_H_
