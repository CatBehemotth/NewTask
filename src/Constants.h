#ifndef CONSTANTS_H_
#define CONSTANTS_H_
const int  MAXIMUM_NUMBER_OF_TANK = 5;
const int MAXIMUM_WALLS = 8;
const char WALL_SYMBOL = ')';
const char TANK_BODY[4] = {'#','&','@','%'};
const int arSize = 5;
const int ENEMY_HEALTH = 1;
const COORD VARIANTS_OF_DIRECTIONS[arSize] = { {-1, 0}, {0, 0}, {1, 0}, {0, -1}, {0, 1} };
const COORD FORTRESS_POSITION[3] = { { 17,47  }, { 20,45 }, { 23,47 } };
const COORD START_COORDINATES[5] = { { 14,46 }, { 12,40 }, { 40,30 }, { 32,23 }, { 26,19 } };
const COORD SCORE_COORD = { 0,51 };
const COORD TIME_COORD = { 20,51 };
#endif // !CONSTANTS_H_
