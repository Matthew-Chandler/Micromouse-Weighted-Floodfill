#ifndef SOLVER_H
#define SOLVER_H

struct coord;

typedef enum Heading {NORTH, EAST, SOUTH, WEST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

Action solver();
Action leftWallFollower();
Heading floodFill();

int checkClear(Heading heading, struct coord c);

#endif