### Overview

This repo contains C code to complete the Micromouse floodfill simulator (https://github.com/mackorone/mms) using a weighted floodfill algorithm. Unlike traditional floodfill, which weights adjacent squares equally, this weighted floodfill algorithm can, in addition, weigh turns and streaks of straight conseuctive squares.

### Understanding and changing weights

To change the weights, change constants ```TURN_SCORE```, ```TILE_SCORE```, and ```STREAK_SCORE``` in ```solver.c```. \
```TURN_SCORE``` refers to the penalty for making a turn. \
```TILE_SCORE``` refers to the penalty for moving to an adjacent square.\
```STREAK_SCORE``` refers to the penalty for moving to each additional consecutive square in a straight line. Since we typically want to reward the mouse moving in one diretion, ```STREAK_SCORE``` should be set to a negative number to act as a bonus. 

For example, if ```TILE_SCORE``` is set to 10 and ```STREAK_SCORE``` is set to -1, moving two squares in one direction is worth (10\*2)-1=19, moving three squares in one direction is worth (10\*3)-1-2=27, moving four squares in one direction is worth (10\*4)-1-2-3=34, as so on.

### Demo

I've uploaded a short [![demo video](https://img.youtube.com/vi/YOUTUBE_VIDEO_ID_HERE/0.jpg)](https://www.youtube.com/watch?v=JVsRV0mu0jg) to YouTube with a turn score of 5, tile score of 10, and a streak score of 0. Notice that near the beginning of the maze, the mouse opts to choose a slightly longer path with less turns rather than the shorter path with more turns.

