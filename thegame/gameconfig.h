#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#define NACTORS 1 // number of actors that we're drawing on the screen
// X and Y denote the box that can be used to interact around the player
// limits for Y axis
#define LOWER_SCROLL_LIMIT_Y 20
#define UPPER_SCROLL_LIMIT_Y 200
// limits for the X axis
#define LOWER_SCROLL_LIMIT_X 20
#define UPPER_SCROLL_LIMIT_X 230
// game states
#define TITLESCREEN 0
#define GAMETIME 1
#define GAMEOVER 2

typedef unsigned char gamestate_t;

#endif