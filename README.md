C code to complete the Micromouse floodfill simulator (https://github.com/mackorone/mms) using a weighted floodfill algorithm. Unlike traditional floodfill, which weights adjacent squares equally, this weighted floodfill algorithm can weigh adjacent squares, turns, and streaks of straight consecutive squares differently. 

Change TURN_SCORE, TILE_SCORE, and STREAK_SCORE in solver.c. 
TURN_SCORE refers to the penalty for making a turn.
TILE_SCORE refers to the penalty for moving to an adjacent square.
STREAK_SCORE refers to the bonus (reduction in penalty) for moving to each additional consecutive square in a straight line.
