#include "solver.h"
#include "API.h"
#include <stdio.h>
#include <stdlib.h>

// queue implementation

int currentX = 0;
int currentY = 0;
Heading currentHeading = NORTH;

struct coord
{
    int x;
    int y;
};

typedef struct coord item_type;
typedef struct _queue* queue;
queue queue_create();
void queue_destroy(queue q);
void queue_push(queue q, item_type elem);
item_type queue_pop(queue q);
item_type queue_first(queue q);
int queue_is_empty(queue q);
int queue_size(queue q);
void queue_clear(queue q);

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

int mazeArray[16][16] =
{
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
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int floodArray[16][16] =
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
};


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

// given heading and coordinates, check if there is no wall in front of the mouse
int checkClear(Heading heading, struct coord c)
{
    int x = c.x;
    int y = c.y;
    int val = mazeArray[x][y];
    // quickly check if the cell is sorrounded by walls on 4 sides
    if (val == 16) 
    {
        debug_log("sorrounded on all sides");
        return 1;
    }
    // check if there is a wall based on the direction the mouse is facing
    switch (heading)
    {
        case NORTH:
        {
            if (y == 15 || val == 2 || val == 7 || val == 8 || val == 10 || val == 12 || val == 14)
                return 1;
            else
                return 0;
        }
        case WEST:
        {
            if (x == 0 || val == 1 || val == 5 || val == 8 || val == 9 || val == 11 || val == 14)
                return 1;
            else
                return 0;
        }
        case SOUTH:
        {
            if (y == 0 || val == 4 || val == 5 || val == 6 || val == 10 || val == 12 || val == 14)
                return 1;
            else
                return 0;
        }        
        case EAST:
        {
            if (x == 15 || val == 3 || val == 6 || val == 7 || val == 11 || val == 12 || val == 13)
                return 1;
            else
                return 0;
        }   
    }
    debug_log("invalid heading or array");
    return 0;
}

// given heading and coordinates, check if the neighbor cell can be processed.
// to be processed, the neighbor cell's floodfill value should be -1 and there should not 
// be a wall in between the current cell and the neighborcell
int checkAvailable(Heading heading, struct coord c)
{
    // checks if there is a wall in the way
    if (checkClear(heading,c))
    {
        debug_log("wall in the way");
        return 0;
    }
    // checks if the neighbor's floodfill value is -1
    if (heading == NORTH && floodArray[c.x][c.y+1] == -1)
        return 1;
    else if (heading == WEST && floodArray[c.x-1][c.y] == -1)
        return 1;
    else if (heading == SOUTH && floodArray[c.x][c.y-1] == -1)
        return 1;
    else if (heading == EAST && floodArray[c.x+1][c.y] == -1)
        return 1;
    // if the neighbor's value is not blank, return 0
    return 0;
}

// given coordinates, updates the respective cell's floodfill value
void updateFloodFillCell(struct coord c, int val)
{
    int x = c.x;
    int y = c.y;
    floodArray[x][y] = val;
}

// updates the floodfill array and returns best action
Heading floodFill() {
    queue q = queue_create();
    struct coord current;
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
                // I will be very sad if this passes current by reference instead of by value
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
        // debug_log("printing");

        struct coord neighbor;
        currentVal = floodArray[current.x][current.y];
        // set all blank and accessible neighbors to current's value + 1
        if (checkAvailable(NORTH,current))
        {
            debug_log("can north");
            neighbor.x = current.x;
            neighbor.y = current.y + 1;
            queue_push(q,neighbor);
            updateFloodFillCell(neighbor,currentVal+1);
        }
        if (checkAvailable(WEST,current))
        {
            debug_log("can west");
            neighbor.x = current.x-1;
            neighbor.y = current.y;
            queue_push(q,neighbor);
            updateFloodFillCell(neighbor,currentVal+1);
        }
        if (checkAvailable(SOUTH,current))
        {
            debug_log("can south");
            neighbor.x = current.x;
            neighbor.y = current.y - 1;
            queue_push(q,neighbor);
            updateFloodFillCell(neighbor,currentVal+1);
        }
        if (checkAvailable(EAST,current))
        {
            debug_log("can east");
            neighbor.x = current.x + 1;
            neighbor.y = current.y;
            queue_push(q,neighbor);
            updateFloodFillCell(neighbor,currentVal+1);
        }
    }

    // return least possible direction from current position

    current.x = currentX;
    current.y = currentY;

    int minNeighbor = 1000;
    Heading minDirection;

    if ((checkClear(NORTH,current)) && (floodArray[current.x][current.y + 1] < minNeighbor))
    {
        minNeighbor = floodArray[current.x][current.y + 1];
        minDirection = NORTH;
    }
    if ((checkClear(WEST,current)) && (floodArray[current.x - 1][current.y] < minNeighbor))
    {
        minNeighbor = floodArray[current.x - 1][current.y];
        minDirection = WEST;
    }
    if ((checkClear(SOUTH,current)) && (floodArray[current.x][current.y - 1] < minNeighbor))
    {
        minNeighbor = floodArray[current.x][current.y - 1];
        minDirection = SOUTH;
    }
    if ((checkClear(EAST,current)) && (floodArray[current.x + 1][current.y] < minNeighbor))
    {
        minNeighbor = floodArray[current.x + 1][current.y];
        minDirection = EAST;
    }
    
    return minDirection;
}

// checks for and then updates the walls for the current cell
void updateWalls()
{
    API_wallFront(); // if there is a wall in front, change current cell and cell in front
    // but only if the cell in front is not on the map
    API_wallLeft();
    API_wallRight();
}

Action solver() {
    Heading go = floodFill(); // returns the direction with the least floodfill that is possible to go to
    // move to that cell
    // detects walls around it
    // updates newly found walls in maze array
    return leftWallFollower();
}

// maze array
// floodfill array

/* Loop
* 
    Finds the values of it�s neighboring cells (from the flood array)
    Travels to the neighboring cell with the least value.
    Detects the walls to its left, right and the front
    Updates the newly found walls in the maze array
    Perform the flood fill for the entire flood array
    Back to step 1, and continue until the robot moves to the desired position.
*/

// need to implement flood fill algorithm. use queue algorithm for each cell after each loop run

/*

direction a = determineLeastNeighbor(x, y);
travel(a); (to least neighbor)
- turnRight();
- turnLeft();
- moveForward();

if (wallFront())
    setWall());
if (wallLeft());
    setWall();
if (wallRight());
    setWall();

updateMazeArray();
floodFillWithNewArray();

*/