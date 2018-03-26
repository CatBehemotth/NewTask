#include "stdafx.h"
#include "DisplayCreator.h"

const COORD DisplayCreator::FIELD_SIZE = { 50, 50 };
const COORD DisplayCreator::WINDOW_SIZE = { 50,54 };



DisplayCreator::DisplayCreator()
{
}

DisplayCreator::~DisplayCreator()
{
}

void DisplayCreator::drawScore(const COORD& elementPos, int currentScore)
{
	HANDLE hOut;
	COORD Position = { elementPos.X, elementPos.Y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, Position);
	std::cout << "Score: " << currentScore;
}

void DisplayCreator::drawTime(const COORD& elementPos, clock_t currentTime)
{
	HANDLE hOut;
	COORD Position = { elementPos.X, elementPos.Y };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, Position);
	std::cout << "Time: " << (currentTime / CLOCKS_PER_SEC)/ 60 <<" m : "<<(currentTime / CLOCKS_PER_SEC) % 60<<" s. ";
}