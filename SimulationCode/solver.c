#include "solver.h"
#include "API.h"
#include <stdio.h>
#include <stdlib.h>

// queue type and function declarations

typedef struct coord {
    int x;
    int y;
} coord;

typedef coord item_type;
typedef struct _queue* queue;
queue queue_create();
void queue_destroy(queue q);
void queue_push(queue q, item_type elem);
item_type queue_pop(queue q);
item_type queue_first(queue q);
int queue_is_empty(queue q);
int queue_size(queue q);
void queue_clear(queue q);

// queue type implentations

struct node {
    item_type data;
    struct node* next;
};

struct _queue {
    struct node* head;
    struct node* tail;
    int size;
};

queue queue_create() {
queue q = (queue) malloc(sizeof(struct _queue));
    if (q == NULL) {
        fprintf(stderr, "Insufficient memory to \
        initialize queue.\n");
        abort();
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

void queue_destroy(queue q) {
    if (q == NULL) {
        fprintf(stderr, "Cannot destroy queue\n");
        abort();
    }
    queue_clear(q);
    free(q);
}

void queue_push(queue q, item_type elem) {
    struct node* n;
    n = (struct node*) malloc(sizeof(struct node));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory to \
        create node.\n");
        abort();
    }
    n->data = elem;
    n->next = NULL;
    if (q->head == NULL) {
        q->head = q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    q->size += 1;
}

item_type queue_pop(queue q) {
    if (queue_is_empty(q)) {
    fprintf(stderr, "Can't pop element from queue: \
    queue is empty.\n");
    abort();
    }
    struct node* head = q->head;
    if (q->head == q->tail) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    q->size -= 1;
    item_type data = head->data;
    free(head);
    return data;
}

item_type queue_first(queue q) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Can't return element from queue: \
        queue is empty.\n");
        abort();
    }
    return q->head->data;
}

int queue_is_empty(queue q) {
    if (q==NULL) {
        fprintf(stderr, "Cannot work with NULL queue.\n");
        abort();
    }
    return q->head == NULL;
}

int queue_size(queue q) {
    if (q==NULL) {
        fprintf(stderr, "Cannot work with NULL queue.\n");
        abort();
    }
    return q->size;
}

void queue_clear(queue q) {
    if (q==NULL) {
        fprintf(stderr, "Cannot work with NULL queue.\n");
        abort();
    }
    while(q->head != NULL) {
        struct node* tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    q->tail = NULL;
    q->size = 0;
}

// global variable declarations and assignments

int target = 1; // 0 if going to start, 1 if going to center
int currentX = 0;
int currentY = 0;
Heading currentHeading = NORTH;

// watch out when looking at the following arrays, remember that in 2D text form:
// x values are displayed vertically and y values are displayed horizontally.
// in addition, the x values are displayed upside down compared to how they are displayed in
// a graphing convention; here, x = 15 is at the bottom while x = 0 is at the top

// keeps track of vertical walls in the maze
int verticalWalls[17][16] =
{ // x = 0 and x = 16 are all walls
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// keeps track of horizontal walls in the maze
int horizontalWalls[16][17] =
{ // y = 0 and y = 16 are all horizontal walls
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

int floodArray[16][16];
/* for reference, this is what initialization for a 16x16 maze with goal at the center looks like
{
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1, 0, 0,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1, 0, 0,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}; */

// keeps track of all of the cells the mouse has visited
int travelArray[16][16] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

// resets the floodfill array to target the center as destination
void resetToCenter()
{
    // set the entire flood array to blank values (-1)
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            floodArray[x][y] = -1;
        }
    }
    // set desired goal values (0). for regular competition, this is the center of the maze
    floodArray[7][7] = 0;
    floodArray[7][8] = 0;
    floodArray[8][7] = 0;
    floodArray[8][8] = 0;
}

// resets the floodfill array to target the start as destination
void resetToStart()
{
    // set the entire flood array to blank values (-1)
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            floodArray[x][y] = -1;
        }
    }
    // set desired goal values (0). to go back to the start, this is the bottom left corner
    floodArray[0][0] = 0;
}

// given a coord, checks to see if the mouse has visited a certain cell before
int checkTravelArray(coord c)
{
    return travelArray[c.x][c.y];
}

// given a coord, updates the travel array to mark that the mouse has visited that cell before
void updateTravelArray(coord c)
{
    travelArray[c.x][c.y] = 1;
    // API_setText(c.x,c.y,"1");
}

// given heading and coordinates, check if there is a wall in front of the mouse
int checkWall(Heading heading, coord c)
{
    int x = c.x;
    int y = c.y;

    // check if there is a wall based on the direction the mouse is facing
    switch (heading)
    {
        case NORTH:
            return horizontalWalls[x][y+1];
        case WEST:
            return verticalWalls[x][y];
        case SOUTH:
            return horizontalWalls[x][y];
        case EAST:
            return verticalWalls[x+1][y];
    }
    // the program should ideally never return -1
    return -1;
}

// given heaidng and coordinates, returns the floodfill value of the corresponding neighbor cell.
// if the neighbor is off of the maze (argument cell is on the boundary of the maze), return -2
int getNeighbor(Heading heading, coord c)
{
    int x = c.x;
    int y = c.y;
    switch (heading)
    {
        case NORTH:
            if (y >= 15)
                return -2;
            else
                return floodArray[x][y+1];
        case WEST:
            if (x <= 0)
                return -2;
            else
                return floodArray[x-1][y];
        case SOUTH:
            if (y <= 0)
                return -2;
            else
                return floodArray[x][y-1];
        case EAST:
            if (x >= 15)
                return -2;
            else
                return floodArray[x+1][y];
    }
}

// given heading and coordinates, check if the neighbor cell can be processed.
// to be processed, the neighbor cell's floodfill value should be -1 and there should not 
// be a wall in between the current cell and the neighborcell
int checkAvailable(Heading heading, coord c)
{
    // checks if there is a wall in the way
    if (checkWall(heading,c))
        return 0;

    // checks if the neighbor's floodfill value is -1 // need to prevent from being on the boundary
    int neighbor = getNeighbor(heading,c);
    if (neighbor == -1)
        return 1;
    // if the neighbor is outside the maze or not blank, return 0
    return 0;
}

// given coordinate, updates the respective cell's floodfill value
void updateFloodArray(coord c, int val)
{
    int x = c.x;
    int y = c.y;
    floodArray[x][y] = val;
}

// given coordinate, gets the respective cell's floodfill value
int checkFloodArray(coord c)
{
    return floodArray[c.x][c.y];
}

// updates the floodfill array based on known walls
void floodFill() {
    // set non-goal values to blank so that the floodfill array can be recalculated
    resetToCenter();

    // declare/initialize relevant variables for queue for floodfill algorithm
    queue q = queue_create();
    coord current;
    int currentVal;

    // iterate through the 2D array, find goal values and add them to the queue
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            if (floodArray[x][y] == 0)
            {
                current.x = x;
                current.y = y;
                queue_push(q,current);
            }
        }
    }

    // adds available neighbors to queue and updates their floodfill values
    while (!queue_is_empty(q))
    {
        current = queue_pop(q);
        
        // prints the floodfill number to the simulation screen
        char forSetText[4] = "";
        sprintf(forSetText, "%d", floodArray[current.x][current.y]);
        API_setText(current.x,current.y,forSetText);

        coord neighbor;
        currentVal = floodArray[current.x][current.y];

        // set value of all available (blank and accessible) neighbors to current's value + 1
        // and add available neighbors to queue
        if (checkAvailable(NORTH,current))
        {
            neighbor.x = current.x;
            neighbor.y = current.y + 1;
            queue_push(q,neighbor);
            updateFloodArray(neighbor,currentVal+1);
        }
        if (checkAvailable(WEST,current))
        {
            neighbor.x = current.x-1;
            neighbor.y = current.y;
            queue_push(q,neighbor);
            updateFloodArray(neighbor,currentVal+1);
        }
        if (checkAvailable(SOUTH,current))
        {
            neighbor.x = current.x;
            neighbor.y = current.y - 1;
            queue_push(q,neighbor);
            updateFloodArray(neighbor,currentVal+1);
        }
        if (checkAvailable(EAST,current))
        {
            neighbor.x = current.x + 1;
            neighbor.y = current.y;
            queue_push(q,neighbor);
            updateFloodArray(neighbor,currentVal+1);
        }
    }
}

// places a wall in respective arrays and API at the given heading and coordinate
void placeWall(Heading heading, coord c)
{
    int x = c.x;
    int y = c.y;
    char direction;

    // sets a wall in the wall arrays
    switch (heading)
    {
        case NORTH:
            horizontalWalls[x][y+1] = 1;
            direction = 'n';
            break;
        case WEST:
            verticalWalls[x][y] = 1;
            direction = 'w';
            break;
        case SOUTH:
            horizontalWalls[x][y] = 1;
            direction = 's';
            break;
        case EAST:
            verticalWalls[x+1][y] = 1;
            direction = 'e';
            break;
    }
    // graphically places a wall onto the simulation window via the API
    API_setWall(x,y,direction);
}

// checks for and then updates the walls for the current cell
void updateWalls()
{
    // looks at walls at the current location
    coord c = {.x = currentX, .y = currentY};
    int wallFront = API_wallFront();
    int wallLeft = API_wallLeft();
    int wallRight = API_wallRight();

    // based on the current heading, places walls at the respective locations.
    // walls are placed both in the global wall arrays and in the simulator
    switch (currentHeading)
    {
        case NORTH:
            if (wallFront)
                placeWall(currentHeading,c);
            if (wallLeft)
                placeWall(WEST,c);
            if (wallRight)
                placeWall(EAST,c);
            break;
        case WEST:
            if (wallFront)
                placeWall(currentHeading,c);
            if (wallLeft)
                placeWall(SOUTH,c);
            if (wallRight)
                placeWall(NORTH,c);
            break;
        case SOUTH:
            if (wallFront)
                placeWall(currentHeading,c);
            if (wallLeft)
                placeWall(EAST,c);
            if (wallRight)
                placeWall(WEST,c);
            break;
        case EAST:
            if (wallFront)
                placeWall(currentHeading,c);
            if (wallLeft)
                placeWall(NORTH,c);
            if (wallRight)
                placeWall(SOUTH,c);
            break;
    }
}

// returns the heading to the next cell to visit based on floodfill values
Heading nextHeading()
{
    // set minimum neighbor's floodfill value to very large number, expecting it to get overwritten later
    int minNeighbor = 1000;
    Heading minDirection;
    coord c = {.x = currentX, .y = currentY};

    // finds and returns the direction of the accessible neighbor with the lowest floodfill value
    if ((!checkWall(NORTH,c)) && (floodArray[c.x][c.y + 1] < minNeighbor))
    {
        minNeighbor = floodArray[c.x][c.y + 1];
        minDirection = NORTH;
    }
    if ((!checkWall(WEST,c)) && (floodArray[c.x - 1][c.y] < minNeighbor))
    {
        minNeighbor = floodArray[c.x - 1][c.y];
        minDirection = WEST;
    }
    if ((!checkWall(SOUTH,c)) && (floodArray[c.x][c.y - 1] < minNeighbor))
    {
        minNeighbor = floodArray[c.x][c.y - 1];
        minDirection = SOUTH;
    }
    if ((!checkWall(EAST,c)) && (floodArray[c.x + 1][c.y] < minNeighbor))
    {
        minNeighbor = floodArray[c.x + 1][c.y];
        minDirection = EAST;
    }    
    return minDirection;
}

// increments currentX or currentY global variable based on the mouse's current heading
void incrementXY()
{
    switch (currentHeading)
    {
        case NORTH:
            currentY++;
            break;
        case WEST:
            currentX--;
            break;
        case SOUTH:
            currentY--;
            break;
        case EAST:
            currentX++;
            break;
    }
}

// Increments coord in the direction of the heading by input integer,
// then returns updated coord
coord incrementCoord(Heading h, coord currentCoord, int num)
{
    coord c;
    c.x = currentCoord.x;
    c.y = currentCoord.y;
    switch (h)
    {
        case NORTH:
            c.y += num;
            break;
        case WEST:
            c.x -= num;
            break;
        case SOUTH:
            c.y -= num;
            break;
        case EAST:
            c.x += num;
            break;
    }
    return c;
}

// turns currentHeading global variable to the left based on the mouse's current heading,
// then returns LEFT action
Action incrementLeft()
{
    switch (currentHeading)
    {
        case NORTH:
            currentHeading = WEST;
            break;
        case WEST:
            currentHeading = SOUTH;
            break;
        case SOUTH:
            currentHeading = EAST;
            break;
        case EAST:
            currentHeading = NORTH;
            break;
    }
    return LEFT;
}

// turns currentHeading global variable to the right based on the mouse's current heading,
// then returns RIGHT action
Action incrementRight()
{
    switch (currentHeading)
    {
        case NORTH:
            currentHeading = EAST;
            break;
        case WEST:
            currentHeading = NORTH;
            break;
        case SOUTH:
            currentHeading = WEST;
            break;
        case EAST:
            currentHeading = SOUTH;
            break;
    }
    return RIGHT;
}

// based on updated wall and floodfill information, return the next action that the mouse should do
Action nextAction()
{
    Heading turnTo = nextHeading();
    coord currentCoord = {.x = currentX, .y = currentY};
    updateTravelArray(currentCoord);
    coord originalCoord = currentCoord;

    // moves forward if the mouse is already facing the correct heading
    if (turnTo == currentHeading)
    {
        int moveNumber = 0;
        while (checkTravelArray(currentCoord) == 1 && (!checkWall(turnTo,currentCoord))
        && (checkFloodArray(incrementCoord(turnTo,currentCoord,1)) < checkFloodArray(currentCoord)))
        {
            moveNumber++;
            currentCoord = incrementCoord(turnTo,currentCoord,1);
        } 
        for (int i = 0; i < moveNumber; i++)
        {
            updateTravelArray(incrementCoord(turnTo,originalCoord,i));
        }
        currentX = currentCoord.x;
        currentY = currentCoord.y;

        char forSetText[4] = "";
        sprintf(forSetText, "%d", moveNumber);
        debug_log(forSetText);

        for (int i = 0; i < moveNumber; i++)
        {
            API_moveForward();
        }
        return FORWARD;
    }

    // determines which way to turn based on current direction and desigred direction
    if ((currentHeading == NORTH && turnTo == EAST) || 
        (currentHeading == WEST && turnTo == NORTH) ||
        (currentHeading == SOUTH && turnTo == WEST) ||
        (currentHeading == EAST && turnTo == SOUTH))
    {
        API_turnRight();
        return incrementRight();
    }
    else
    {
        API_turnLeft();
        return incrementLeft();
    }
}

void checkDestination()
{
    if (target) // if going to center
    {
        if (currentX >= 7 && currentX <=8 && currentY >= 7 && currentY <= 8)
            {
                API_ackReset();
                currentX = 0;
                currentY = 0;
                currentHeading = NORTH;
            }
    }
    else
    {
        if (currentX == 0 && currentY == 0)
            target = 1;
    }
}

// sends the mouse's recommended next action back to main
Action solver() {
    checkDestination();
    updateWalls();    
    floodFill();
    return nextAction();
}