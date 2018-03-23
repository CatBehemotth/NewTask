#ifndef CONSTANTS_H_
#define CONSTANTS_H_
const int  MAXIMUM_NUMBER_OF_ENEMIES = 5;
const int MAXIMUM_WALLS = 5;
const char WALL_SYMBOL = ')';
const char TANK_BODY[4] = {'#','&','@','%'};

const int arSize = 5;
const COORD VARIANTS_OF_DIRECTIONS[arSize] = { {-1, 0}, {0, 0}, {1, 0}, {0, -1}, {0, 1} };
const int ENEMY_HEALTH = 1;

const COORD START_COORDINATES[5] = { { 15,46 }, { 12,40 }, { 28,30 }, { 32,5 }, { 20,19 } };


#endif // !CONSTANTS_H_
