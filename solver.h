#ifndef SOLVER_H
#define SOLVER_H

typedef enum Heading {NORTH, WEST, SOUTH, EAST} Heading;
typedef enum Action {LEFT, FORWARD, RIGHT, IDLE} Action;

Action solver();

#endif