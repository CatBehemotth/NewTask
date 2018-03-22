#include "stdafx.h"
#include "UpdateDisplay.h"

UpdateDisplay::UpdateDisplay()
{
}

UpdateDisplay::~UpdateDisplay()
{
}

void UpdateDisplay::drowElement(const COORD& elementPos, char element)
{
	HANDLE hOut;
	COORD Position = { elementPos.X, elementPos.Y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, Position);
	std::cout << element;
}

void UpdateDisplay::cleanDisplay(const COORD& boardSize, char element)
{
	for (short i = 0; i < boardSize.X; ++i)
	{
		drowElement({ 0, i }, '*');
		drowElement({ i, boardSize.X - 1 }, '*');
		drowElement({ i, 0 }, '*');
		drowElement({ boardSize.X - 1, i }, '*');
	}

	for (short y = 1; y < boardSize.Y - 1; ++y)
	{
		for (short x = 1; x < boardSize.X - 1; ++x)
		{
			HANDLE hOut;
			COORD Position = { x, y };
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hOut, Position);
			std::cout << " ";
		}
	}
}
