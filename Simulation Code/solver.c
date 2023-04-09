#include "solver.h"
#include "API.h"

Action solver() {
    return leftWallFollower();
}

// This is an example of a simple left wall following algorithm.
Action leftWallFollower() {
    if(API_wallFront()) {
        if(API_wallLeft()){
            return RIGHT;
        }
        return LEFT;
    }
    return FORWARD;
}


// Put your implementation of floodfill here!
Action floodFill() {
    return IDLE;
}

// maze array
// floodfill array

/* Loop
* 
    Finds the values of it’s neighboring cells (from the flood array)
    Travels to the neighboring cell with the least value.
    Detects the walls to its left, right and the front
    Updates the newly found walls in the maze array
    Perform the flood fill for the entire flood array
    Back to step 1, and continue until the robot moves to the desired position.
*/

// need to implement flood fill algorithm. use queue algorithm for each cell after each loop run

/*

direction a = determineLeastNeighbor(x, y);
travel(a); 
- turnRight();
- turnLeft();
- moveForward();

wallFront();
setWall();

wallLeft();
setWall();

wallRight();
setWall();

updateMazeArray();

determineLeastNeighbor(x,y);

*/