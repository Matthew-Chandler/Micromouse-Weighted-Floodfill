#ifndef CONSTANTS_H
#define CONSTANTS_H

// floodfill weighting scores
const int TURN_SCORE = 0;
const int TILE_SCORE = 1;
const int STREAK_SCORE = 0;
const int STREAK_MULTIPLIER = 0;

// if you want the mouse to reset to the start once it reaches the middle, set RESET_AT_CENTER to 1
// otherwise, set it to 0 if you want it to make its way back to the start
const unsigned char RESET_AT_CENTER = 0;

// starting position. keep it the same for all regular micromouse rules
#define STARTING_TARGET 1; // 0 if going to start, 1 if going to center
#define STARTING_X 0;
#define STARTING_Y 0;
#define STARTING_HEADING NORTH;

#endif