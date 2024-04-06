#ifndef API_H
#define API_H

int API_wallFront();
int API_wallRight();
int API_wallLeft();

void API_moveForward();
void API_moveForwardHalf();

void API_turnRight();
void API_turnLeft();
void API_turnRight45();
void API_turnLeft45();

// remove the below commands when transferring to mouse. assign no-ops

int API_mazeWidth();
int API_mazeHeight();

void API_setWall(int x, int y, char direction);
void API_clearWall(int x, int y, char direction);

void API_setColor(int x, int y, char color);
void API_clearColor(int x, int y);
void API_clearAllColor();

void API_setText(int x, int y, char* str);
void API_clearText(int x, int y);
void API_clearAllText();

int API_wasReset();
void API_ackReset();

void debug_log(char* text);
float getStat(char* text);

#endif